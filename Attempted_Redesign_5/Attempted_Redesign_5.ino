
/**
   Teensy_Firmware.ino


   Description: This file is the firmware on the TEENSY for the CALPOLY SSIV

   Date:                      April 26 2018
   Last Edit by:              Dominic Riccoboni

   Version Description:
                              -This Version is the fifth attempted restructure of the code to fit new design with Raspberry Pi firmware. Implemented complete restructure since
                              attempted restructure 4. Now there is a register map union whos memory can be accessed wither by a struct type or an array of bytes. The interrupt 
                              service routine has also been completely rethought. It now accepts an address byte on the first byte of a message, knows wether it is a read or 
                              write request, and has a logical structure that allows the master to write to as many addresses as desired in a single message (so long as they
                              are adjacent)

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
#include "Adafruit_BNO055.h"
#include "imumaths.h"


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Communication/SPI Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Instantiate T3SPI class as SPI_SLAVE WHEN AN SPI OBJECT WAS BEING CREATED BY T3SPI*/
T3SPI SPI_SLAVE;
///* SPI memory map setup definitions */
//#define SPI_MODE0     0x00//00 mode0, 01 mode1
//#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Spi Register Setup*/
//Create a register map to store read, write, and command data on the Teensy. Values are volatile because the register map is being accessed by spi0_isr 
typedef struct reg_struct {
//  //Test Registers
//  volatile int8_t test_reg_0;  
//  volatile int8_t test_reg_1;
//  volatile int8_t test_reg_2;
//  volatile int8_t test_reg_3;
//  volatile int8_t test_reg_4;
//  volatile int8_t test_reg_5;
//  volatile int8_t test_reg_6;
//  volatile int8_t test_reg_7;
//  volatile int8_t test_reg_8;
//  volatile int8_t test_reg_9;
//Commmand Registers
  volatile uint8_t print_registers;
  volatile uint8_t begin_data_collection;
  volatile uint8_t print_imu;
  volatile uint8_t print_radio;
  volatile uint8_t init_servo_radio;
//Read Registers
  //IMU Registers
  volatile int16_t euler_x;
  volatile int16_t euler_y;
  volatile int16_t euler_z;
  volatile int16_t accl_x;
  volatile int16_t accl_y;
  volatile int16_t accl_z;
  volatile int16_t gyro_x;
  volatile int16_t gyro_y;
  volatile int16_t gyro_z;
  //Servo and Radio Read Registers 
  volatile int16_t radio_steering_read;
  volatile int16_t radio_throttle_read; 
   
//Write Registers
  volatile int16_t throttle_all_write;  
  volatile int16_t servo_write;  
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
volatile uint8_t spi_rw_bit;//stores wether the master is sending a read or write message
#define RW_MASK 0b10000000 
#define ADDRESS_MASK 0b01111111

/*Spi Task/isr Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet. Initilize commands from master will be ignored if initialization has already occured
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been initialized
bool collecting_data = false; //Used by SPI task to start and stop data collection from sensors
bool reg_buf_flag = true;
bool address_flag = true;

/* Teensy Status Byte */
volatile uint8_t Teensy_Status_Byte = 69;


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

/* Steering and Throttle (both from radio) Preparation (These are externs found in input_handler and are updated in an interrupt service routine)*/
// instantiate variable for throttle input value (ranges from ~-500 to 500)
volatile int16_t THR_in;
// instantiate variable for steering input value (ranges from ~-500 to 500)
volatile int16_t ST_in;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*BNO055 Inertial Measurement Unit Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
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
//These are used to tell how much time the isr is taking to run
volatile long isrStartTime;
volatile long isrEndTime;
//These are used to tell how much time is elapsing between messages
volatile long messageTime1;
volatile long message_delta_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {

/*begin serial port operation*/
  Serial.begin(115200);
  while ( !Serial ) ;
  Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
  delay(500);
  
/*Initialize the SPI_slave device,register map, and interrupt service routines*/
  spi_slave_init();
//Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0); //CURRENTLY DONT KNOW WHY THIS IS ENABLING THE ISR
//Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0),spi_transfer_complete_isr,RISING);
//Initialize some of the starting conditions of the registers
  registers.reg_map.begin_data_collection = 1;//Set Begin Data Collection flag high
  registers.reg_map.print_imu = 0;//Control wether IMU data is printing or not
  registers.reg_map.init_servo_radio = 1;//Control wether the initialization code for the servo and radio will run
  registers.reg_map.print_radio = 0;//Control wether radio transeiver data is printing or not
//Print the registers at initialization
  spi_print();

/* Start Up the BNO055 IMU*/
Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
//Initialize the sensor
if(!bno.begin())
{
  //There was a problem detecting the BNO055 ... check your connections
  Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
  //while(1);
}
//Display the current IMU temperature
int8_t temp = bno.getTemp();
Serial.print("Current Temperature: ");
Serial.print(temp);
Serial.println(" C");
Serial.println("");
bno.setExtCrystalUse(true);
Serial.println("Calibration status values: 0 uncalibrated, 3 fully calibrated");

/*Startup CAN network*/
  //CANbus.begin();

}

void loop() {

  //CAN_message_t msg;//Dont know why this has to be at the beginning of void loop() but here it is

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

/*INIT_MOTOR_CONTROLLERS register*/   
//  //grab spi_register_array data for use by Teensy
//
//
//      //Initialize the motor controllers if asked to do so by Master and the on flag is false  
//      if (register_data == 1 && motor_controllers_on == false) {
//        //Run Initialize motor code if the register data is 1
//        ret = reset_nodes();
//        if (ret > 0)
//        {
//          error = ret;
//        }
//        delay(1000);
//
//        ret = initialize_CAN();
//        if (ret > 0)
//        {
//          error = ret;
//        }
//        delay(50);
//
//        ret = initialize_MC(NODE_1);
//        if (ret > 0)
//        {
//          error = ret;
//        }
//
//        process_available_msgs();
//        delay(100);
//        ret = initialize_MC(NODE_2);
//        if (ret > 0)
//        {
//          error = ret;
//        }
//        process_available_msgs();
//        delay(100);
//        ret = initialize_MC(NODE_3);
//        if (ret > 0)
//        {
//          error = ret;
//        }
//
//        process_available_msgs();
//        delay(100);
//        ret = initialize_MC(NODE_4);
//        if (ret > 0)
//        {
//          error = ret;
//        }
//
//        if (error == ERROR_CAN_WRITE)
//        {
//          delay(500);
//          stop_remote_node(NODE_1); //DOES THIS TURN OFF THE MOTOR DRIVERS?
//          stop_remote_node(NODE_2);
//          stop_remote_node(NODE_3);
//          stop_remote_node(NODE_4);
//
//          //NEED TO DEAL WITH ERROR CODE HERE. IF NO STARTUP THEN DO SOMETHING
//        }
//        else
//        {
//          motor_controllers_on = true;
//        }
//
//      }

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
  //Print live time IMU values
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
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array*/

/*throttle_all_write register*/
    //Send CAN message to update all motors with a the same torque setpoint

/*throttle_right_front_write register*/
    //Send CAN message to update right front motor torque setpoint

/*throttle_left_front_write register*/
    //Send CAN message to update left front motor torque setpoint

/*throttle_right_rear_write register*/
    //Send CAN message to update right rear motor torque setpoint

/*throttle_left_rear_write register*/
    //Send CAN message to update left rear motor torque setpoint

/*STEERING_WRITE register*/
    //Update the servo pwm value
    //writeServo(registers.steering);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* UPDATE SENSOR spi_register ARRAYS with the latest readings if collecting_data flag is true (set true via command from Master)*/

  if (collecting_data) {
    //collect and store every sensor value
    //The CAN messages for wheel velocity readings will be here. Data will be recieved and loaded into the corresponding spi_register.

    // Grab the IMU vector using I2C communication
    /*
    //IMU gravity - m/s^2 
    imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);  
    //IMU linear acceleration - m/s^2 
    imu::Vector<3> lin_accl = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);             
    //IMU magnetometer - uT
    imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);  
    */
    //IMU gyroscope - rad/s
    imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);  
    //IMU euler - degrees
    imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);  
    //IMU accelration - m/s^2 
    imu::Vector<3> accl = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
    //quaternion
    imu::Quaternion quat = bno.getQuat();

    //Gather the sensor data. These functions are from Adafruit_BNO055.cpp
    registers.reg_map.euler_x = euler.x(); //i2C call to IMU BNO to return x direction euler angle and place in the euler_x register
    registers.reg_map.euler_y = euler.y(); //i2C call to IMU BNO to return y direction euler angle and place in the euler_y register
    registers.reg_map.euler_z = euler.z(); //i2C call to IMU BNO to return z direction euler angle and place in the euler_z register
    registers.reg_map.accl_x = accl.x(); //i2C call to IMU BNO to return x direction acceleration and place in the euler_x register
    registers.reg_map.accl_y = accl.y(); //i2C call to IMU BNO to return y direction acceleration and place in the euler_y register
    registers.reg_map.accl_z = accl.z(); //i2C call to IMU BNO to return z direction acceleration and place in the euler_z register
    registers.reg_map.gyro_x = gyro.x(); //i2C call to IMU BNO to return x direction angular velocity and place in the gyro_x register
    registers.reg_map.gyro_y = gyro.y(); //i2C call to IMU BNO to return y direction angular velocity and place in the gyro_y register
    registers.reg_map.gyro_z = gyro.z(); //i2C call to IMU BNO to return z direction angular velocity and place in the gyro_z register

    //Gather the steering and throttle inputs from the RADIO
    registers.reg_map.radio_steering_read = ST_in; //This value is an extern declared in input_handler.h
    registers.reg_map.radio_throttle_read = THR_in; //This value is an extern declared in input_handler.h
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
    spi_rw_bit = SPI0_POPR_buf & RW_MASK;//ANDs the shift register buffer value and the read/write bit mask (extract the MSB that tells wether this is a read or write message)
    
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
  Serial.println("Made it to spi_slave_init");
  delay(500);
    //Initialize spi slave object THE OLD WAY, USING T3SPI
  SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);

  Serial << "SPI0_MCR: ";
  Serial.println(SPI0_MCR,BIN);
  
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
  Serial.println("Made it to end of spi_slave_init");//Code is currently not making it to this print statement
  delay(500);

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

    next_pointer = (uint32_t)&registers.reg_map.init_servo_radio - first_pointer;
      Serial << "init_servo_radio: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.init_servo_radio;
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

    next_pointer = (uint32_t)&registers.reg_map.radio_steering_read - first_pointer;
      Serial << "radio_steering_read: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.radio_steering_read;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 


    next_pointer = (uint32_t)&registers.reg_map.radio_throttle_read - first_pointer;
      Serial << "radio_throttle_read: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.radio_throttle_read;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.throttle_all_write - first_pointer;
      Serial << "throttle_all_write: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.throttle_all_write;
      Serial.println(); 
      Serial << " \t index = " << next_pointer;
      Serial.println();  
      Serial.println(); 

    next_pointer = (uint32_t)&registers.reg_map.servo_write - first_pointer;
      Serial << "servo_write: "; 
      Serial.println(); 
      Serial << " \t value = "<< registers.reg_map.servo_write;
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

      Serial << "radio_steering_read: " << registers.reg_map.radio_steering_read;
      Serial.println();  
      Serial.println(); 
      
      Serial << "radio_throttle_read: " << registers.reg_map.radio_throttle_read;
      Serial.println();  
      Serial.println(); 
}

