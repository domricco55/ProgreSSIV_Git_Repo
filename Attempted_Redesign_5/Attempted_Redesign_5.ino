
/**
   Teensy_Firmware.ino


   Description: This file is the firmware on the TEENSY for the CALPOLY SSIV

   Date:                      April 26 2018
   Last Edit by:              Dominic Riccoboni

   Version Description:
                              -This Version is the fifth attempted restructure of the code to fit new design with Raspberry Pi firmware. Implemented complete restructure since
                              attempted restructure 4. Now there is a register map union whos memory can be accessed wither by a struct type or an array of bytes. The interrupt 
                              service routine has also been completely rethought. It now accepts an address byte on the first byte of a message, knows whether it is a read or 
                              write request, and has a logical structure that allows the master to write to as many addresses as desired in a single message (so long as they
                              are adjacent) THE LAST PART OF THIS IS NO LONGER VALID DUE TO HOW THE ALLOCATION OF MEMORY FOR A STRUCT OCCURS

   Errors:                    -Probably a lot at the moment


   TO-DOs:
                              -

   Compiling[Y/N]:            Y


*/

#include "uLaren_CAN_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"
#include "t3spi.h"
//libraries for imu
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055_ProgreSSIV.h"
#include "imumaths.h"


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Communication/SPI Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Instantiate T3SPI class as SPI_SLAVE(MAY WANT TO COME BACK LATER AND GET RID OF THIS. MOST IF NOT ALL OF THE SPI SETUP CODE IS BELOW COMMENTED OUT)*/
T3SPI SPI_SLAVE;
///* SPI memory map setup definitions */
//#define SPI_MODE0     0x00//00 mode0, 01 mode1
//#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Spi Register Setup*/
//Create a register map to store read, write, and command data on the Teensy. Values are volatile because the register map is being accessed by spi0_isr 
typedef struct reg_struct {
  volatile uint8_t print_registers;
  volatile uint8_t begin_data_collection;
  volatile uint8_t print_imu;
  volatile uint8_t print_radio;
  volatile uint8_t init_servo_radio;
  volatile uint8_t init_motor_controllers;
  volatile uint8_t init_imu;
// Sensor/Data registers
  // IMU 
  volatile int16_t euler_x;
  volatile int16_t euler_y;
  volatile int16_t euler_z;
  volatile int16_t accl_x;
  volatile int16_t accl_y;
  volatile int16_t accl_z;
  volatile int16_t gyro_x;
  volatile int16_t gyro_y;
  volatile int16_t gyro_z;
  //Servo and Radio 
  volatile int16_t radio_throttle; 
  volatile int16_t radio_steering;
// Output/Actuation Registers
  volatile int16_t throttle_right_front; 
  volatile int16_t throttle_left_front; 
  volatile int16_t throttle_right_rear; 
  volatile int16_t throttle_left_rear; 
  volatile int16_t servo_out;  
} reg_struct_t ;

//union type definition linking the above reg_struct type to a 128 byte array that will be instantiated in loop below. This will be the memory accessed by both the struct and the array
typedef union reg_union {
  volatile uint8_t bytes[128];//Allocates 128 bytes of memory to use for the register map 
  reg_struct_t reg_map; //Map of the registers
} reg_union_t;

//Initialize the register union (making it all zeroes by default)
reg_union_t registers;//Instantiate the register union

//Initializes a register buffer of the same union type as registers. Now registers and registers_buf can copy themselves into each other. Used in spi0_isr to prevent writing 
//data to registers while they are being accessed by spi task.
reg_union_t registers_buf = registers; 

/*
can access exact same data like this:
    registers.bytes[1]
OR like this:
    registers.reg_map.init_servo_radio
*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* spi0_isr buffer related */
//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
volatile uint8_t spi_address_buf;//stores the address byte for use in the isr
volatile uint8_t spi_rw_bit;//stores the information of whether the master is sending a read or write message
#define RW_MASK 0b10000000 
#define ADDRESS_MASK 0b01111111

