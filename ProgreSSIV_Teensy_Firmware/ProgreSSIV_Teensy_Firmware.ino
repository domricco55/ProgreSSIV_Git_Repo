
/**
   Teensy_Firmware.ino


   Description: This file is the firmware on the TEENSY for the CALPOLY SSIV

   Date:                      May 29 2018
   Last Edit by:              Dominic Riccoboni

   Version Description:
                              -

   Errors:                    -

   TO-DOs:
                              -

   Compiling[Y/N]:            Y


*/

#include "ProgreSSIV_CAN_driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"
//libraries for imu
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055_ProgreSSIV.h"
#include "imumaths.h"


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Interrupt and Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* SPI memory map setup definitions */
#define SPI_MODE0     0x00//00 mode0, 01 mode1
#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

///* Spi Register Setup*/
////Create a register struct to define data that will be read from, and written to over SPI. Values are volatile because the register map is being accessed during an interrupt
////service routine
typedef struct __attribute__ ((__packed__)) reg_struct {
  volatile uint8_t init_motor_controllers;
  volatile uint8_t reset_imu;//Will re-run the bno055 initialization code...the intitial conditions of the euler angle readings will change when you reset...may want to integrate this into the dead switch logic
  volatile uint8_t dead_switch;
  // IMU
  volatile int16_t euler_heading;
  volatile int16_t euler_roll;
  volatile int16_t euler_pitch;
  volatile int16_t accl_x;
  volatile int16_t gyro_x;
  volatile int16_t accl_y;
  volatile int16_t gyro_y;
  volatile int16_t accl_z;
  volatile int16_t gyro_z;
  //Servo and Radio
  volatile int16_t radio_throttle;
  volatile int16_t radio_steering;
  // Output/Actuation Registers
  volatile int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
  volatile int16_t servo_out;
  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
  volatile int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
  //CAN Motor Controller Commands
  volatile uint8_t shutdown_MCs;//Not yet implemented but will need to be at some point.
  //CAN Error Code Registers
  volatile uint8_t node_errors[4];//Array of node error messages
  //CAN Statusword Registers 
  volatile uint8_t node_statuswords[4];//Array of node statuswords
} reg_struct_t ;

//Union type definition linking the above reg_struct type to a 128 byte array. This will allow the same memory to be accessed by both the struct and the array. The above reg_struct_t defines names and types
//of variables that will be stored in the memory, or the "registers". The registers will be 128 bytes of memory that can be accessed in two different ways, one through the name as defined in the struct and
//another by simply indexing an array
typedef union __attribute__ ((__packed__)) reg_union {

  volatile uint8_t bytes[128];//Allocate 128 bytes of memory. The registers ARE these bytes.

  reg_struct_t reg_map; //Maps the 128 registers to data names and types as defined in the reg_struct above.

} reg_union_t;

reg_union_t registers;//Instantiate the register union (the registers will be filled with zeros by default)

/*
  can access exact same data like this:
    registers.bytes[1]
  OR like this:
    registers.reg_map.init_motor_controllers
*/


reg_union_t registers_buf = registers; //Create a register buffer of the same union type as registers. The registers get copied into registers_buf and remain there for the duration of an spi message. This is to prevent data from being corrupted
////if both spi task and spi0_isr attempt to alter the same register at the same time.

/* spi0_isr buffer related */
volatile uint8_t spi_address_buf;//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
volatile uint8_t spi_rw_bit;//stores the information of whether the master is sending a read or write message
#define RW_MASK 0b10000000
#define ADDRESS_MASK 0b01111111

/*Spi Task/isr Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet. Initilize commands from master will be ignored if initialization has already occured
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been started up
bool imu_on = false;//Used by SPI task to know if imu has already been started up
bool first_interrupt_flag = true;

/* Teensy Status Byte */
volatile uint8_t Teensy_Status_Byte = 25;//25 by default for now. NOT YET IMPLEMENTED CODE TO HANDLE A TEENSY STATUS BYTE.

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus/Motor Controller preparation (From uLaren_CAN_driver)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

/* Controlword values that drive the state transitions within the Device Control state machine. See EPOS4 Firmware Specification documentation for information on the controlword and state machine. */
#define SHUTDOWN_COMMAND 0x0006 //Controlword for shutdown. Takes the Device Control state machine from the "switch-on disabled" (post initialization state) to the "Ready to switch on" state. 
#define ENABLE_OP_COMMAND 0x000F //Controlword for switch on and enable. Puts Device Control state machine into "Operation enabled state" under MOST conditions. 
#define QUICKSTOP_COMMAND 0x000B //Controlword for Quick stop. Takes the Device Control state machine from the "Operation enabled" state to the "Quick stop active" state. The motors will decelerate to zero 
                                  //velocity at the quick stop deceleration value (index 0x6085). 
#define RESET_FAULT_COMMAND 0x0080 //Controlword for reset fault. Takes the Device Control state machine from the "fault" state to the "Switch on disabled state"
#define DISABLE_VOLTAGE_COMMAND 0x0000 //Controlword for disable voltage. Takes the Device Control state machine from the "quick stop active" state to the "Switch on disabled" state

/*CAN variables.*/
uint8_t ret = 0;
int16_t rpm_FR;//stores rpm of node 1 (Front Right wheel)
int16_t rpm_FL;//stores rpm of node 2 (Front Left wheel)
int16_t rpm_BR;//stores rpm of node 3 (Back Right wheel)
int16_t rpm_BL;//stores rpm of node 4 (Back Left wheel)
uint16_t statuswords[4];//stores statuswords locally
int32_t torque_write_error_cnt = 0;
int32_t torque_write_attempts = 0;


/* Motor Controller state machine setup */
enum MC_state{

  MC_state_0,  
  MC_state_1, 
  MC_state_2, 
  MC_state_3,
  MC_state_4,
  MC_state_5,
  MC_state_6,
  MC_state_7,
  MC_state_8,
  MC_state_9,
  MC_state_10,
  MC_state_11,
  MC_state_12
};

