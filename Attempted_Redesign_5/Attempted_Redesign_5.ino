
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
#define SPI_MODE0     0x00//00 mode0, 01 mode1
#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

/* Create a rgister map to store read, write, and command data on the Teensy. Values are volatile because the register map is being accessed by spi0_isr */
typedef struct reg_struct {

  volatile bool init_servo_radio;
  volatile bool begin_data_collection;
  volatile bool print_registers;
  
} reg_struct_t ;

// union type definition linking the above reg_struct type to a 128 byte array that will be instantiated in loop below. This will be the memory accessed by both the struct and 
//the array 
typedef union reg_union {

  volatile uint8_t bytes[128];//Allocates 128 bytes of memory pointed to by 
  reg_struct_t reg_map; //Map of the registers
  
} reg_union_t;

//Initialize the register map union (all zeroes by default)
reg_union_t registers = {0}; 
//can access data like:
//                      registers.bytes[1]
//                      registers.init_servo_radio

/* spi0_isr buffer related */
//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
int8_t spi_address_buff;//stores the address byte for use in the isr
int8_t spi_rw_bit;//stores wether the master is sending a read or write message
#define RW_MASK 0b10000000; 
#define ADDRESS_MASK 0b01111111;

/*Spi Task/isr Flags */
bool servo_radio_on = false; //Used by SPI task to know if the servo and radio are initialized yet. Initilize commands from master will be ignored if initialization has already occured
bool motor_controllers_on = false; //Used by SPI task to know if motor controllers have already been initialized
bool collecting_data = false; //Used by SPI task to start and stop data collection from sensors
bool spi_address_flag = true; //Used by spi_transfer_complete_isr to let spi0_isr know that the first byte (the address byte) of a message has arrived

/* Print spi registers function related */
uint32_t first_pointer;
uint32_t next_pointer;
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
  
/*Initialize the SPI_slave device,register map, and interrupt service routines*/
  spi_slave_init();
//Enable the SPI0 Interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0); //CURRENTLY DONT KNOW WHY THIS IS ENABLING THE ISR
//Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0),spi_transfer_complete_isr,RISING);
  
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
    //Initialize the servo and radio if asked to do so by Master and the on flag is false    
  if (registers.reg_map.init_servo_radio == true && servo_radio_on == false ) {
    initPWMin();
    initServo();
    servo_radio_on = true;
  }

/*INIT_MOTOR_CONTROLLERS register*/   
  //grab spi_register_array data for use by Teensy


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
  if (registers.reg_map.begin_data_collection == true && collecting_data == false ) { 
    if (collecting_data == false){
  
      collecting_data = true;
  
    }
  }

  
/*SERIAL_PRINT_REGISTERS register (for debugging)*/   
  //If Master wants Teensy to print it will send a true to address of print_registers and this code will run
  if (registers.reg_map.print_registers == true ){

      print_register_map();
      
    }

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array*/

/*THROTTLE_ALL_WRITE register*/
    //grab spi_register_array data for use by Teensy

    
    //Send CAN message to update all motors with a the same torque setpoint

/*THROTTLE_RIGHT_FRONT_WRITE register*/
    //grab spi_register_array data for use by Teensy


    //Send CAN message to update right front motor torque setpoint

/*THROTTLE_LEFT_FRONT_WRITE register*/
    //grab spi_register_array data for use by Teensy

   
    //Send CAN message to update left front motor torque setpoint

/*THROTTLE_RIGHT_REAR_WRITE register*/
    //grab spi_register_array data for use by Teensy


    //Send CAN message to update right rear motor torque setpoint

/*THROTTLE_LEFT_REAR_WRITE register*/
    //grab spi_register_array data for use by Teensy


    //Send CAN message to update left rear motor torque setpoint

/*STEERING_WRITE register*/
    //grab spi_register_array data for use by Teensy


    //Update the servo pwm value
    //writeServo(registers.steering);

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/            