/*Spi Task/isr Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet. Initilize commands from master will be ignored if initialization has already occured
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been started up
bool imu_on = false;//Used by SPI task to know if imu has already been started up
bool collecting_data = false; //Used by SPI task to start and stop data collection from sensors
bool reg_buf_flag = true;
bool address_flag = true;

/* Teensy Status Byte */
volatile uint8_t Teensy_Status_Byte = 25;//25 by default for now. NOT YET IMPLEMENTED CODE TO HANDLE A TEENSY STATUS BYTE. 

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

FlexCAN CANbus(1000000);

/* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

//loop CAN variables
int ret = 0;
int error = NO_ERROR;


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both for the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
volatile int16_t THR_in; // instantiate variable for throttle input value (ranges from ~-500 to 500)
volatile int16_t ST_in;  // instantiate variable for steering input value (ranges from ~-500 to 500)

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*BNO055 Inertial Measurement Unit Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Instantiate and initialize an Adafruit_BNO055 object */
//bno is the name of the object in this context. Use bno.<function name (arguments)> here to use the objects functions
Adafruit_BNO055 bno = Adafruit_BNO055(); 

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Debugging setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
//"Adding streaming (insertion-style) Output" from playground.arduino.cc
//Allows Serial << "This is an insertion-style message" type operation
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj;}

/*SPI Debugging Setup*/
// SPI Printing Related
uint32_t first_pointer;
uint32_t next_pointer;
uint8_t packet_cnt = 0x01;
#define DEBUG_PRINT 0
#define GENERAL_PRINT 1
//These are used to tell how much time the isr is taking to run
volatile long isrStartTime;
volatile long isrEndTime;
//These are used to tell how much time is elapsing between messages
volatile long messageTime1;
volatile long message_delta_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Dead Switch code */
//Controls if the dead switch is active or not (Recommend that this be active while Simulink code is running. Not recommended for normal mode) TURN THIS INTO A REGISTER??
#define DEAD_SWITCH 1 

//Tells the motor controller actuation code that the trigger
uint8_t safe = 0;

////timing variables
//unsigned long start_time_motors;
//unsigned long current_time_motors;
//unsigned long start_time_servo;
//unsigned long current_time_servo;
//unsigned long start_time_voltage;
//unsigned long current_time_voltage;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* The setup function runs all start up functions. Any functions that are run only once, always, and at startup should go here. */
void setup() {

/*begin serial port operation*/
  Serial.begin(115200);
  while ( !Serial ) ;
  if(GENERAL_PRINT){
    Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
    delay(500); 
  }

  
/*Configure the Teensy for SPI Slave Mode, set some register map initial conditions, and initialize the interrupt service routines*/
  spi_slave_init();
  
  //Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0); //CURRENTLY DONT KNOW WHY THIS IS ENABLING THE ISR
  
  //Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0),spi_transfer_complete_isr,RISING);
  
  //Set some of the starting conditions of the registers in the register map
  registers.reg_map.begin_data_collection = 1;//Anything non-zero will cause the begin_data_collection flag to be set true in the SPI task
  registers.reg_map.init_servo_radio = 1;//Anything non-zero will cause the servo and radio initialization code to run in the SPI task 
  registers.reg_map.init_motor_controllers = 1;//Anything non-zero will cause the motor controllers (associated with the CAN Bus) to initialize in the SPI task
  registers.reg_map.init_imu = 1;//Anything non-zero will cause the init imu code to run in the SPI task
  registers.reg_map.print_radio = 0;//Controls whether radio transeiver data is printing or not
  registers.reg_map.print_imu = 0;//Controls whether IMU data is printing or not
  
  registers.reg_map.servo_out = -500;//Set an initial servo position value. Just a visual que that servo is working at startup
  if(GENERAL_PRINT){
    //Print the registers at initialization
      spi_print();
  }

/* Start up and confirm the start up of the BNO055 Inertial Measurement Unit */
  if(GENERAL_PRINT){
    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
    //Initialize the sensor
  }

  if(!bno.begin())
  {
    if(GENERAL_PRINT){
      //There was a problem detecting the BNO055 ... check your connections
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      //while(1); 
    }

  }
  if(GENERAL_PRINT){
    //Display the current IMU temperature
    int8_t temp = bno.getTemp();
    Serial.print("Current Temperature: ");
    Serial.print(temp);
    Serial.println(" C");
    Serial.println("");
    bno.setExtCrystalUse(true);
    Serial.println("Calibration status values: 0 uncalibrated, 3 fully calibrated");
  }


/*Startup CAN network*/
  CANbus.begin();

}