MC_state MC_state_var = MC_state_0; //First state to be entered

uint8_t bootup_count; 
uint8_t op_mode_SDO_count;
uint8_t inhibit_time_SDO_count;


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both for the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
volatile int16_t THR_in; // instantiate variable for throttle input value (ranges from ~-500 to 500)
volatile int16_t ST_in;  // instantiate variable for steering input value (ranges from ~-500 to 500)

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*BNO055 Inertial Measurement Unit Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Instantiate and initialize an Adafruit_BNO055 object. */
Adafruit_BNO055 bno = Adafruit_BNO055();

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Debugging/Printing setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define GENERAL_PRINT 1
#define CAN_FILTER_PRINT 1
#define PRINT_REGISTERS 0
#define PRINT_IMU 0
#define PRINT_RADIO 0
#define MC_CHECK_PRINT 0
#define SPI_DEBUG_PRINT 0

/*SPI Debugging Setup*/
// SPI Printing Related
uint32_t first_pointer;
uint32_t next_pointer;
uint8_t message_cnt = 0x01;


//These are used to tell how much time the isr is taking to run
volatile long isrStartTime;
volatile long isrEndTime;

//These are used to tell how much time is elapsing between messages
volatile long messageStartTime;
volatile long message_delta_t;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.

//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_print;
unsigned long start_time_motors;
unsigned long start_time_servo;
unsigned long start_time_quickstop;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* The setup function runs all start up functions. Any functions that are run only once, always, and at startup should go here. */
void setup() {

  /*begin serial port operation*/
  Serial.begin(115200);
  delay(3000);
  //while ( !Serial ) ;
  if (GENERAL_PRINT) {
    Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
    delay(500);
  }

  /* Initialize the radio and zervo at startup. Write a zero command to the servo.*/
  initPWMin();
  initServo();
  writeServo(0);

  /*Configure the Teensy for SPI Slave Mode, set some register map initial conditions, and initialize the interrupt service routines*/
  spi_slave_init();

  //Enable the spi0_isr interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0);

  //Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0), spi_transfer_complete_isr, RISING);

  //Set some of the starting conditions of the registers
  registers.reg_map.init_motor_controllers = 1;//Anything non-zero will cause the motor controllers (associated with the CAN Bus) to initialize in the SPI task
  registers.reg_map.dead_switch = 1;//Dead switch on or off?
  
//  registers.reg_map.servo_out = 0;//Set an initial servo position value. Just a visual que that servo is working at startup
  if (GENERAL_PRINT) {
    //Print the registers at initialization
    spi_registers_print();
  }

  //This code will cause the bno to initialize. If it did not, it will print the error message
  if (!bno.begin()) {
    if (GENERAL_PRINT) {
      //There was a problem detecting the BNO055 ... check your connections
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      //while(1);
    }
  }
  else {
    if (GENERAL_PRINT) {
      //Display the current IMU temperature
      int8_t temp = bno.getTemp();
      Serial.print("Current Temperature: ");
      Serial.print(temp);
      Serial.println(" C");
      Serial.println("");
      Serial.println("You may want to calibrate your bno055");
    }
    bno.setExtCrystalUse(true);
  }

  /*Startup CAN network (this is a FlexCAN function)*/
  Can0.begin(1000000); //void FlexCAN::begin (uint32_t baud, const CAN_filter_t &mask, uint8_t txAlt, uint8_t rxAlt)
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function. 
  uint8_t num_mailboxes = Can0.setNumTxBoxes(1); //Set the number of transmit mailboxes. There are 16 mailboxes available in the CAN hardware. Anything not used for transmitting will be used for receiving. If set to 1, strict in order transmission occurs
  if (GENERAL_PRINT){
    Serial.println();
    Serial.print("The number of CAN Tx Mailboxes is: ");
    Serial.println(num_mailboxes);
    Serial.println();
  }

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly.*/
void loop() {
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*SPI Task*/
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /*

      SPI TASK DESCRIPTION HERE

  */
  
  //Initialize all timing variables for the loop. 
  if (timing_init_flag) {
    // Initialize the Timing Variables so that there is a start time
    start_time_motors = micros();
    start_time_servo = micros();
    start_time_print = millis();
    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
    //start_time_voltage = millis();
    timing_init_flag = false;
  }

  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  
  unsigned long current_time_print = millis();
  if ((current_time_print - start_time_print) >= 10000)  //2000ms => 1/2 hz. All printing will happen at this frequency.
  {
    //Print the entire register map at the print frequency
    if(PRINT_REGISTERS){
      
      spi_registers_print();
      
    }
    
    //Print the IMU values only at the print frequency
    if (PRINT_IMU) {
      print_imu_data();
    }

    //Print only the registers associated with the radio athe the print frequency
    if (PRINT_RADIO) {
      print_radio_data();
    }

    if(MC_CHECK_PRINT){
      Serial.println();
      Serial.print("Statusword 1 = 0x");
      Serial.println(statuswords[0], HEX);
      Serial.print("Statusword 2 = 0x");
      Serial.println(statuswords[1], HEX);
      Serial.print("Statusword 3 = 0x");
      Serial.println(statuswords[2], HEX);
      Serial.print("Statusword 4 = 0x");
      Serial.println(statuswords[3], HEX);
      Serial.println();
  
//      Serial.println();
//      Serial.print("Error 1 = 0x");
//      Serial.println(registers.reg_map.node_errors[1], HEX);
//      Serial.print("Error 2 = 0x");
//      Serial.println(registers.reg_map.node_errors[2], HEX);
//      Serial.print("Error 3 = 0x");
//      Serial.println(registers.reg_map.node_errors[3], HEX);
//      Serial.print("Error 4 = 0x");
//      Serial.println(registers.reg_map.node_errors[4], HEX);
//      Serial.println();

      print_CAN_statistics();
    }


    start_time_print = current_time_print;
  }

  /*init_motor_controllers register signals this state machine to begin*/

  MC_state_machine();//The motor controller state machine is in this function. It will run every time through the loop


  /*reset_imu register*/
  //Run the imu initialization code from Adafruit_BNO055 library to reset the IMU readings
  if (registers.reg_map.reset_imu) {
    if (!bno.begin()) { //This code will cause the bno to initialize. If it did not, it will print the error message
      if (GENERAL_PRINT) {
        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); //Should likely add some error handling code here. Nothing to protect for this occurence.
      }
    }
    else {
      if (GENERAL_PRINT) {
        //Display the current IMU temperature
        int8_t temp = bno.getTemp();
        Serial.print("Current Temperature: ");
        Serial.print(temp);
        Serial.println(" C");
        Serial.println("");
        Serial.println("You may want to calibrate your bno055");
      }
    }
    registers.reg_map.reset_imu = 0;//Clear the register so that reset code does not run continuously.
  }

  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array. This code will send the most recent actuation to the approprate peripheral*/

  //Write the servo value from servo_out register
  writeServo(registers.reg_map.servo_out);
  
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* UPDATE SENSOR READINGS. This code will grab the latest sensor values and store them in the registers. */

  //Gather the IMU sensor data. These functions are from Adafruit_BNO055_ProgreSSIV.cpp

  uint8_t bno_buffer[6]; //Used to store the I2C message containting the imu data

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_EULER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of EULER data

  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
  registers.reg_map.euler_heading = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  registers.reg_map.euler_roll = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  registers.reg_map.euler_pitch = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_ACCELEROMETER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of ACCELEROMETER data

  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
  registers.reg_map.accl_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  registers.reg_map.accl_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  registers.reg_map.accl_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_GYROSCOPE, bno_buffer, 6); //Send and I2C message to request the 6 bytes of GYROSCOPE data

  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
  registers.reg_map.gyro_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  registers.reg_map.gyro_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  registers.reg_map.gyro_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

  //Gather the steering and throttle inputs from the RADIO
  registers.reg_map.radio_steering = ST_in; //This value is an extern declared in input_handler.h
  registers.reg_map.radio_throttle = THR_in; //This value is an extern declared in input_handler.h

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* CAN message filtering and error requests*/

  try_CAN_msg_filter();//Function in this script that checks for an available CAN message from the FlexCAN buffer and interprets it accordingly. Motor Controller wheel velocities, 
                        //statuswords, error messages, boot up messages, and so on are gathered here. This function also sets flags used in Motor Controller related state machines.  

}

