
/**
   Teensy_Firmware.ino


   Description: This file is the firmware on the TEENSY for the CALPOLY SSIV

   Date:                      April 20 2018
   Last Edit by:              Dominic Riccoboni

   Version Description:
                              -This Version is the fourth attempted restructure of the code to fit new design with Raspberry Pi firmware

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

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Communication/SPI Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Instantiate T3SPI class as SPI_SLAVE*/
T3SPI SPI_SLAVE;

/* Volatiles used by spi0_isr interrupt service routine*/
volatile uint8_t current_register = 0; //this is set in interrupt.  The current register is the register address that the latest spi message from the Master (well, once the second byte has sent this is true).
volatile uint8_t spi_data_index = 0; //this allows the isr to know when the full message (4 bytes) has been recieved

/*This sets the amount of bytes in an SPI message (agreed upon by Master and Slave).*/
#define dataLength  4

/*SPI INCOMING Data Array Buffer. An incoming Master SPI Message will trigger an interrupt service routine that grabs the message.
  An incoming SPI message will have dataLength many bytes and be stored in the data[] array buffer. Only the Master can trigger an SPI interrupt.*/
volatile uint8_t data[dataLength] = {}; //<--- SPI INCOMING Data is stored here in the interrupt service routine
/*SPI Default Outgoing Data Array. This is the data array that will be sent as the data from the Master is coming in. Sending and recieving happen simultaneously.*/
volatile uint8_t default_data_read[dataLength] = {};


/*Register addresses (or more accurately, the index of the address of the register) for SPI Communication (Agreed Upon by Master and Slave to refer to a specific sensor reading, actuation, or command) */
/* Commands from Master*/
#define INIT_STEERING_THROTTLE 1
#define INIT_MOTOR_CONTROLLERS 2
#define BEGIN_DATA_COLLECTION 3
#define SERIAL_PRINT_REGISTERS 4
/* Master Requests These Readings*/
#define RADIO_STEERING_READ 101 //Radio steering input from user
#define RADIO_THROTTLE_READ 102 //Radio throttle input from user
#define RIGHT_FRONT_VELOCITY_READ 103 //Rotational velocity of right front wheel
#define LEFT_FRONT_VELOCITY_READ 104 //Rotational velocity of left front wheel
#define RIGHT_REAR_VELOCITY_READ 105 //Rotational velocity of right rear wheel
#define LEFT_REAR_VELOCITY_READ 106 //Rotational velocity of left rear wheel
/* Master Sends These Actuations (none but the actuators should be addressed over 200)*/
#define THROTTLE_ALL_WRITE 201
#define THROTTLE_RIGHT_FRONT_WRITE 202
#define THROTTLE_LEFT_FRONT_WRITE  203
#define THROTTLE_RIGHT_REAR_WRITE  204
#define THROTTLE_LEFT_REAR_WRITE   205
#define STEERING_WRITE 206

/*SPI registers preparation*/
volatile uint8_t *spi_register_array[256];//An array of pointers to the spi register arrays (example is the initial array below)

/* Used to grab data from spi_register_array and concatinate it into one 16 bit integer*/
uint8_t register_data_low_byte = 0;
uint8_t register_data_high_byte = 0;
int16_t register_data = 0;

/* Defines a placeholder return data array that will be written to by code in spi task and then loaded into its corresponding spi_register_array register.
The next time the Master sends a message to that register address, the master will recieve the return message*/
uint8_t return_array[dataLength] = {255,255,255,255};