void loop() {

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Task*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /* Each element an spi message is 1 byte.  The master can send as many bytes per message as it wants.*/
  /*
  * If the read bit is set high, the structure of the incoming message will look like this:
  * registers.bytes[0] -> register address of data_0 (Interrupt 1)
  * registers.bytes[1] -> junk (Interrupt 2)
  * registers.bytes[2] -> junk (Interrupt 3)
  * registers.bytes[3] -> junk -> Teensy_Status (junk is replaced with the Teensy Status byte inside the CS0 isr)
  */
  /* 
  * If the read bit is set high, the structure of the outgoing message will look like this (there is a wasted byte due to the double buffering of the spi hardware registers):
  * registers.bytes[0] -> junk (Interrupt 1)
  * registers.bytes[1] -> Teensy_Status byte (Interrupt 2) 
  * registers.bytes[2] -> data_0 (only relevant for READS)
  * registers.bytes[3] -> data_1 (only relevant for READS)
  */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* COMMANDS Master sends a 1 if it wants the peripheral to be initialized, data collection to start, or some other command to run*/

/*begin_data_collection register*/   
  if (registers.reg_map.begin_data_collection && !collecting_data ) { 
  
    collecting_data = true;
  
  }

  
/*print_registers register (ONLY USE THIS FOR DEBUGGING AND NOT FOR DYNAMIC OPERATION, THERE IS A DELAY)*/   
  //If Master wants Teensy to print it will send a true to address of print_registers and this code will run
   if (registers.reg_map.print_registers){
    
      delay(1);//Wait for all of the registers to be written to before printing them (in case the print command is being sent along with write data)
      spi_print();
      registers.reg_map.print_registers = 0;//Clear the print_registers register so that a print_registers command from master prints the registers only once.

   }
   
/* print_sensors register*/
  //Print live time IMU values
  if (registers.reg_map.print_imu){
      delay(50);
      print_imu_data();  
  }
  
/* print_sensors register*/
  //Print live time radio values
  if (registers.reg_map.print_radio){
      delay(50);
      print_radio_data();  
  }
  
/*init_servo_radio register*/
    //Initialize the servo and radio if asked to do so by Master and the on flag is false    
  if (registers.reg_map.init_servo_radio && !servo_radio_on) {
    initPWMin();
    initServo(); 
    servo_radio_on = true;
  }
  
/*init_motor_controllers register*/   
  //Initialize the motor controllers if asked to do so by Master and the motor_controllers_on flag is false  
  if (registers.reg_map.init_motor_controllers && !motor_controllers_on) {
    
    //Run the function that sends the CAN message for reseting the nodes. Ret is what is returned during the CAN message
    ret = reset_nodes();
    if (ret > 0)
    {
      error = ret;
    }
    delay(1000);
    //Run the function that sends the CAN message for initializing CAN. Ret is what is returned during the CAN message
    ret = initialize_CAN();
    if (ret > 0)
    {
      error = ret;
    }
    delay(50);
    //Run the function that sends the CAN message for initializing motor controller node 1. Ret is what is returned during the CAN message
    ret = initialize_MC(NODE_1);
    if (ret > 0)
    {
      error = ret;
    }
    //A uLaren_CAN_Driver function that prints a recieved CAN message I believe. 
    process_available_msgs();
    delay(100);
    //Run the function that sends the CAN message for initializing motor controller node 2. Ret is what is returned during the CAN message
    ret = initialize_MC(NODE_2);
    if (ret > 0)
    {
      error = ret;
    }
    //A uLaren_CAN_Driver function that prints a recieved CAN message I believe. 
    process_available_msgs();
    delay(100);
    //Run the function that sends the CAN message for initializing motor controller node 3. Ret is what is returned during the CAN message
    ret = initialize_MC(NODE_3);
    if (ret > 0)
    {
      error = ret;
    }
    //A uLaren_CAN_Driver function that prints a recieved CAN message I believe. 
    process_available_msgs();
    delay(100);
    //Run the function that sends the CAN message for initializing motor controller node 4. Ret is what is returned during the CAN message
    ret = initialize_MC(NODE_4);
    if (ret > 0)
    {
      error = ret;
    }
    //If one or more of the attempted initializations returned an ERROR_CAN_WRITE, then stop all motor controllers from operating and 
    //for now, do nothing and exit. I NEED TO CHANGE WHAT HAPPENS HERE!!! Before there were some printed errors and such but not sure
    if (error == ERROR_CAN_WRITE)
    {
      delay(500);
      stop_remote_node(NODE_1); //DOES THIS TURN OFF THE MOTOR DRIVERS?
      stop_remote_node(NODE_2);
      stop_remote_node(NODE_3);
      stop_remote_node(NODE_4);
      
      delay(500);
      //This function "process_available_msgs() may be printing CAN errors if they have occured but not certain. uLaren would know. 
      process_available_msgs();
      //NEED TO DEAL WITH ERROR CODE HERE. IF NO STARTUP THEN DO SOMETHING
      error = 0;
    }
    else
    {
      motor_controllers_on = true;         
      //Link the nodes together...a lot is happening in their link_node function. I'm not really sure what is going on with this
      //The function includes calls to OTHER uLaren_CAN_Driver functions including write_velocity_and_enable_MC(), arm_MC(), and send_statusword_request()
      //Thinking that they used this function and intended for it only to be used once and maybe Paul thought that was the function 
      //you call to write a velocity value. Or it could be that they couldnt get the normal write_velocity function to work and resorted
      //to using the one with the enable_MC thing...really really not sure. NEED TO FIGURE THIS ALL OUT 
      link_node(NODE_1);
      delay(500);
      link_node(NODE_2);
      delay(500);
      link_node(NODE_3);
      delay(500);
      link_node(NODE_4);
      delay(500);

      //Make sure the motors arent actuating initially
      //Write the throttle_right_front register value to the motor controller
      write_velocity_and_enable_MC(NODE_1, 0 );
      
      //Write the throttle_left_front register value to the motor controller
      write_velocity_and_enable_MC(NODE_2, 0 );
      
      //Write the throttle_right_rear register value to the motor controller
      write_velocity_and_enable_MC(NODE_3, 0);
    
      //Write the throttle_left_rear register value to the motor controller
      write_velocity_and_enable_MC(NODE_4, 0);
    }

  /* init_imu register */
  if(registers.reg_map.init_imu && !imu_on){
    if(!bno.begin())
    {
      if(GENERAL_PRINT){
        //There was a problem detecting the BNO055 ... check your connections
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
        //while(1); 
      }
  
    }
    if(GENERAL_PRINT){
      //Display the current IMU temperature
      int8_t temp = bno.getTemp();
      Serial.print("Current Temperature: ");
      Serial.print(temp);
      Serial.println(" C");
      Serial.println("");
      bno.setExtCrystalUse(true);
      Serial.println("Calibration status values: 0 uncalibrated, 3 fully calibrated");
    }
    imu_on = true;

  }

  }
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array*/

  //Write the servo value from servo_out register
  writeServo(registers.reg_map.servo_out);
  
  // Dead man's switch.  If throttle is not at full(ish) forward or reverse motors should be set to zero.
  if ( THR_in > 200 ) {
      safe = 1;
  }
  else {
      safe = 0;
  }    
  
  if (DEAD_SWITCH && !safe){
    
    //Write the throttle_right_front register value to the motor controller
    write_velocity_and_enable_MC(NODE_1, 0);
    
    //Write the throttle_left_front register value to the motor controller
    write_velocity_and_enable_MC(NODE_2, 0);
    
    //Write the throttle_right_rear register value to the motor controller
    write_velocity_and_enable_MC(NODE_3, 0);
  
    //Write the throttle_left_rear register value to the motor controller
    write_velocity_and_enable_MC(NODE_4, 0);
    
  }
  
  else{
      
    //Write the throttle_right_front register value to the motor controller
    write_velocity_and_enable_MC(NODE_1, -registers.reg_map.throttle_right_front * SCALE_FACTOR);
    
    //Write the throttle_left_front register value to the motor controller
    write_velocity_and_enable_MC(NODE_2, registers.reg_map.throttle_left_front * SCALE_FACTOR);
    
    //Write the throttle_right_rear register value to the motor controller
    write_velocity_and_enable_MC(NODE_3, -registers.reg_map.throttle_right_rear * SCALE_FACTOR);
  
    //Write the throttle_left_rear register value to the motor controller
    write_velocity_and_enable_MC(NODE_4, registers.reg_map.throttle_left_rear * SCALE_FACTOR);
  }

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* UPDATE SENSOR spi_register ARRAYS with the latest readings if collecting_data flag is true (set true via command from Master)*/

  if (collecting_data) {
    
//Gather the IMU sensor data. These functions are from Adafruit_BNO055_ProgreSSIV.cpp

    //Used to store the I2C message containting the imu data
    uint8_t bno_buffer[6]; 
    
    //Send and I2C message to request the 6 bytes of EULER data
    bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_EULER, bno_buffer, 6);
    
    /* NOTE: ORDER OF IMU DATA IS DIFFERENT THAN IN THE ADAFRUIT PROVIDED FUNCTIONS. THIS IS BECAUSE IMU DATA IS COMING IN STRANGELY. X IS Z AND Z IS X I BELIEVE. 
     * SWITCHING THEM HERE AS WORK AROUND.
     */
    
    //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
    registers.reg_map.euler_z = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
    registers.reg_map.euler_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
    registers.reg_map.euler_x = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
    
    //Send and I2C message to request the 6 bytes of ACCELEROMETER data
    bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_ACCELEROMETER, bno_buffer, 6);
  
    //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
    registers.reg_map.accl_z = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
    registers.reg_map.accl_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
    registers.reg_map.accl_x = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
  
    //Send and I2C message to request the 6 bytes of GYROSCOPE data
    bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_GYROSCOPE, bno_buffer, 6);
  
    //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
    registers.reg_map.gyro_z = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
    registers.reg_map.gyro_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
    registers.reg_map.gyro_x = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
    