/* END OF MAIN LOOP*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SERIAL PERIPHERAL INTERFACE (SPI) INTERRUPT SERVICE ROUTINES*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
  Teensy SPI Communication Protocol Description:

    spi0_isr handles the incoming bytes - or each frame - of an SPI message while spi_transfer_complete_isr prepares the code for recieving a new spi message
    once the current one is complete.

    An SPI message in this code consists of several one byte frames. The Master can send as many frames per message as it wants and there are two types of messages it can
    initiate with the Slave, a read message and a write message. These are mutually exclusive and which one is occurring is determined by the value of the MSB of the first
    byte recieved in a message, the Read/Write bit. The master sets this bit to 1 for reads and 0 for writes. This byte also contains in the remaining 7 bits the register
    address (a value between 0 an 127). This value indexes a register in the registers union that is to be read from or written to with SPI data. For example:

         0b10000001 -  This as the first frame of a message indicates that a read message is to follow and it should start at index 1 of the registers, i.e. registers.bytes[1].
                       This index currently points to the memory location of the "begin data collection" command flag, i.e. registers.reg_map.init_motor_controllers.

    The next frame the master sends will fill this memory location with data. Any subsequent frames will fill further registers with data, i.e. registers.bytes[2], registers.bytes[3]
    and so on. These may correspond to different commands, sensor readings, or actuation signals. In this iteration of the code, there is no protection agains writing to a read register
    but this is a recommended feature. Making some of the registers read only can prevent errors.

    Below is an outline of both a read message and a write message.
*/
/*
  If the read bit is high, the structure of the incoming message will behave like this:

    first incoming frame -> Teensy recieves register address of data_0 (Just prior to Interrupt 1)
    second incoming frame -> Teensy recieves junk (Just prior to Interrupt 2)
    third incoming frame -> Teensy recieves junk (Just prior to Interrupt 3)
    fourth incoming frame -> Teensy recieves junk (Just prior to Interrupt 4)
    fifth incoming frame -> Teensy recieves junk (Just prior to Interrupt 5) --> After the last spi0_isr interrupt (5), and immediately after the CS0 pin is brought high by MASTER, the Teensy
                                                                                   will enter the spi_transfer_complete_isr interrupt. There it will load the SPI0_PUSHR_SLAVE push register with the Teensy
                                                                                   status byte to be sent out in the next message (status byte handler code not yet implemented)
*/
/*
  If the read bit is set high, the structure of the outgoing message will look like this (there is a wasted byte due to the double buffering of the spi hardware registers):

    from registers.bytes[address] -> Teensy sends junk (Just prior to Interrupt 1)
    from registers.bytes[address+1] -> Teensy sends the Teensy_Status byte (Just prior to Interrupt 2)
    from registers.bytes[address+2] -> Teensy sends requested data 0 (Just prior to Interrupt 3)
    from registers.bytes[address+3] -> Teensy sends requested data 1 (Just prior to Interrupt 4)
    from registers.bytes[address+4] -> Teensy sends requested data 2 (Just prior to Interrupt 5)

  For more details on this process, including a graphical representation of this communnication protocol, please refer to the ProgreSSIV firmware documentation.

*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Interrupt Service Routine to run the slave data transfer function call. Responds to the Master's request for a message*/
void spi0_isr(void) {

  volatile uint8_t SPI0_POPR_buf = SPI0_POPR; //Use SPI0_POPR to read the R1 FIFO buffer value. This is the value that was just recieved in the spi shift register from Master.

  //If this is a new message, also decode the R/W bit and grab the address of the register to be accesses. These are both done with bit masks on the first byte of a message.
  if (first_interrupt_flag) {
    
    first_interrupt_flag = false;
    isrStartTime = micros();
    messageStartTime = micros();
    registers_buf = registers; //If this is a new message, copy the registers into the register buffer for temporary use in the isr
    
    if (SPI_DEBUG_PRINT) {
      Serial.println();
      Serial.print("--------");
      Serial.print(message_cnt);
      Serial.println("---------");
    }

    spi_address_buf = SPI0_POPR_buf & ADDRESS_MASK; //ANDs the shift register buffer value and the address mask (extract the 7 bit address from the first byte of the message)

    spi_rw_bit = SPI0_POPR_buf & RW_MASK; //ANDs the shift register buffer value and the read/write bit mask (extract the MSB that tells whether this is a read or write message)

    if (SPI_DEBUG_PRINT) {
      Serial.println("State 1:");
      Serial.print("\tAddr: ");
      Serial.println(spi_address_buf);
      Serial.print("\tReg: ");
      Serial.println(registers_buf.bytes[spi_address_buf]);
      spi_debug();
    }

    if (spi_rw_bit) { //if the read/write bit is 1, it is a read message and spi_rw_buf will be true
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 2:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);
      }

      SPI0_PUSHR_SLAVE = registers_buf.bytes[spi_address_buf];//Place the read message byte into the push register to be immediately placed in the T1 FIFO register. By the next 
                                                              //interrupt this value will have been placed in the shift register and by the one after that, it will have been shifted
                                                              //out to the Master device. The message from slave to master lags by two frames.

      spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register

    }
  }

  //NOW NOT ON THE FIRST INTERRUPT ANYMORE. This is the code that will run for all subsequent interrupts of a single spi message.
  else {

    if (spi_rw_bit & RW_MASK) { //Message is a READ message
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 3:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);
        spi_debug();
      }

      SPI0_PUSHR_SLAVE = registers_buf.bytes[spi_address_buf]; //Place the read message byte into the push register to be immediately placed in the T1 FIFO register. By the next 
                                                               //interrupt this value will have been placed in the shift register and by the one after that, it will have been shifted
                                                               //out to the Master device. The message from slave to master lags by two frames.

    }
    else {//Message is a WRITE message

      registers_buf.bytes[spi_address_buf] = SPI0_POPR_buf;
      
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 4:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers_buf.bytes[spi_address_buf]);
        spi_debug();
      }

    }
    
    spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register
    
  }
  
  isrEndTime = micros();
  if (SPI_DEBUG_PRINT) {
    Serial << "\tInterrupt Time: " << (isrEndTime - isrStartTime) << " Microseconds";
    Serial.println();
    Serial.println();
  }


  SPI0_SR |= SPI_SR_RFDF; //Setting the RFDF or "Recieve FIFO Drain Flag" bit in the SPI0_SR register low (this is cleared by writing a 1 to it) to let the SPI0 module know that all entries have
                          //been removed from the RXFIFO register. Not sure exactly why this needs to be done or if it is absolutely necessary. 

}