/*Spi Task Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been initialized
bool collecting_data = false; //Used by SPI task to start and stop data collection from sensors

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
/*Local Teensy Variables (Where Teensy temporarily stores data recieved via peripherals, SPI, I2C, Analog, etc.)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//"Out" and "In" from perspective of the Teensy
///*Write (actuation) variables (where SPI data from Master is stored. These variables are for the most part immediately used in a CAN message to the motor controllers)*/
//int16_t throttle_out_RF = 0;
//int16_t throttle_out_LF = 0;
//int16_t throttle_out_RR = 0;
//int16_t throttle_out_LR = 0;
//int16_t steer_angle_out = 0;
/*Read (sensor/measurement) variables (where messages recieved via function calls to sensor objects is stored)*/
int16_t radio_steering_in = 0;
int16_t radio_throttle_in = 0;
int16_t velocity_in_RF = 0;
int16_t velocity_in_LF = 0;
int16_t velocity_in_RR = 0;
int16_t velocity_in_LR = 0;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Debugging setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//"Adding streaming (insertion-style) Output" from playground.arduino.cc
//Allows Serial << "This is an insertion-style message" type operation
template<class T> inline Print &operator <<(Print &obj, T arg) { obj.print(arg); return obj;}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void setup() {

/*begin serial port operation*/
  Serial.begin(115200);
  Serial.println("Hello user. I am your debugging assistant. You make call me TeensyTron5000.");
  
/*Initialize SPI communication*/
  //Initialize spi slave object
  SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0);
  //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
  SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);
  //Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0); //CURRENTLY DONT KNOW WHY THIS IS ENABLING THE ISR
  
  //Populate status array so that there is no segmentation fault later on when an index that hasn't been populated is called. 
  //This code allocates 256 four byte memory arrays and makes sure that *spi_register[i] is a pointer to the ith array */
  int i;
  for (i = 0; i < 256; i++) {
    spi_register_array[i] = return_array;
  }
  //This code initializes the command arrays so that the deffault data (high and low byte concatinated) is zero. It needs to be zero so that the peripherals are guaranteed
  //to not initialize upon powering up of the Teensy. 
  return_array [2] = 0; //Low byte zero
  return_array [3] = 0; //High byte zero
  spi_register_array[INIT_STEERING_THROTTLE] = return_array;
  spi_register_array[INIT_MOTOR_CONTROLLERS] = return_array;
  spi_register_array[BEGIN_DATA_COLLECTION] = return_array;
  
/*Startup CAN network*/
  CANbus.begin();

}