//Gather the steering and throttle inputs from the RADIO
    registers.reg_map.radio_steering = ST_in; //This value is an extern declared in input_handler.h
    registers.reg_map.radio_throttle = THR_in; //This value is an extern declared in input_handler.h

  }

}

/* END OF MAIN LOOP*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*INTERRUPT SERVICE ROUTINES*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Interrupt Service Routine to run the slave data transfer function call. Responds to the Masters request for a message.
void spi0_isr(void) {  
  
  volatile uint8_t SPI0_POPR_buf = SPI0_POPR;//Grab the SPI0_RXFR1 buffer value. This is the value that was in the push register during the TRANSFER PRIOR TO THAT WHICH CAUSED THIS INTERRUPT

  //If this is a new message, copy the registers into the register buffer for temporary use in the isr
  if (reg_buf_flag){
    reg_buf_flag = false;
//    isrStartTime = micros();
//    messageTime1 = micros();
    registers_buf = registers; //Grab the registers current values
  }
  if (address_flag){
    if(DEBUG_PRINT){
      Serial.println(); 
      Serial.print("--------");
      Serial.print(packet_cnt);
      Serial.println("---------"); 
    }
    address_flag = false;
    spi_address_buf = SPI0_POPR_buf & ADDRESS_MASK; //ANDs the shift register buffer value and the address mask (extract the 7 bit address from the first byte of the message)   
    spi_rw_bit = SPI0_POPR_buf & RW_MASK;//ANDs the shift register buffer value and the read/write bit mask (extract the MSB that tells whether this is a read or write message)
    
    if (DEBUG_PRINT){
      Serial.println("State 1:");
      Serial.print("\tAddr: ");
      Serial.println(spi_address_buf);
      Serial.print("\tReg: ");
      Serial.println(registers_buf.bytes[spi_address_buf]);
  //    spi_debug();
    }

    if (spi_rw_bit){//if the read/write bit is 1, it is a read message and spi_rw_buf will be true
      if (DEBUG_PRINT){
        Serial.println("State 2:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);  
      }
      
      SPI0_PUSHR_SLAVE = registers_buf.bytes[spi_address_buf];
      spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register
      
    } 
  }
  //Now not on the first interrupt anymore. This is the code that will run for all subsequent interrupts of a single message.
  else{
    
    if (spi_rw_bit & RW_MASK){//Message is a READ message
      if (DEBUG_PRINT){
        Serial.println("State 3:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);
        //spi_debug();
      }

        SPI0_PUSHR_SLAVE = registers_buf.bytes[spi_address_buf];
        spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register 

    }
    else {//Message is a WRITE message
      
        registers_buf.bytes[spi_address_buf] = SPI0_POPR_buf;
      if (DEBUG_PRINT){
        Serial.println("State 4:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);
        //spi_debug();     
      }

        spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register 
        
    }    
  }
//  isrEndTime = micros();
//  if(DEBUG_PRINT){
//    Serial <<"\tInterrupt Time: " << (isrEndTime-isrStartTime) << " Microseconds";
//    Serial.println();  
//    Serial.println();  
//  }

  SPI0_SR |= SPI_SR_RFDF;//Allow for another interrupt to occur.
    
} 

/* End spi0_isr */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Used to print some memory map information for debugging purposes. CTR tells the count of the double buffer TX1,2,3, and 4 and PTR tells which data in it is being pointed to*/
void spi_debug(void){
  Serial.print("\tCTR: ");
  Serial.println((SPI0_SR&(0b1111<<12))>>12);
  Serial.print("\tPTR: ");
  Serial.println((SPI0_SR&(0b1111<<8))>>8);
  Serial.print("\tTX0: ");
  //These are glimpses into data that is to be shifted out. What is in the double buffer to be sent into the shift registers 
  Serial.println(SPI0_TXFR0);
  Serial.print("\tTX1: ");
  Serial.println(SPI0_TXFR1);
  Serial.print("\tTX2: ");
  Serial.println(SPI0_TXFR2);
  Serial.print("\tTX3: ");
  Serial.println(SPI0_TXFR3);
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//Interrupt service routine for the rising edge of the chip enable pin. The end of every SPI message.
void spi_transfer_complete_isr(void) {

  reg_buf_flag = true;//Raises the new message flag so spi0_isr knows to load the register buffer
  address_flag = true;//Let spi0_isr know the address/rw byte was just sent
  
  if (DEBUG_PRINT){
    Serial.println("State 4a:");
    Serial.print("\tAddr: ");
    Serial.println(spi_address_buf);
    Serial.print("\tReg: ");
    Serial.println(registers_buf.bytes[spi_address_buf]); 
    spi_debug();   
  }

  SPI0_MCR |= (1<<11);//Clear the TX FIFO counter so that the buffer does not attempt to keep track of multiple spi messges. We are getting around the double buffer behavior 
                      //by only using the first byte of the buffer throughout the entire message.  
  SPI0_PUSHR_SLAVE = Teensy_Status_Byte;//This loads the push register with the status byte (well, it WILL be a Teensy status byte once implemented)

  registers = registers_buf;//Replace the registers with the updated values at the end of the message

  packet_cnt++;//For Debugging Purposes, print how many messages have been sent 

///* Timing Calculations */
//  //Calculate and Print the end of the 
//  message_delta_t = micros()- messageTime1;
//  
//  if (DEBUG_PRINT){
//    Serial.print("Message Time: ");
//    Serial.println(message_delta_t);    
//  }

}
/* End spi_transfer_complete_isr */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*FUNCTIONS*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void spi_slave_init(void){
  
    //Initialize spi slave object THE OLD WAY, USING T3SPI
  SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);

if(GENERAL_PRINT){
  Serial << "SPI0_MCR: ";
  Serial.println(SPI0_MCR,BIN);
}

//  /*Configure SPI Memory Map*/
//  SIM_SCGC6 |= SIM_SCGC6_SPI0;    // enable clock to SPI. THIS WAS MISSING PRIOR AND WOULD CAUSE CODE TO GET STUCK IN THIS FUNCTION
//  delay(1000);
////This clears the entire SPI0_MCR register. This will clear the MSTR bit (turn off master mode), clear the 
//  SPI0_MCR=0x00000000;
////THIS CLEARS THE ENTIRE SPI0_CTAR0 REGISTER (effectively clearing the default frame size which is 8 --> Not necessary as we want an 8 bit frame size)
//  SPI0_CTAR0=0;
////NEED TO FIGURE OUT WHAT THIS ONE IS DOING AND WHAT THE DIFFERENCE IS BETWEEN THIS AND THE ONE ABOVE IT
//  SPI0_CTAR0_SLAVE=0;
////This line sets the clock phase and clock polarity bits. Clock is inactive low (polarity) and the data is captured on the leading edge of SCK (phase)
//  SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | SPI_MODE0 << 25;
////THIS SETS THE BITS FOR FRAME SIZE (The value in this register plus one is the frame size. Want a single byte frame size. Master and slave in our system agree on this)
//  SPI0_CTAR0 |= SPI_CTAR_FMSZ(7);
////Request Select and Enable Register. Setting the RFDF_RE FIFO DRAIN REQUEST ENABLE Pin that allows interrupts or DMA to occur. The default method of draining
////the SPI hardware data register is interrupts. When a full 8 bits has been recieved an interrupt will be triggered (SPI0_ISR) and the data will be decoded. 
//  SPI0_RSER = 0x00020000;
////Enable the SCK, MISO, MOSI, and CS0 Pins (connections to the master device)
//  CORE_PIN13_CONFIG = PORT_PCR_MUX(2);//Serial Clock (SCK) pin
//  CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);//Master Output Slave Input (MOSI) pin
//  CORE_PIN12_CONFIG = PORT_PCR_MUX(2);//Master Input Slave Output (MISO) pin
//  CORE_PIN10_CONFIG = PORT_PCR_MUX(2);//Chip Select 0 (CS0) or Enable  pin
//  SPI0_MCR &= ~SPI_MCR_HALT & ~SPI_MCR_MDIS;//START
if(GENERAL_PRINT){
  Serial.println("Made it to end of spi_slave_init");//Code is currently not making it to this print statement
  delay(500); 
}


}