/* End spi0_isr */

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Used to print some memory map information for debugging purposes. This was used to debug the behavior of the TX FIFO buffer and better understand how it is working. */
void spi_debug(void) {
  Serial.print("\tCTR: ");
  Serial.println((SPI0_SR & (0b1111 << 12)) >> 12); // CTR tells the number of entries in the TX FIFO register
  Serial.print("\tPTR: ");
  Serial.println((SPI0_SR & (0b1111 << 8)) >> 8); //Grab the TX FIFO pointer value that tells which TX FIFO entry is to be transmitted during the next transfer
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

/*Interrupt service routine for the rising edge of the chip enable pin. This will occur at the end of every spi message. It resets flags, clears the microcontoller TX FIFO counter
  (by setting a bit in the SPI0_MCR register high) and loads the push register buffer with the Teensy status byte.   */
void spi_transfer_complete_isr(void) {

  first_interrupt_flag = true;//Raises the new message flag so spi0_isr knows to take the initial interrupt service routine actions of copying the register buffer, extracting the address 
                              //and extracting the R/W bits

  if (SPI_DEBUG_PRINT) {
    Serial.println("State 4a:");
    Serial.print("\tAddr: ");
    Serial.println(spi_address_buf);
    Serial.print("\tReg: ");
    Serial.println(registers_buf.bytes[spi_address_buf]);
    spi_debug();
  }

  SPI0_MCR |= (1 << 11);  //Clear the TX FIFO counter so that the Teensy Status Byte gets placed in the first location in the TX FIFO buffer. During the last interrupt, data was
                          //placed in TX FIFO to be placed in the shift register next. Since this data was not transfered into the shift register, the counter currently points to the 
                          //next location in TX FIFO. If we did not clear this counter, the Teensy Status Byte would be placed "in line behind" old junk data. This also helps get around 
                          //double buffering behavior of the SPI hardware by dissallowing TXFIFO from acting like a multiple frame buffer. 

  SPI0_PUSHR_SLAVE = Teensy_Status_Byte; //This loads the push register with the status byte. Currently status byte code is not implemented but perhaps it can be 8 bits that let the Master
  //know which sensors are currently on. There could be a task that sets the bits according to which peripheral-on flags are high or low.

  registers = registers_buf; //Replace the entire registers union with the updated values that the spi0_isr was storing in the registers buffer. Now Teensy has updated actuations or commands if any were just sent. 

  message_cnt++; //For SPI Debugging Purposes. If SPI_DEBUG_PRINT is true, then the packet count will be displayed at the beginning of each spi message/packet

  /* Timing Calculations */
  message_delta_t = micros() - messageStartTime; //Calculate the time the spi message took to occur from start to finish. Can be used to help diagnose performance/frequency issues

  if (SPI_DEBUG_PRINT) {
    Serial.print("Message Time: ");
    Serial.println(message_delta_t);
  }

}

/* End spi_transfer_complete_isr */

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*FUNCTIONS*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void spi_slave_init(void) {

  /*Configure SPI Memory Map*/
  SIM_SCGC6 |= SIM_SCGC6_SPI0;    // enable clock to SPI. THIS WAS MISSING PRIOR AND WOULD CAUSE CODE TO GET STUCK IN THIS FUNCTION
  delay(1000);

  SPI0_MCR |= SPI_MCR_HALT | SPI_MCR_MDIS; //While configuring memory map, halt spi functions

  SPI0_MCR = 0x00000000; //This clears the entire SPI0_MCR register. This will clear the MSTR bit (master mode is a 1 and slave mode is a 0)

  SPI0_CTAR0_SLAVE = 0; //Clears entire CTAR0 slave register

  SPI0_CTAR0 |= SPI_CTAR_FMSZ(7); //THIS SETS THE BITS FOR FRAME SIZE (The value in this register plus one is the frame size. Want a single byte frame size.
  //Master and slave in our system agree on this)

  SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | SPI_MODE0 << 25; //This line sets the clock phase and clock polarity bits. Clock is inactive low (polarity)
  //and the data is captured on the leading edge of SCK (phase). Configures CTAR0 Slave register

  SPI0_RSER = 0x00020000; //Request Select and Enable Register. Setting the RFDF_RE FIFO DRAIN REQUEST ENABLE Pin that allows interrupts or DMA to occur. The default method of draining
  //the SPI hardware data register is interrupts. When a full 8 bits (the frame size) has been recieved an interrupt will be triggered (SPI0_ISR) and the data will be decoded.

  //Enable the SCK, MISO, MOSI, and CS0 Pins (connections to the master device)
  CORE_PIN13_CONFIG = PORT_PCR_MUX(2); //Serial Clock (SCK) pin
  CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2); //Master Output Slave Input (MOSI) pin
  CORE_PIN12_CONFIG = PORT_PCR_MUX(2); //Master Input Slave Output (MISO) pin
  CORE_PIN10_CONFIG = PORT_PCR_MUX(2); //Chip Select 0 (CS0) or Enable  pin

  SPI0_MCR &= ~SPI_MCR_HALT & ~SPI_MCR_MDIS; //Resume spi functions

  if (GENERAL_PRINT) {
    Serial.println("Made it to end of spi_slave_init");
    delay(500);
    Serial << "SPI0_MCR: ";
    Serial.println(SPI0_MCR, BIN);
  }
}