void loop() {

  CAN_message_t msg;//Dont know why this has to be at the beginning of void loop() but here it is

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Task*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
  /*
  * Each element in spi_register_array is 1 byte.  Therefore 4 bytes per packet.  The array shows up on Simulink end as one message packet.  
  * structure if spi arrays for outgoing data:
  * spi_register_array[0] -> register address of that data
  * spi_register_array[1] -> low byte of data (only relevant for READS)
  * spi_register_array[2] -> high byt of data (only relevant for READS)
  * spi_register_array[3] -> status of teensy (slave)
  */

  /* 
  * structure if spi arrays for incoming data:
  * spi_register_array[0] -> Master status byte
  * spi_register_array[1] -> spi_register_array register address 
  * spi_register_array[2] -> low byte of data (only relevant for READS)
  * spi_register_array[3] -> high byt of data (only relevant for READS)
  */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* COMMANDS Master sends a 1 if it wants the peripheral to be initialized or data collection to start*/

/*INIT_STEERING_THROTTLE register*/
  //grab spi_register_array data for use by Teensy
  spi_register_array[INIT_STEERING_THROTTLE][1] = register_data_low_byte;
  spi_register_array[INIT_STEERING_THROTTLE][2] = register_data_high_byte;
  register_data = (register_data_low_byte << 8 | register_data_high_byte);
  
//    //Initialize the servo and radio if asked to do so by Master and the on flag is false    
//      if (register_data == 1 && servo_radio_on == false ) {
//        initPWMin();
//        initServo();
//        servo_radio_on = true;
//        //return_array [0] = INIT_STEERING_THROTTLE; //Can alter the return array element-wise before updating the spi register with (not doing this now) 
//        spi_register_array[INIT_STEERING_THROTTLE] = return_array ;//Can let Master Know they have been initialized (this is what will be returned during the next spi message)
//      }

/*INIT_MOTOR_CONTROLLERS register*/   
  //grab spi_register_array data for use by Teensy
  spi_register_array[INIT_MOTOR_CONTROLLERS][1] = register_data_low_byte;
  spi_register_array[INIT_MOTOR_CONTROLLERS][2] = register_data_high_byte;
  register_data = (register_data_low_byte << 8 | register_data_high_byte);

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
//          //return_array [0] = INIT_MOTOR_CONTROLLERS; //Can alter the return array element-wise before updating the spi register with it. For the controllers, the return message could be a confirmation
//          spi_register_array[INIT_MOTOR_CONTROLLERS] = return_array ;//Can let Master Know they have been initialized (this is what will be returned during the next spi message)
//        }
//
//      }

/*BEGIN_DATA_COLLECTION register*/   
  //grab spi_register_array data for use by Teensy
  spi_register_array[BEGIN_DATA_COLLECTION][1] = register_data_low_byte;
  spi_register_array[BEGIN_DATA_COLLECTION][2] = register_data_high_byte;
  register_data = (register_data_low_byte << 8 | register_data_high_byte);
  
  if (collecting_data == false){
    
    collecting_data = true;
    
    //return_array [0] = BEGIN_DATA_COLLECTION; //Can alter the return array element-wise before updating the spi register with it. For the controllers, the return message could be a confirmation
    spi_register_array[INIT_MOTOR_CONTROLLERS] = return_array ;//Can let Master Know they have been initialized (this is what will be returned during the next spi message)  
    
  }
  
/*SERIAL_PRINT_REGISTERS register (for debugging)*/   
  //grab spi_register_array data for use by Teensy
  spi_register_array[SERIAL_PRINT_REGISTERS][1] = register_data_low_byte;
  spi_register_array[SERIAL_PRINT_REGISTERS][2] = register_data_high_byte;
  register_data = (register_data_low_byte << 8 | register_data_high_byte);

  //If Master wants Teensy to print it will write a 1 to the register data bytes and the Teensy will print all the registers via serial 
  if (register_data == 1){
    //WOULD BE NICE TO FIND A WAY TO MAKE THIS INTO A FOR LOOP. NEED TO MAKE REGISTER ADDRESSES MORE SCALABLE...BUT STRING IN BEGINNING MAKES IT QUITE A BIT TRICKY
    Serial << "INIT_STEERING_THROTTLE Register" << " " <<  spi_register_array[SERIAL_PRINT_REGISTERS][0] << " " << spi_register_array[SERIAL_PRINT_REGISTERS][1]
    << " " << spi_register_array[INIT_STEERING_THROTTLE][2] << " " << spi_register_array[INIT_STEERING_THROTTLE][3];
    Serial.println();
    Serial << "INIT_MOTOR_CONTROLLERS" << " " <<  spi_register_array[INIT_MOTOR_CONTROLLERS][0] << " " << spi_register_array[INIT_MOTOR_CONTROLLERS][1]
    << " " << spi_register_array[INIT_MOTOR_CONTROLLERS][2] << " " << spi_register_array[INIT_MOTOR_CONTROLLERS][3];
    Serial.println();
    Serial << "BEGIN_DATA_COLLECTION" << " " <<  spi_register_array[BEGIN_DATA_COLLECTION][0] << " " << spi_register_array[BEGIN_DATA_COLLECTION][1]
    << " " << spi_register_array[BEGIN_DATA_COLLECTION][2] << " " << spi_register_array[BEGIN_DATA_COLLECTION][3];
    Serial.println();
    Serial << "SERIAL_PRINT_REGISTERS" << " " <<  spi_register_array[SERIAL_PRINT_REGISTERS][0] << " " << spi_register_array[SERIAL_PRINT_REGISTERS][1]
    << " " << spi_register_array[SERIAL_PRINT_REGISTERS][2] << " " << spi_register_array[SERIAL_PRINT_REGISTERS][3];
    Serial.println();
    Serial << "RADIO_STEERING_READ" << " " <<  spi_register_array[RADIO_STEERING_READ][0] << " " << spi_register_array[RADIO_STEERING_READ][1]
    << " " << spi_register_array[RADIO_STEERING_READ][2] << " " << spi_register_array[RADIO_STEERING_READ][3];
    Serial.println();
    Serial << "RADIO_THROTTLE_READ" << " " <<  spi_register_array[RADIO_THROTTLE_READ][0] << " " << spi_register_array[RADIO_THROTTLE_READ][1]
    << " " << spi_register_array[RADIO_THROTTLE_READ][2] << " " << spi_register_array[RADIO_THROTTLE_READ][3];
    Serial.println();
    Serial << "RIGHT_FRONT_VELOCITY_READ" << " " <<  spi_register_array[RIGHT_FRONT_VELOCITY_READ][0] << " " << spi_register_array[RIGHT_FRONT_VELOCITY_READ][1]
    << " " << spi_register_array[RIGHT_FRONT_VELOCITY_READ][2] << " " << spi_register_array[RIGHT_FRONT_VELOCITY_READ][3];
    Serial.println();      
    Serial << "LEFT_FRONT_VELOCITY_READ" << " " <<  spi_register_array[LEFT_FRONT_VELOCITY_READ][0] << " " << spi_register_array[LEFT_FRONT_VELOCITY_READ][1]
    << " " << spi_register_array[LEFT_FRONT_VELOCITY_READ][2] << " " << spi_register_array[LEFT_FRONT_VELOCITY_READ][3];
    Serial.println();    
    Serial << "RIGHT_REAR_VELOCITY_READ" << " " <<  spi_register_array[RIGHT_REAR_VELOCITY_READ][0] << " " << spi_register_array[RIGHT_REAR_VELOCITY_READ][1]
    << " " << spi_register_array[RIGHT_REAR_VELOCITY_READ][2] << " " << spi_register_array[RIGHT_REAR_VELOCITY_READ][3];
    Serial.println();    
    Serial << "THROTTLE_ALL_WRITE" << " " <<  spi_register_array[THROTTLE_ALL_WRITE][0] << " " << spi_register_array[THROTTLE_ALL_WRITE][1]
    << " " << spi_register_array[THROTTLE_ALL_WRITE][2] << " " << spi_register_array[THROTTLE_ALL_WRITE][3];
    Serial.println();    
     Serial << "THROTTLE_RIGHT_FRONT_WRITE" << " " <<  spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][0] << " " << spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][1]
    << " " << spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][2] << " " << spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][3];
    Serial.println();    
    Serial << "THROTTLE_LEFT_FRONT_WRITE" << " " <<  spi_register_array[THROTTLE_LEFT_FRONT_WRITE][0] << " " << spi_register_array[THROTTLE_LEFT_FRONT_WRITE][1]
    << " " << spi_register_array[THROTTLE_LEFT_FRONT_WRITE][2] << " " << spi_register_array[THROTTLE_LEFT_FRONT_WRITE][3];
    Serial.println();    
    Serial << "THROTTLE_RIGHT_REAR_WRITE" << " " <<  spi_register_array[THROTTLE_RIGHT_REAR_WRITE][0] << " " << spi_register_array[THROTTLE_RIGHT_REAR_WRITE][1]
    << " " << spi_register_array[THROTTLE_RIGHT_REAR_WRITE][2] << " " << spi_register_array[THROTTLE_RIGHT_REAR_WRITE][3];
    Serial.println();    
    Serial << "THROTTLE_LEFT_REAR_WRITE" << " " <<  spi_register_array[THROTTLE_LEFT_REAR_WRITE][0] << " " << spi_register_array[THROTTLE_LEFT_REAR_WRITE][1]
    << " " << spi_register_array[THROTTLE_LEFT_REAR_WRITE][2] << " " << spi_register_array[THROTTLE_LEFT_REAR_WRITE][3];
    Serial.println();    
    Serial << "STEERING_WRITE" << " " <<  spi_register_array[STEERING_WRITE][0] << " " << spi_register_array[STEERING_WRITE][1]
    << " " << spi_register_array[STEERING_WRITE][2] << " " << spi_register_array[STEERING_WRITE][3];
    Serial.println();    

    //Resets the register_data to zero so that this code only prints the registers once
    return_array [2] = 0; //Low byte zero
    return_array [3] = 0; //High byte zero
    spi_register_array[SERIAL_PRINT_REGISTERS] = return_array;
      
    }

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array*/