void spi_print(void){//This prints the name and address of each of the items in the register map along with the data stored in each register MUST UPDATE AS REGISTERS ARE ADDED
    Serial.println();
    Serial << "Register Map of Teensy";
    Serial.println();
    Serial.println();
    
    first_pointer = (uint32_t)&registers.reg_map;//Grab the address of the first register in the register map. (uint32_t) is a cast used to get the address to the correct type
      
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_0 - first_pointer;
//      Serial << "test_reg_0: ";       
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_0;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//      
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_1 - first_pointer;
//      Serial << "test_reg_1: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_1;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_2 - first_pointer;
//      Serial << "test_reg_2: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_2;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_3 - first_pointer;
//      Serial << "test_reg_3: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_3;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_4 - first_pointer;
//      Serial << "test_reg_4: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_4;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_5 - first_pointer;
//      Serial << "test_reg_5: ";
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_5;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_6 - first_pointer;
//      Serial << "test_reg_6: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_6;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//     next_pointer = (uint32_t)&registers.reg_map.test_reg_7 - first_pointer;
//      Serial << "test_reg_7: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_7;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_8 - first_pointer;
//      Serial << "test_reg_8: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_8;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 
//
//    next_pointer = (uint32_t)&registers.reg_map.test_reg_9 - first_pointer;
//      Serial << "test_reg_9: "; 
//      Serial.println(); 
//      Serial << " \t value = "<< registers.reg_map.test_reg_9;
//      Serial.println(); 
//      Serial << " \t index = " << next_pointer;
//      Serial.println();  
//      Serial.println(); 

//REFERENCE!! REPLACE EVERY TIME SOMETHING IS ADDED TO THE REGISTER MAP
//  volatile uint8_t print_registers;
//  volatile uint8_t begin_data_collection;
//  volatile uint8_t print_imu;
//  volatile uint8_t print_radio;
//  volatile uint8_t init_servo_radio;
//  volatile uint8_t init_motor_controllers;
//// Sensor/Data registers
//  // IMU 
//  volatile int16_t euler_x;
//  volatile int16_t euler_y;
//  volatile int16_t euler_z;
//  volatile int16_t accl_x;
//  volatile int16_t accl_y;
//  volatile int16_t accl_z;
//  volatile int16_t gyro_x;
//  volatile int16_t gyro_y;
//  volatile int16_t gyro_z;
//  //Servo and Radio 
//  volatile int16_t radio_throttle; 
//  volatile int16_t radio_steering;
//// Output/Actuation Registers
//  volatile int16_t throttle_right_front; 
//  volatile int16_t throttle_left_front; 
//  volatile int16_t throttle_right_rear; 
//  volatile int16_t throttle_left_rear; 
//  volatile int16_t servo_out;  
                                             
    next_pointer = (uint32_t)&registers.reg_map.print_registers - first_pointer;
      Serial << "print_registers: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.print_registers;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.begin_data_collection - first_pointer;
      Serial << "begin_data_collection: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.begin_data_collection;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.print_imu - first_pointer;
      Serial << "print_imu: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.print_imu;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


    next_pointer = (uint32_t)&registers.reg_map.print_radio - first_pointer;
      Serial << "print_radio: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.print_radio;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.init_servo_radio - first_pointer;
      Serial << "init_servo_radio: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.init_servo_radio;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.init_motor_controllers - first_pointer;
      Serial << "init_motor_controllers: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.init_motor_controllers;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


    next_pointer = (uint32_t)&registers.reg_map.euler_x - first_pointer;
      Serial << "euler_x: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.euler_x;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.euler_y - first_pointer;
      Serial << "euler_y: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.euler_y;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.euler_z - first_pointer;
      Serial << "euler_z: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.euler_z;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.accl_x - first_pointer;
      Serial << "accl_x: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.accl_x;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.accl_y - first_pointer;
      Serial << "accl_y: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.accl_y;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.accl_z - first_pointer;
      Serial << "accl_z: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.accl_z;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.gyro_x - first_pointer;
      Serial << "gyro_x: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.gyro_x;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.gyro_y - first_pointer;
      Serial << "gyro_y: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.gyro_y;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.gyro_z - first_pointer;
      Serial << "gyro_z: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.gyro_z;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


    next_pointer = (uint32_t)&registers.reg_map.radio_throttle - first_pointer;
      Serial << "radio_throttle: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.radio_throttle;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.radio_steering - first_pointer;
      Serial << "radio_steering: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.radio_steering;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


    next_pointer = (uint32_t)&registers.reg_map.throttle_right_front - first_pointer;
      Serial << "throttle_right_front: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.throttle_right_front;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.throttle_left_front - first_pointer;
      Serial << "throttle_left_front: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.throttle_left_front;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.throttle_right_rear - first_pointer;
      Serial << "throttle_right_rear: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.throttle_right_rear;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 
      
    next_pointer = (uint32_t)&registers.reg_map.throttle_left_rear - first_pointer;
      Serial << "throttle_left_rear: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.throttle_left_rear;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.servo_out - first_pointer;
      Serial << "servo_out: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.servo_out;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


      //Last messages frequency (hz)
      long message_f = 1/message_delta_t;
      Serial.print("Message Frequency Latest Sample ");
      Serial.println(message_f);

}