void spi_registers_print(void) { //This prints the name and address of each of the items in the register map along with the data stored in each register MUST UPDATE AS REGISTERS ARE ADDED
  Serial.println();
  Serial << "Register Map of Teensy";
  Serial.println();
  Serial.println();

  first_pointer = (uint32_t)&registers.reg_map;//Grab the address of the first register in the register map. (uint32_t) is a cast used to get the address to the correct type

  next_pointer = (uint32_t)&registers.reg_map.init_motor_controllers - first_pointer;
  Serial << "init_motor_controllers: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.init_motor_controllers;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.reset_imu - first_pointer;
  Serial << "reset_imu: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.reset_imu;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.dead_switch - first_pointer;
  Serial << "dead_switch: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.dead_switch;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.euler_heading - first_pointer;
  Serial << "euler_heading: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.euler_heading;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.euler_roll - first_pointer;
  Serial << "euler_roll: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.euler_roll;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.euler_pitch - first_pointer;
  Serial << "euler_pitch: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.euler_pitch;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.accl_x - first_pointer;
  Serial << "accl_x: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.accl_x;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.gyro_x - first_pointer;
  Serial << "gyro_x: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.gyro_x;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.accl_y - first_pointer;
  Serial << "accl_y: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.accl_y;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.gyro_y - first_pointer;
  Serial << "gyro_y: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.gyro_y;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.accl_z - first_pointer;
  Serial << "accl_z: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.accl_z;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.gyro_z - first_pointer;
  Serial << "gyro_z: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.gyro_z;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();


  next_pointer = (uint32_t)&registers.reg_map.radio_throttle - first_pointer;
  Serial << "radio_throttle: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.radio_throttle;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.radio_steering - first_pointer;
  Serial << "radio_steering: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.radio_steering;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_torques[0] - first_pointer;
  Serial << "torque front right/node_torques[0]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_torques[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_torques[1] - first_pointer;
  Serial << "torque front left/node_torques[1]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_torques[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_torques[2] - first_pointer;
  Serial << "torques_back_right/node_torques[2]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_torques[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_torques[3] - first_pointer;
  Serial << "torque back left/node_torques[3]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_torques[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.servo_out - first_pointer;
  Serial << "servo_out: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.servo_out;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_rpms[0] - first_pointer;
  Serial << "rpm front right/node_rpms[0]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_rpms[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_rpms[1] - first_pointer;
  Serial << "rpm front left/node_rpms[1]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_rpms[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_rpms[2]- first_pointer;
  Serial << "rpm back right/node_rpms[2]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_rpms[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_rpms[3] - first_pointer;
  Serial << "rpm back left/node_rpms[3]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_rpms[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.shutdown_MCs - first_pointer;
  Serial << "shutdown_MCs: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.shutdown_MCs;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();
  
  next_pointer = (uint32_t)&registers.reg_map.node_errors[0] - first_pointer;
  Serial << "node_errors[0]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_errors[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_errors[1] - first_pointer;
  Serial << "node_errors[1]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_errors[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_errors[2] - first_pointer;
  Serial << "node_errors[2]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_errors[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_errors[3] - first_pointer;
  Serial << "node_errors[3]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_errors[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_statuswords[0] - first_pointer;
  Serial << "node_statuswords[0]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_statuswords[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println(); 

  next_pointer = (uint32_t)&registers.reg_map.node_statuswords[1] - first_pointer;
  Serial << "node_statuswords[1]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_statuswords[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println(); 

  next_pointer = (uint32_t)&registers.reg_map.node_statuswords[2] - first_pointer;
  Serial << "node_statuswords[2]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_statuswords[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.node_statuswords[3] - first_pointer;
  Serial << "node_statuswords[3]: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.node_statuswords[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();


  //REFERENCE!! REPLACE EVERY TIME SOMETHING IS ADDED TO THE REGISTER MAP
//  volatile uint8_t init_motor_controllers;
//  volatile uint8_t reset_imu;//Will re-run the bno055 initialization code...the intitial conditions of the euler angle readings will change when you reset...may want to integrate this into the dead switch logic
//  volatile uint8_t dead_switch;
//  // IMU
//  volatile int16_t euler_heading;
//  volatile int16_t euler_roll;
//  volatile int16_t euler_pitch;
//  volatile int16_t accl_x;
//  volatile int16_t gyro_x;
//  volatile int16_t accl_y;
//  volatile int16_t gyro_y;
//  volatile int16_t accl_z;
//  volatile int16_t gyro_z;
//  //Servo and Radio
//  volatile int16_t radio_throttle;
//  volatile int16_t radio_steering;
//  // Output/Actuation Registers
//  volatile int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
//  volatile int16_t servo_out;
//  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
//  volatile int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
//  //CAN Motor Controller Commands
//  volatile uint8_t shutdown_MCs;//Not yet implemented but will need to be at some point.
//  //CAN Error Code Registers
//  volatile uint8_t node_errors[4];//Array of node error messages
//  //CAN Statusword Registers 
//  volatile uint8_t node_statuswords[4];//Array of node statuswords

}

