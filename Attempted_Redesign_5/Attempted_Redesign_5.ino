
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


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SPI Communication/SPI Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* SPI memory map setup definitions */
#define SPI_MODE0     0x00
#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

/*SPI registers preparation*/
volatile uint8_t *spi_register_array[256];//An array of pointers to the spi register arrays (example is the initial array below)

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
  
/*Configure SPI Memory Map*/
//This clears the entire SPI0_MCR register. This will clear the MSTR bit (turn off master mode), clear the 
  SPI0_MCR=0x00000000;
//THIS CLEARS THE ENTIRE SPI0_CTAR0 REGISTER (effectively clearing the deffault frame size which is 8 --> Not necessary as we want an 8 bit frame size)
  SPI0_CTAR0=0
//This line sets the clock phase and clock polarity bits. Clock is inactive low (polarity) and the data is captured on the leading edge of SCK (phase)
  SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | SPI_MODE0 << 25;
//THIS SETS THE BITS FOR FRAME SIZE (The value in this register plus one is the frame size. Want a single byte frame size. Master and slave in our system agree on this)
  SPI0_CTAR0 |= SPI_CTAR_FMSZ(7);
//Request Select and Enable Register. Setting the RFDF_RE FIFO DRAIN REQUEST ENABLE Pin that allows interrupts or DMA to occur. The default method of draining
//the SPI hardware data register is interrupts. When a full 8 bits has been recieved an interrupt will be triggered (SPI0_ISR) and the data will be decoded. 
  SPI0_RSER = 0x00020000;
//Enable the SCK, MISO, MOSI, and CS0 Pins (connections to the master device)
  CORE_PIN13_CONFIG = PORT_PCR_MUX(2);
  CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);
  CORE_PIN12_CONFIG = PORT_PCR_MUX(2);
  CORE_PIN10_CONFIG = PORT_PCR_MUX(2);
//Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0); //CURRENTLY DONT KNOW WHY THIS IS ENABLING THE ISR
//Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0),spi_transfer_complete_ISR,RISING);


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