void print_imu_data(void){
  
      Serial << "euler_x: " << registers.reg_map.euler_x;
      Serial.println(); 
      Serial.println(); 

      Serial << "euler_y: " << registers.reg_map.euler_y;
      Serial.println();  
      Serial.println(); 

      Serial << "euler_z: " << registers.reg_map.euler_z;
      Serial.println();  
      Serial.println(); 
      
      Serial << "accl_x: " << registers.reg_map.accl_x;
      Serial.println();  
      Serial.println(); 

      Serial << "accl_y: " << registers.reg_map.accl_y;
      Serial.println();  
      Serial.println(); 

      Serial << "accl_z: " << registers.reg_map.accl_z;
      Serial.println();  
      Serial.println(); 
      
      Serial << "gyro_x: " << registers.reg_map.gyro_x;
      Serial.println();  
      Serial.println(); 

      Serial << "gyro_y: " << registers.reg_map.gyro_y;
      Serial.println();  
      Serial.println(); 


      Serial << "gyro_z: " << registers.reg_map.gyro_z;
      Serial.println();  
      Serial.println(); 
}

void print_radio_data(void){

      Serial << "radio_steering: " << registers.reg_map.radio_steering;
      Serial.println();  
      Serial.println(); 
      
      Serial << "radio_throttle: " << registers.reg_map.radio_throttle;
      Serial.println();  
      Serial.println(); 
}