void print_imu_data(void) {

  Serial << "euler_heading: " << registers.reg_map.euler_heading;
  Serial.println();
  Serial.println();

  Serial << "euler_roll: " << registers.reg_map.euler_roll;
  Serial.println();
  Serial.println();

  Serial << "euler_pitch: " << registers.reg_map.euler_pitch;
  Serial.println();
  Serial.println();

  Serial << "accl_x: " << registers.reg_map.accl_x;
  Serial.println();
  Serial.println();

  Serial << "gyro_x: " << registers.reg_map.gyro_x;
  Serial.println();
  Serial.println();

  Serial << "accl_y: " << registers.reg_map.accl_y;
  Serial.println();
  Serial.println();

  Serial << "gyro_y: " << registers.reg_map.gyro_y;
  Serial.println();
  Serial.println();

  Serial << "accl_z: " << registers.reg_map.accl_z;
  Serial.println();
  Serial.println();

  Serial << "gyro_z: " << registers.reg_map.gyro_z;
  Serial.println();
  Serial.println();
}

void print_radio_data(void) {

  Serial << "radio_steering: " << ST_in;
  Serial.println();
  Serial.println();

  Serial << "radio_throttle: " << THR_in;
  Serial.println();
  Serial.println();
}

int16_t saturate_torque(int16_t torque_command)
{

  if (torque_command > 1000){ //Torque command is in units of [MotorRatedTorque/1000] and we want the max user input torque to be the max continutous torque, i.e. the rated torque. 

    torque_command = 1000; 
    
  }

  if (torque_command < -1000){
    torque_command = -1000;
  }

  return torque_command;
}

void try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and internal data and update the Teensy memory associated with that data or set a flag accordingly.
  CAN_message_t msg;// Struct defined in FlexCAN 
  if(Can0.read(msg))//If there was something to read, this will be true and msg will be filled with CAN data from the most recent read buffer value (FlexCAN function)
  {
    if(CAN_FILTER_PRINT){
      Serial.print("TRY_CAN_MSG_FILTER READ OCCURED, the id was: ");
      Serial.println(msg.id, HEX);
    }
    
    switch(msg.id){
      
      
      case 0x1A1: //If TxPDO1, node 1 (the motor velocity)
      
        rpm_FR = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 1. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
        registers.reg_map.node_rpms[0] = rpm_FR;
        
      break;

      case 0x1A2: //If TxPDO1, node 1 (the motor velocity)

        rpm_FL = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 2. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
        registers.reg_map.node_rpms[1] = rpm_FL;
        
      break;

      case 0x1A3: //If TxPDO1, node 1 (the motor velocity)

        rpm_BR = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 3. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
        registers.reg_map.node_rpms[2] = rpm_BR;
        
      break;

      case 0x1A4: //If TxPDO1, node 1 (the motor velocity)
      
        rpm_BL = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 4. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
        registers.reg_map.node_rpms[3] = rpm_BL;
          
      break;

      case 0x2A1: //If TxPDO2, node 1 (the statusword)
      
        statuswords[0] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 1, both high byte and low byte, and storing the whole 16 bit statusword locally.

        registers.reg_map.node_statuswords[0] = msg.buf[0]; // This is extracting the statusword value from TxPDO2 node 1 (High byte of the statusword is ignored here because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A2: //If TxPDO2, node 2 (the statusword)
      
        statuswords[1] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 2, both high byte and low byte, and storing the whole 16 bit statusword locally.
        
        registers.reg_map.node_statuswords[1] = msg.buf[0]; // This is extracting the statusword value from TxPDO2 node 2 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A3: //If TxPDO2, node 3 (the statusword)

        statuswords[2] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 3, both high byte and low byte, and storing the whole 16 bit statusword locally.
      
        registers.reg_map.node_statuswords[2] = msg.buf[0]; // This is extracting the statusword value from TxPDO2 node 3 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A4: //If TxPDO2, node 4 (the statusword )

        statuswords[3] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 4, both high byte and low byte, and storing the whole 16 bit statusword locally.

        registers.reg_map.node_statuswords[3] = msg.buf[0]; // This is extracting the statusword value from TxPDO2 node 4 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

      break;

      case 0x581: case 0x582: case 0x583: case 0x0584: //If Service Data Object from one of the nodes

        filter_SDO(msg); //This function will interpret the Service Data Object and act occordingly. A reference to the CAN message object is passed in

      break;

      case 0x701: case 0x702: case 0x703: case 0x704:
      
        if(msg.buf[0] == 0 && msg.buf[1] == 0 && msg.buf[2] == 0 && msg.buf[3] == 0 && msg.buf[4] == 0 && msg.buf[5] == 0 &&msg.buf[6] == 0 &&msg.buf[7] == 0){ //If Network Management (NMT) Boot Up message
         
          bootup_count++;
          
          if(CAN_FILTER_PRINT){
          Serial.println();
          Serial.println("Recieved a bootup confirmation");  
          Serial.println();
          print_CAN_message(msg);
          }  
        }
          

      break;
      
      default:

      if(CAN_FILTER_PRINT){
        Serial.println();
        Serial.print("A message was received during the try_CAN_msg_filter() function call that was not accounted for: ");
        Serial.println();
        print_CAN_message(msg);
      }
      
      break;
    }
  } 
}

