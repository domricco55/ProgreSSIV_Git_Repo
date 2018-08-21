
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

   Compiling[Y/N]:            


*/

/* Task File includes*/
#include "ProgreSSIV_MC_state_machine.h"
#include "ProgreSSIV_SPI_task.h"
#include "ProgreSSIV_IMU_task.h"
#include "ProgreSSIV_CAN_filter_task.h"
#include "shares.h"

/* Other includes */

#include "FlexCAN.h"
#include "kinetis_flexcan.h"


/* MAY CHANGE OVER TO TASK STRUCTURE LATER */
#include "ProgreSSIV_CAN_write_driver.h"
#include "input_handler.h"
#include "output_handler.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Task Static RAM*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Task Object Pointers declared in Static RAM*/
SPI_task *SPI_task_p;
MC_state_machine *MC_state_machine_p;
IMU_task *IMU_task_p;
CAN_filter_task *CAN_filter_task_p;


/* Shared data struct pointers declared in Static RAM */
SPI_actuations_t *SPI_actuations;
SPI_commands_t *SPI_commands;
SPI_sensor_data_t *SPI_sensor_data;
node_info_t *node_info;
radio_struct_t *radio_struct;
flags_struct_t *flags_struct;
    
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Static RAM*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both for the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
volatile int16_t THR_in; // instantiate variable for throttle input value (ranges from ~-500 to 500)
volatile int16_t ST_in;  // instantiate variable for steering input value (ranges from ~-500 to 500)

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
#define LOOP_PRINT_REGISTERS 0
#define MC_CHECK_PRINT 0
//#define PRINT_IMU 0
//#define PRINT_RADIO 0

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

unsigned long *start_time_print;

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

  //Enable the spi0_isr interrupt
  NVIC_ENABLE_IRQ(IRQ_SPI0);
  
  //Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0), spi_transfer_complete_isr_wrapper, RISING);

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

  /*Task setup*/
  //Shared variable struct initialization on the heap
  SPI_actuations = new SPI_actuations_t();
  
  SPI_commands = new SPI_commands_t();
  
  SPI_sensor_data = new SPI_sensor_data_t();
  node_info = new node_info_t();
  radio_struct = new radio_struct_t();
  flags_struct = new flags_struct_t();
    
  //SPI task initialization on the heap
  SPI_task_p = new SPI_task(SPI_actuations, SPI_commands, SPI_sensor_data, node_info, radio_struct, flags_struct); //Create an instance of the SPI_task class on the heap. 
  SPI_task_p -> spi_slave_init();

  //MC state machine initialization on the heap
  MC_state_machine_p = new MC_state_machine(SPI_commands, SPI_actuations -> node_torques, node_info, radio_struct); //Creat an instance of the MC_state_machine class on the heap

  //IMU task initialization on the heap
  IMU_task_p = new IMU_task(SPI_commands, SPI_sensor_data, flags_struct);

  //CAN filter task initialization on the heap
  CAN_filter_task_p = new CAN_filter_task(node_info, SPI_sensor_data -> node_rpms);

  
  
  /*Timinig Initialization*/
  start_time_print = new unsigned long(millis());
  
}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Do not use delays in the loop
as dynamic tasks are executing and their timing is reliant upon cooperative multitasking.*/
void loop() {
  
//  /* CANT QUITE DECIDE IF I WANT THE PRINTING DONE IN MAIN OR IN EACH TASK...BETER FOR ORGANIZING FLOW OF INFORMATION*/
//  unsigned long start_time_print = start_time_print;
//  unsigned long current_time_print = millis();
//  if ((current_time_print - start_time_print) >= 10000)  //2000ms => 1/2 hz. All printing will happen at this frequency.
//  {
////    //Print the entire register map at the print frequency
////    if(LOOP_PRINT_REGISTERS){
////      
////      SPI_task_p -> spi_registers_print();
////      
////    }
//    
////    //Print the IMU values only at the print frequency
////    if (PRINT_IMU) {
////      print_imu_data();
////    }
//
////    //Print only the registers associated with the radio athe the print frequency
////    if (PRINT_RADIO) {
////      print_radio_data();
////    }
//
////    if(MC_CHECK_PRINT){
////      Serial.println();
////      Serial.print("Statusword 1 = 0x");
////      Serial.println(node_info -> node_statuswords[0], HEX);
////      Serial.print("Statusword 2 = 0x");
////      Serial.println(node_info -> node_statuswords[1], HEX);
////      Serial.print("Statusword 3 = 0x");
////      Serial.println(node_info -> node_statuswords[2], HEX);
////      Serial.print("Statusword 4 = 0x");
////      Serial.println(node_info -> node_statuswords[3], HEX);
////      Serial.println();
//  
////      Serial.println();
////      Serial.print("Error 1 = 0x");
////      Serial.println(registers.reg_map.node_errors[1], HEX);
////      Serial.print("Error 2 = 0x");
////      Serial.println(registers.reg_map.node_errors[2], HEX);
////      Serial.print("Error 3 = 0x");
////      Serial.println(registers.reg_map.node_errors[3], HEX);
////      Serial.print("Error 4 = 0x");
////      Serial.println(registers.reg_map.node_errors[4], HEX);
////      Serial.println();
//
//      print_CAN_statistics();
//    }
//    start_time_print = current_time_print;
//  }

  SPI_task_p -> handle_registers(); //Run one iteration of the SPI tasks register handling function
  MC_state_machine_p -> run_sm(); //Run one iteration of the motor controllers state machine
  IMU_task_p -> take_data(); //Run one iteration of the IMU tasks sensor data gathering function
  CAN_filter_task_p -> try_CAN_msg_filter(); //Read and filter a CAN message from the CAN bus buffers if it is available

/* Havent made servo code compatible with the new task structure yet so this is a legacy of the old way of doing things...here for now */
  //Write the servo value from servo_out register
  writeServo(SPI_actuations -> servo_out);
  
  //Gather the steering and throttle inputs from the RADIO
  radio_struct -> ST_in = ST_in; //This value is an extern declared in input_handler.h
  radio_struct -> THR_in = THR_in; //This value is an extern declared in input_handler.h

}

/* END OF MAIN LOOP*/


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*FUNCTIONS*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void print_radio_data(void) {

  Serial << "radio_steering: " << ST_in;
  Serial.println();
  Serial.println();

  Serial << "radio_throttle: " << THR_in;
  Serial.println();
  Serial.println();
}

//These wrapper functions are here so that the interrupt service routines can be members of class SPI_task but still be a callback function for an interrupt
void spi_transfer_complete_isr_wrapper(void){
 Serial.println("Got to spi_transfer_complete_isr_wrapper");
 SPI_task_p -> spi_transfer_complete_isr();
}

void spi0_isr(void){
 Serial.println("Got to spio_isr");
 SPI_task_p -> spi0_callback();
}
