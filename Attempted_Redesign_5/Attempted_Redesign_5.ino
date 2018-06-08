
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

#include "uLaren_CAN_Driver.h"
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

/* Spi Register Setup*/
//Create a register struct to define data that will be read from, and written to over SPI. Values are volatile because the register map is being accessed during an interrupt
//service routine
typedef struct reg_struct {
  volatile uint8_t print_registers;
  volatile uint8_t begin_data_collection;
  volatile uint8_t print_imu;
  volatile uint8_t print_radio;
  volatile uint8_t init_servo_radio;
  volatile uint8_t init_motor_controllers;
  volatile uint8_t reset_imu;//Will re-run the bno055 initialization code
  //volatile uint8_t reset_teensy; //Not implemented yet but would set all initial conditions of the Teensy or perhaps hard reset the Teensy.
  volatile uint8_t dead_switch;
  // Sensor/Data registers
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
  volatile int16_t throttle_right_front;
  volatile int16_t throttle_left_front;
  volatile int16_t throttle_right_rear;
  volatile int16_t throttle_left_rear;
  volatile int16_t servo_out;
} reg_struct_t ;

//Union type definition linking the above reg_struct type to a 128 byte array. This will allow the same memory to be accessed by both the struct and the array. The above reg_struct_t defines names and types
//of variables that will be stored in the memory, or the "registers". The registers will be 128 bytes of memory that can be accessed in two different ways, one through the name as defined in the struct and
//another by simply indexing an array
typedef union reg_union {

  volatile uint8_t bytes[128];//Allocate 128 bytes of memory. The registers ARE these bytes.

  reg_struct_t reg_map; //Maps the 128 registers to data names and types as defined in the reg_struct above.

} reg_union_t;

reg_union_t registers;//Instantiate the register union (the registers will be filled with zeros by default)

/*
  can access exact same data like this:
    registers.bytes[1]
  OR like this:
    registers.reg_map.begin_data_collection
*/


reg_union_t registers_buf = registers; //Create a register buffer of the same union type as registers. The registers get copied into registers_buf and remain there for the duration of an spi message. This is to prevent data from being corrupted
//if both spi task and spi0_isr attempt to alter the same register at the same time.

/* spi0_isr buffer related */
volatile uint8_t spi_address_buf;//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
volatile uint8_t spi_rw_bit;//stores the information of whether the master is sending a read or write message
#define RW_MASK 0b10000000
#define ADDRESS_MASK 0b01111111

/*Spi Task/isr Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet. Initilize commands from master will be ignored if initialization has already occured
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been started up
bool imu_on = false;//Used by SPI task to know if imu has already been started up
bool collecting_data = false; //Used by SPI task to start and stop data collection from sensors
bool first_interrupt_flag = true;
//bool reg_buf_flag = true; //Lets spi0_isr know that a new message has begun and it should transfer registers into registers_buf
//bool address_flag = true;  //Lets spi0_isr know that a new message has begun and it should decode the R/W bit and the register address

/* Teensy Status Byte */
volatile uint8_t Teensy_Status_Byte = 25;//25 by default for now. NOT YET IMPLEMENTED CODE TO HANDLE A TEENSY STATUS BYTE.

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus preparation (From uLaren_CAN_driver)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

FlexCAN CANbus(1000000);

/* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

/*loop CAN variables.*/
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