void filter_SDO(CAN_message_t &msg){

  
  uint16_t object_index = (msg.buf[2] << 8 | msg.buf[1]); //Concatinate the high and low byte of the object dictionairy index of the recieved SDO message
  uint8_t command_specifier = msg.buf[0]; //Grab the command specifier of the recieved SDO message
  uint8_t node_id;
  
  switch (object_index){

    case 0x6040: //Controlword object dictionary index

    break;

    case 0x6041: //Statusword object dictionary index

        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_statuswords[node_id-1] = msg.buf[4]; //The first data byte of the SDO return message is the LSB of the Statusword for the node. For storage in SPI registers
        statuswords[node_id-1] = (uint16_t)(msg.buf[5] << 8 | msg.buf[4]); //Store the FULL 16 bit statusword for local Teensy use
        if(CAN_FILTER_PRINT){
          Serial.println("Recieved an SDO statusword response");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);  
        }

    break;

    case 0x6060: //Modes of operation object dictionary index

      if(command_specifier == 0x60){//If the SDO was an expedited write confirmation (command specifier of 0x60)
        
        op_mode_SDO_count++;
        
        if(CAN_FILTER_PRINT){
          Serial.println("Recieved an SDO operating mode write confirmation");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);
        }  
      }
        

        
    break;
//
//    case 0x1001: //Error register object dictionary index
//    
//      //if(command_specifier == 0x4B){//If the command specifier indicates that the message was a read dictionary object reply of 1 byte
//        
//        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
//        registers.reg_map.node_errors[node_id-1] = msg.buf[4]; //The first data byte of the SDO return message 
//        //error_flag = true;  
//        
//        if(CAN_FILTER_PRINT){
//          
//          Serial.println("Recieved an SDO error register response");  
//          Serial.println();
//          Serial.print("The COB-id was: ");
//          Serial.print(msg.id, HEX);
//          Serial.println(); 
//          Serial.print("The command specifier was: "); 
//          Serial.println(command_specifier, HEX);
//          Serial.print("The object index was: "); 
//          Serial.println(object_index, HEX);
//          Serial.println();
//          print_CAN_message(msg);
//        }  
//        
//     // }
//
//
//    break;

    case 0x1800:

      if((command_specifier == 0x60) && (msg.buf[3] == 0x03)){//If the SDO was an expedited write confirmation (command specifier of 0x60) AND the subindex was that of the inhibit time (3)
        
        inhibit_time_SDO_count++;
        
        if(CAN_FILTER_PRINT){
          
          Serial.println("Recieved an SDO TxPDO1 inhibit time write confirmation");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);
        }   
      }

    break;

    default:
    
      if(CAN_FILTER_PRINT){
        Serial.println();
        Serial.print("A message was received during the try_CAN_msg_filter() function call that was not accounted for: ");
        Serial.println();
        print_CAN_message(msg);
      }
      
      break;
  }
  
}