/* UPDATE SENSOR spi_register ARRAYS with the latest readings if collecting_data flag is true (set true via command from Master)*/

  if (collecting_data == true) {
    //collect and store every sensor value
    //The CAN messages for wheel velocity readings will be here. Data will be recieved and loaded into the corresponding spi_register
  }

}

/* END OF MAIN LOOP*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*INTERRUPT SERVICE ROUTINES*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//Interrupt Service Routine to run the slave data transfer function call. Responds to the Masters request for a message.
void spi0_isr(void) {

  if (spi_address_flag) {

    spi_address_buff = ADDRESS_MASK & SPI0_POPR; //Ands the shift register 
    spi_rw_bit = RW_MASK & SPI0_POPR;
    spi_address_flag = false;

    if (spi_rw_bit){//if the read/write bit is 1, it is a read message and spi_rw_buff will be true

      SPI0_PUSHR_SLAVE = registers.bytes[spi_address_buff];
      spi_address_buff++; //Increment the address so the next byte sent will be the next byte in the spi register
      
    }
    
  }
//    dataIN[dataPointer] = SPI0_POPR;
//    SPI0_PUSHR_SLAVE = dataOUT[dataPointer];  
//    SPI0_SR |= SPI_SR_RFDF;
}

void spi_transfer_complete_isr(void) {

  spi_address_flag = true;//Raises the address flag so that the in the next message, spi0_isr knows it is recieving the address byte
  
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*FUNCTIONS*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void spi_slave_init(void){
  /*Configure SPI Memory Map*/
//This clears the entire SPI0_MCR register. This will clear the MSTR bit (turn off master mode), clear the 
  SPI0_MCR=0x00000000;
//THIS CLEARS THE ENTIRE SPI0_CTAR0 REGISTER (effectively clearing the deffault frame size which is 8 --> Not necessary as we want an 8 bit frame size)
  SPI0_CTAR0=0;
//This line sets the clock phase and clock polarity bits. Clock is inactive low (polarity) and the data is captured on the leading edge of SCK (phase)
  SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | SPI_MODE0 << 25;
//THIS SETS THE BITS FOR FRAME SIZE (The value in this register plus one is the frame size. Want a single byte frame size. Master and slave in our system agree on this)
  SPI0_CTAR0 |= SPI_CTAR_FMSZ(7);
//Request Select and Enable Register. Setting the RFDF_RE FIFO DRAIN REQUEST ENABLE Pin that allows interrupts or DMA to occur. The default method of draining
//the SPI hardware data register is interrupts. When a full 8 bits has been recieved an interrupt will be triggered (SPI0_ISR) and the data will be decoded. 
  SPI0_RSER = 0x00020000;
//Enable the SCK, MISO, MOSI, and CS0 Pins (connections to the master device)
  CORE_PIN13_CONFIG = PORT_PCR_MUX(2);//Serial Clock (SCK) pin
  CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2);//Master Output Slave Input (MOSI) pin
  CORE_PIN12_CONFIG = PORT_PCR_MUX(2);//Master Input Slave Output (MISO) pin
  CORE_PIN10_CONFIG = PORT_PCR_MUX(2);//Chip Select 0 (CS0) or Enable  pin

}

void print_register_map(void){//This prints the name and address of each of the items in the register map along with the data stored in each register MUST UPDATE AS REGISTERS ARE ADDED
    Serial << "Register Map of Teensy";
    Serial.println();

    first_pointer = (uint32_t)&registers.reg_map.init_servo_radio;//Grab the address of the first register in the register map. (uint32_t) is a cast used to get the address to the correct type
    
    next_pointer = (uint32_t)&registers.reg_map.init_servo_radio - first_pointer;
      Serial << "init_servo_radio " << registers.reg_map.init_servo_radio;
      Serial.println();
    next_pointer = (uint32_t)&registers.reg_map.begin_data_collection - first_pointer;
      Serial << "begin_data_collection " << registers.reg_map.begin_data_collection;
      Serial.println();
    next_pointer = (uint32_t)&registers.reg_map.print_registers - first_pointer;
      Serial << "print_registers " << registers.reg_map.print_registers;
      Serial.println();            
}