/*SPI Debugging Setup*/
// SPI Printing Related
uint32_t first_pointer;
uint32_t next_pointer;
uint8_t message_cnt = 0x01;
#define SPI_DEBUG_PRINT 0

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
//unsigned long start_time_voltage;//Need to add in the voltage monitoring feature of the motor controllers. FUTURE WORK

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


  /*Configure the Teensy for SPI Slave Mode, set some register map initial conditions, and initialize the interrupt service routines*/
  spi_slave_init();

  //Enable the spi0_isr interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0);

  //Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0), spi_transfer_complete_isr, RISING);

  //Set some of the starting conditions of the registers
  //  registers.reg_map.begin_data_collection = 1;//Anything non-zero will cause the begin_data_collection flag to be set true in the SPI task
  //  registers.reg_map.init_servo_radio = 1;//Anything non-zero will cause the servo and radio initialization code to run in the SPI task
  //  registers.reg_map.init_motor_controllers = 1;//Anything non-zero will cause the motor controllers (associated with the CAN Bus) to initialize in the SPI task
  registers.reg_map.print_registers = 1;//Controls whether radio transeiver data is printing or not
  registers.reg_map.print_radio = 0;//Controls whether radio transeiver data is printing or not
  registers.reg_map.print_imu = 0;//Controls whether IMU data is printing or not
  registers.reg_map.servo_out = -500;//Set an initial servo position value. Just a visual que that servo is working at startup
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

  /*Startup CAN network*/
  CANbus.begin();

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly. This is where any finite state machine code may be placed.*/
void loop() {
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*SPI Task*/
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /*

      SPI TASK DESCRIPTION HERE

  */

  if (timing_init_flag) {
    // Initialize the Timing Variables so that there is a start time
    start_time_print = millis();
    start_time_motors = millis();
    start_time_servo = millis();
    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
    //start_time_voltage = millis();
    timing_init_flag = false;
  }

  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* COMMANDS. Master sends a non-zero value if it wants the peripheral to be initialized, data collection to start, or some other command to run*/

  /*begin_data_collection register*/
  if (registers.reg_map.begin_data_collection && !collecting_data ) {

    collecting_data = true;

  }

  /*print command registers (ONLY USE THIS FOR DEBUGGING AND NOT FOR DYNAMIC OPERATION, MAY CAUSE BUGS TO OCCUR OTHERWISE)*/
  
  //Print the entire register map
  if (registers.reg_map.print_registers) {
    spi_registers_print();
    registers.reg_map.print_registers = 0; //Clear the flag register so that the printing only occurs once. Master must write to this each time it wants the register map to print. 
  }
  
  unsigned long current_time_print = micros();
  if ((current_time_print - start_time_print) >= 100000)  //100ms => 10hz. All printing will happen at this frequency.
  {
    //If Master wants Teensy to print it will send a non-zero value to the address for the print command and its code will run

    //Print the IMU values only
    if (registers.reg_map.print_imu) {
      print_imu_data();
    }

    //Print only the registers associated with the radio
    if (registers.reg_map.print_radio) {
      print_radio_data();
    }

  }


  /*init_servo_radio register*/
  //Initialize the servo and radio if asked to do so by Master and the on flag is false
  if (registers.reg_map.init_servo_radio && !servo_radio_on) {
    initPWMin();
    initServo();
    servo_radio_on = true;
  }

  /*init_motor_controllers register*/
  //Initialize the motor controllers if asked to do so by Master (non zero value sent to the init_motor_controllers register) and the motor_controllers_on flag is false
  if (registers.reg_map.init_motor_controllers && !motor_controllers_on) {

    //Run the function that sends the CAN message for reseting the nodes. Ret is what is returned during the CAN message
    ret = reset_nodes();
    if (ret > 0)
    {
      error = ret;
    }
    delay(1000);
    ret = initialize_CAN(); //Run the function that sends the CAN message for initializing CAN. Ret is what is returned during the CAN message
    if (ret > 0)
    {
      error = ret;
    }
    delay(50);
    ret = initialize_MC(NODE_1); //Run the function that sends the CAN message for initializing motor controller node 1. Ret is what is returned during the CAN message
    if (ret > 0)
    {
      error = ret;
    }
    process_available_msgs(); //A uLaren_CAN_Driver function that prints a recieved CAN message I believe. Not really certain.
    delay(100);
    ret = initialize_MC(NODE_2); //Run the function that sends the CAN message for initializing motor controller node 2. Ret is what is returned during the CAN message
    if (ret > 0)
    {
      error = ret;
    }
    process_available_msgs(); //A uLaren_CAN_Driver function that prints a recieved CAN message I believe.
    delay(100);
    ret = initialize_MC(NODE_3); //Run the function that sends the CAN message for initializing motor controller node 3. Ret is what is returned during the CAN message
    if (ret > 0)
    {
      error = ret;
    }
    process_available_msgs(); //A uLaren_CAN_Driver function that prints a recieved CAN message I believe.
    delay(100);
    ret = initialize_MC(NODE_4); //Run the function that sends the CAN message for initializing motor controller node 4. Ret is what is returned during the CAN message
    if (ret > 0)
    {
      error = ret;
    }
    if (error == ERROR_CAN_WRITE)  //If one or more of the attempted initializations returned an ERROR_CAN_WRITE, then stop all motor controllers from operating and
      //for now, do nothing and exit. I NEED TO CHANGE WHAT HAPPENS HERE!!! Before there were some printed errors and such but not sure
    {
      delay(500);
      //If there is an error, stop the motor controller nodes. Not sure yet of the details of this function. Explore the uLaren CAN driver files and MAXON CANopen firmware specification documentation to figure this out.
      stop_remote_node(NODE_1);
      stop_remote_node(NODE_2);
      stop_remote_node(NODE_3);
      stop_remote_node(NODE_4);

      delay(500);
      process_available_msgs(); //This function "process_available_msgs() may be printing CAN errors if they have occured but not certain. uLaren would know.
      //NEED TO DEAL WITH ERROR CODE HERE. IF NO STARTUP THEN DO SOMETHING
      error = 0;
    }
    else
    {
      motor_controllers_on = true; //Lets Teensy know the motor controllers have already been turned on

      registers.reg_map.init_motor_controllers = 0; //Clears the register so that this command can be sent again later. The command still wont do anything if the motor_controllers_on flag is true but this flag can be set false
      //in motor controller shut off code. Shut off code has not currently been implemented.

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
      write_velocity_and_enable_MC(NODE_1, 0 ); //Write the throttle_right_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_2, 0 ); //Write the throttle_left_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_3, 0); //Write the throttle_right_rear register value to the motor controller

      write_velocity_and_enable_MC(NODE_4, 0); //Write the throttle_left_rear register value to the motor controller
    }
  }

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

  // Dead man's switch.  If throttle is not at full(ish) forward the car should come to a halt. There is a dead switch already implemented in Simulink but that one is
  //for redundancy.
  if (registers.reg_map.dead_switch) {
    if ( THR_in > 200 ) {

      write_velocity_and_enable_MC(NODE_1, -registers.reg_map.throttle_right_front); //Write the throttle_right_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_2, registers.reg_map.throttle_left_front); //Write the throttle_left_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_3, -registers.reg_map.throttle_right_rear); //Write the throttle_right_rear register value to the motor controller

      write_velocity_and_enable_MC(NODE_4, registers.reg_map.throttle_left_rear); //Write the throttle_left_rear register value to the motor controller
    }
    else {

      write_velocity_and_enable_MC(NODE_1, 0); //Write the throttle_right_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_2, 0); //Write the throttle_left_front register value to the motor controller

      write_velocity_and_enable_MC(NODE_3, 0); //Write the throttle_right_rear register value to the motor controller

      write_velocity_and_enable_MC(NODE_4, 0); //Write the throttle_left_rear register value to the motor controller

      //Write zeros to the registers so that next time the trigger is pressed, the actuation is zero unless overriden by the Master device.
      registers.reg_map.throttle_right_front = 0;
      registers.reg_map.throttle_left_front = 0;
      registers.reg_map.throttle_right_rear = 0;
      registers.reg_map.throttle_left_rear = 0;
    }
  }

  //If the dead man's switch is turned off, just update the motor controllers immediately.
  else {

    write_velocity_and_enable_MC(NODE_1, -registers.reg_map.throttle_right_front); //Write the throttle_right_front register value to the motor controller

    write_velocity_and_enable_MC(NODE_2, registers.reg_map.throttle_left_front); //Write the throttle_left_front register value to the motor controller

    write_velocity_and_enable_MC(NODE_3, -registers.reg_map.throttle_right_rear); //Write the throttle_right_rear register value to the motor controller

    write_velocity_and_enable_MC(NODE_4, registers.reg_map.throttle_left_rear); //Write the throttle_left_rear register value to the motor controller

  }

  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* UPDATE SENSOR READINGS. This code will grab the latest sensor values and store them in the registers if collecting_data is true. */

  if (collecting_data) {

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

  }

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

         ob10000001 -  This as the first frame of a message indicates that a read message is to follow and it should start at index 1 of the registers, i.e. registers.bytes[1].
                       This index currently points to the memory location of the "begin data collection" command flag, i.e. registers.reg_map.begin_data_collection.

    The next frame the master sends will fill this memory location with data. Any subsequent frames will fill further registers with data, i.e. registers.bytes[2], registers.bytes[3]
    and so on. These may correspond to different commands, sensor readings, or actuation signals. In this iteration of the code, there is no protection agains writing to a read register
    but this is a recommended feature. Making some of the registers read only can prevent errors.

    Below is an outline of both a read message and a write message.
*/
/*
  If the read bit is high, the structure of the incoming message will behave like this:

    first incoming message -> Teensy recieves register address of data_0 (Just prior to Interrupt 1)
    second incoming message -> Teensy recieves junk (Just prior to Interrupt 2)
    third incoming message -> Teensy recieves junk (Just prior to Interrupt 3)
    fourth incoming message -> Teensy recieves junk (Just prior to Interrupt 4)
    fifth incoming message -> Teensy recieves junk (Just prior to Interrupt 5) --> After the last spi0_isr interrupt (5), and immediately after the CS0 pin is brought high by MASTER, the Teensy
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
  }
  
  isrEndTime = micros();
  if (SPI_DEBUG_PRINT) {
    Serial << "\tInterrupt Time: " << (isrEndTime - isrStartTime) << " Microseconds";
    Serial.println();
    Serial.println();
  }

  spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register

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

  //REFERENCE!! REPLACE EVERY TIME SOMETHING IS ADDED TO THE REGISTER MAP

  //  volatile uint8_t print_registers;
  //  volatile uint8_t begin_data_collection;
  //  volatile uint8_t print_imu;
  //  volatile uint8_t print_radio;
  //  volatile uint8_t init_servo_radio;
  //  volatile uint8_t init_motor_controllers;
  //  volatile uint8_t reset_imu;
  //  //volatile uint8_t reset_teensy; //Not implemented yet but would set all initial conditions of the Teensy or perhaps hard reset the Teensy.
  //  volatile uint8_t dead_switch;
  //// Sensor/Data registers
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
  //// Output/Actuation Registers
  //  volatile int16_t throttle_right_front;
  //  volatile int16_t throttle_left_front;
  //  volatile int16_t throttle_right_rear;
  //  volatile int16_t throttle_left_rear;
  //  volatile int16_t servo_out;

  next_pointer = (uint32_t)&registers.reg_map.print_registers - first_pointer;
  Serial << "print_registers: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.print_registers;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.begin_data_collection - first_pointer;
  Serial << "begin_data_collection: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.begin_data_collection;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.print_imu - first_pointer;
  Serial << "print_imu: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.print_imu;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();


  next_pointer = (uint32_t)&registers.reg_map.print_radio - first_pointer;
  Serial << "print_radio: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.print_radio;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.init_servo_radio - first_pointer;
  Serial << "init_servo_radio: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.init_servo_radio;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

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

  //    next_pointer = (uint32_t)&registers.reg_map.reset_teensy - first_pointer;
  //      Serial << "reset_teensy: ";
  //      Serial.println();
  //      Serial << " \t value = "<< registers.reg_map.reset_teensy;
  //      Serial.println();
  //      Serial << " \t index = " << next_pointer;
  //      Serial.println();
  //      Serial.println();

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


  next_pointer = (uint32_t)&registers.reg_map.throttle_right_front - first_pointer;
  Serial << "throttle_right_front: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.throttle_right_front;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.throttle_left_front - first_pointer;
  Serial << "throttle_left_front: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.throttle_left_front;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.throttle_right_rear - first_pointer;
  Serial << "throttle_right_rear: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.throttle_right_rear;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers.reg_map.throttle_left_rear - first_pointer;
  Serial << "throttle_left_rear: ";
  Serial.println();
  Serial << " \t value = " << registers.reg_map.throttle_left_rear;
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


  //Last messages frequency (hz)
  long message_f = 1 / message_delta_t;
  Serial.print("Message Frequency Latest Sample ");
  Serial.println(message_f);

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

  Serial << "radio_steering: " << registers.reg_map.radio_steering;
  Serial.println();
  Serial.println();

  Serial << "radio_throttle: " << registers.reg_map.radio_throttle;
  Serial.println();
  Serial.println();
}