void MC_state_machine(){


/* MOTOR CONTROLLER STARTUP AND OPERATION STATE MACHINE*/

  //This tasks stack variables
  int32_t torque_actuate[4];
  unsigned long current_time_motors;
      
  switch(MC_state_var) {

    case MC_state_0: //Init

      bootup_count = 0; 
      op_mode_SDO_count = 0;
      inhibit_time_SDO_count = 0;
      
      ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
  
      if (GENERAL_PRINT) {
        Serial.println();
        Serial <<"reset_nodes() function call successfully wrote this many NMT commands:  "  << ret;
        Serial.println();
        Serial.println();
      }
      
      MC_state_var = MC_state_1;
      if(GENERAL_PRINT){
        Serial.println();
        Serial.println("Transitioning to MC_state_1");
        Serial.println();
      }
    
    break;

    case MC_state_1: //Wait for init MCs flag - SPI task has access to this flag

      if(bootup_count == 4){

        bootup_count = 0; //Make sure this is cleared BEFORE sending reset_communications command
        
        ret = reset_communications(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"reset_communications() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_2;
        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state2");
          Serial.println();
        }
      }
    
    break;

    case MC_state_2: //Wait for reset node complete - A bootup confirmation should be received from each node 
    
      if(registers.reg_map.init_motor_controllers && bootup_count==4){
        
        bootup_count = 0; 
        
        ret = enter_pre_operational(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"enter_pre_operational() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)

        ret = set_torque_operating_mode(); // Configure all nodes for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"set_torque_operating_mode() function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        registers.reg_map.init_motor_controllers = 0; //Can be made true again by writing to SPI register location

        MC_state_var = MC_state_3;
        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_3");
          Serial.println();
        }
      }


             
    
    break;

    case MC_state_3: //Wait for set torque mode Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(op_mode_SDO_count == 4){
        
        delayMicroseconds(10);
        ret = set_TxPDO1_inhibit_time(); //Set the TxPDO1 inhibit time for all nodes
         
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"set_TxPDO1_inhibit_time() function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        op_mode_SDO_count = 0;
        
        MC_state_var = MC_state_4;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_4");
          Serial.println();
        }
      }
    
    break;

    case MC_state_4: //Wait for set inhibit time Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(inhibit_time_SDO_count == 4){

        delayMicroseconds(10);
        ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
 
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"start_remote_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"start_remote_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        inhibit_time_SDO_count = 0;
        
        MC_state_var = MC_state_5;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_5");
          Serial.println();
        }
      }
    
    break;

    case MC_state_5: //Wait for remote nodes startup confirmation - the Statuswords of each node should indicate "Switch on disabled" device control state 

      if((uint8_t)statuswords[0] & (uint8_t)statuswords[1]  & (uint8_t)statuswords[2] & (uint8_t)statuswords[3] & 0b01000000){
        
        delayMicroseconds(10);
        ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND);
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_6;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_6");
          Serial.println();
        }
        
      }
    
    break;

    case MC_state_6: //Wait for "Ready to switch on" device control state - the Statuswords of each node will indicate state 

      if((uint8_t)statuswords[0] & (uint8_t)statuswords[1]  & (uint8_t)statuswords[2] & (uint8_t)statuswords[3] & 0b00100001){

        if(!registers.reg_map.dead_switch){//If the dead switch feature is off
          
          ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
          
          if (GENERAL_PRINT) {
            Serial.println();
            Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
            Serial.println();
            Serial.println();
          }

          MC_state_var = MC_state_7;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_7");
            Serial.println();
          }
        }

        else{//The dead switch feature is on
           
          MC_state_var = MC_state_8;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_8");
            Serial.println();
          }
        }
        
      }
    
    break;

    case MC_state_7: //Wait for "Operation enabled" device control state = the Statuswords of each node will indicate state 

      if(registers.reg_map.node_statuswords[0] & registers.reg_map.node_statuswords[1] & registers.reg_map.node_statuswords[2] & registers.reg_map.node_statuswords[3] & 0b00100111 ){

        registers.reg_map.node_torques[0] = 0;
        registers.reg_map.node_torques[1] = 0;
        registers.reg_map.node_torques[2] = 0;
        registers.reg_map.node_torques[3] = 0;

        torque_actuate[0] = 0;
        torque_actuate[1] = 0;
        torque_actuate[2] = 0;
        torque_actuate[3] = 0;

        MC_state_var = MC_state_9;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_9");
          Serial.println();
        }       
      }


    break;

    case MC_state_8: //Wait for throttle - the dead switch flag is true and waiting for user to pull the throttle on the radio transeiver 

      if( THR_in >= 200){
        
        ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_7;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_7");
          Serial.println();
        }
      }
    
    
    break;

    case MC_state_9: //"Operation enabled" device control state, actuate torque - Send out the torque actuations at a set frequency of about 180hz 
      
      current_time_motors = micros();
      if ((current_time_motors - start_time_motors) >= 5555)  //5,555 microseconds => 180hz. Motor torque setpoints will update at this frequency (this frequency should prevent buffer overruns on the nodes
      {
        //If SPI task ends up being a task with access to the MC state machine data, this chunk of code will not need to be here
        torque_actuate[0] = (int32_t)(-saturate_torque(registers.reg_map.node_torques[0])); //Front right wheel
        torque_actuate[1] = (int32_t)saturate_torque(registers.reg_map.node_torques[1]); //Front left wheel
        torque_actuate[2] = (int32_t)(-saturate_torque(registers.reg_map.node_torques[2])); //Back right wheel
        torque_actuate[3] = (int32_t)saturate_torque(registers.reg_map.node_torques[3]); //Back left wheel

        for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
          //Write saturated torque actuation values
          ret = RxPDO2_torque_write(node_id,torque_actuate[node_id-1]);
          
          if(!ret){
            torque_write_error_cnt++;
          }
          
          torque_write_attempts++;
        }

        start_time_motors = current_time_motors;
      }


      if(registers.reg_map.dead_switch){
        if(THR_in < 200){
        //If conditions for quickstop have been met

          if (GENERAL_PRINT){
            Serial.println();
            Serial.print("The Torque write error count was: ");
            Serial.println(torque_write_error_cnt);
            Serial.println();
            Serial.print("The Torque write attempt count was: ");
            Serial.println(torque_write_attempts);
            Serial.println();
          }
          torque_write_error_cnt = 0;
          torque_write_attempts = 0;
          
          //Write zero torque actuation values
          RxPDO2_torque_write(NODE_1, 0);
          RxPDO2_torque_write(NODE_2, 0);
          RxPDO2_torque_write(NODE_3, 0);
          RxPDO2_torque_write(NODE_4, 0);
          
          delayMicroseconds(10);
          
          ret = RxPDO1_controlword_write(QUICKSTOP_COMMAND); 
          
          if (GENERAL_PRINT) {
            Serial.println();
            Serial <<"RxPDO1_controlword_write(QUICKSTOP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
            Serial.println();
            Serial.println();
          }
          
          MC_state_var = MC_state_10;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_10");
            Serial.println();
          }
        }
      }
          
    break;

    case MC_state_10: //Wait for "Quickstop active" device control state - the Statuswords of each node will indicate state 
      
      if(statuswords[0] >> 8 & statuswords[1] >> 8 & statuswords[2] >> 8 & statuswords[3] >> 8 & 0b00000111 ){
      //If MCs have reached the "Quickstop active" device control state, transition
          
          MC_state_var = MC_state_11;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_11");
            Serial.println();
          }
      }

    break;

    case MC_state_11: //"Quickstop active" device control state - the dead switch flag is true and waiting for user to pull the throttle on the radio transeiver 

      if(THR_in >= 200){
        
        ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_7;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_7");
          Serial.println();
        }
      }
      
    break;
    
  }
}