/*THROTTLE_ALL_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_ALL_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_ALL_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);
    
    //Send CAN message to update all motors with a the same torque setpoint
    //return_array [0] = THROTTLE_ALL_WRITE; //Something will be done here
    spi_register_array[THROTTLE_ALL_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*THROTTLE_RIGHT_FRONT_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_RIGHT_FRONT_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);

    //Send CAN message to update right front motor torque setpoint
    //return_array [0] = THROTTLE_RIGHT_FRONT_WRITE; //Something will be done here
    spi_register_array[THROTTLE_RIGHT_FRONT_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*THROTTLE_LEFT_FRONT_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_LEFT_FRONT_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_LEFT_FRONT_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);
   
    //Send CAN message to update left front motor torque setpoint
    //return_array [0] = THROTTLE_LEFT_FRONT_WRITE; //Something will be done here
    spi_register_array[THROTTLE_LEFT_FRONT_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*THROTTLE_RIGHT_REAR_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_RIGHT_REAR_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_RIGHT_REAR_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);

    //Send CAN message to update right rear motor torque setpoint
    //return_array [0] = THROTTLE_RIGHT_REAR_WRITE; //Something will be done here
    spi_register_array[THROTTLE_RIGHT_REAR_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*THROTTLE_LEFT_REAR_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_LEFT_REAR_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_LEFT_REAR_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);

    //Send CAN message to update left rear motor torque setpoint
    //return_array [0] = THROTTLE_LEFT_REAR_WRITE; //Something will be done here
    spi_register_array[THROTTLE_LEFT_REAR_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*STEERING_WRITE register*/
    //grab spi_register_array data for use by Teensy
    spi_register_array[THROTTLE_LEFT_REAR_WRITE][1] = register_data_low_byte;
    spi_register_array[THROTTLE_LEFT_REAR_WRITE][2] = register_data_high_byte;
    register_data = (register_data_low_byte << 8 | register_data_high_byte);

    //Send CAN message to update left rear motor torque setpoint
    writeServo(register_data);
    //return_array [0] = THROTTLE_LEFT_REAR_WRITE; //Something will be done here
    spi_register_array[THROTTLE_LEFT_REAR_WRITE] = return_array ;//Can let Master know they have been initialized (this is what will be returned during the next spi message)

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* UPDATE SENSOR spi_register ARRAYS with the latest readings if collecting_data flag is true (set true via command from Master)*/

  if (collecting_data == true) {
    //collect and store every sensor value
    //The CAN messages for wheel velocity readings will be here. Data will be recieved and loaded into the corresponding spi_register
  }

}

/* END OF MAIN LOOP*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*INTERRUPT SERVICE ROUTINE*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//Interrupt Service Routine to run the slave data transfer function call. Responds to the Masters request for a message.
void spi0_isr(void) {
  spi_data_index++;
  current_register = data[1];
  SPI_SLAVE.rxtx8(data, spi_register_array[current_register], dataLength);

  if (spi_data_index == 4) {
    /*data[] array contains the most recent SPI message from Master when the index is at 4*/
    spi_register_array[current_register] = data;//Moving recently recieved message into the appropriate register
    spi_data_index = 0; // reset the spi data index to zero

  }

}


