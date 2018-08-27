/** @file ProgreSSIV_Teensy_Firmware.ino
 *  @ brief Main Teensy Firmware script. 
 *  
 *  @details
 *  Runs tasks sequentially in a loop using a cooperative multitasking approach.
 *  
 *  @copyright
 *  
 *  @mainpage mainpage content 
 *  @brief
 *  @details
 */


/* Task File includes*/
#include "ProgreSSIV_MC_state_machine.h"                                                                              
#include "ProgreSSIV_SPI_task.h"
#include "ProgreSSIV_IMU_task.h"
#include "ProgreSSIV_CAN_msg_handler.h"
#include "shares.h"

/* Other includes */

#include "FlexCAN.h"
#include "kinetis_flexcan.h"


/* MAY CHANGE OVER TO TASK STRUCTURE LATER BUT FOR NOW THESE ARENT CLASSES */

#include "input_handler.h"
#include "output_handler.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Task Static RAM*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Task Object Pointers declared in Static RAM*/
SPI_task *SPI_task_p;                                                                                                                   //!< brief
MC_state_machine *MC_state_machine_p;                                                                                                   //!< brief
IMU_task *IMU_task_p;                                                                                                                   //!< brief
CAN_msg_handler *CAN_msg_handler_p;                                                                                                     //!< brief


/* Shared data struct pointers declared in Static RAM */
SPI_actuations_t *SPI_actuations;                                                                                                       //!< brief
SPI_commands_t *SPI_commands;                                                                                                           //!< brief
SPI_sensor_data_t *SPI_sensor_data;                                                                                                     //!< brief
node_info_t *node_info;                                                                                                                 //!< brief
radio_struct_t *radio_struct;                                                                                                           //!< brief
flags_struct_t *flags_struct;                                                                                                           //!< brief
    
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Static RAM*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both for the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
volatile int16_t THR_in; // instantiate variable for throttle input value (ranges from ~-500 to 500)                                    //!< brief
volatile int16_t ST_in;  // instantiate variable for steering input value (ranges from ~-500 to 500)                                    //!< brief

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Debugging/Printing setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define GENERAL_PRINT 1                                                                                                                 //!< brief
#define LOOP_PRINT_REGISTERS 0                                                                                                          //!< brief
#define MC_CHECK_PRINT 0                                                                                                                //!< brief

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

unsigned long *start_time_print;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/** @brief Arduino setup function 
 *  
 *  The setup function contains all functions that are are to be run only once at startup. Task objects are instiantiated in
 *  this function and the servo, IMU, and CAN bus startup functions are run here. The interrupt vectors for spi0_isr 
 *  and spi_transfer_complete_isr_wrapper are attached here as well. 
 *  
 */
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
  
  //Initialize a pin change interrupt on the rising edge of the chip select (enable) pin for spi
  attachInterrupt(digitalPinToInterrupt(CS0), spi_transfer_complete_isr_wrapper, RISING);

  //CAN filter task initialization on the heap
  CAN_msg_handler_p = new CAN_msg_handler(node_info, SPI_sensor_data -> node_rpms);
  
  //MC state machine initialization on the heap
  MC_state_machine_p = new MC_state_machine(SPI_commands, SPI_actuations -> node_torques, node_info, radio_struct, CAN_msg_handler_p); //Creat an instance of the MC_state_machine class on the heap

  //IMU task initialization on the heap
  IMU_task_p = new IMU_task(SPI_commands, SPI_sensor_data, flags_struct);
  
  /*Timinig Initialization*/
  start_time_print = new unsigned long(millis());
  
}

/** @brief Arduino loop function 
 *  
 *  Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Do not use delays in the loop
 *  as dynamic tasks are executing and their timing is reliant upon cooperative multitasking.
 *  
 */
 
void loop() {

  //Run each task sequentially
  SPI_task_p -> handle_registers(); //Run one iteration of the SPI tasks register handling function
  MC_state_machine_p -> run_sm(); //Run one iteration of the motor controllers state machine
  IMU_task_p -> take_data(); //Run one iteration of the IMU tasks sensor data gathering function
  CAN_msg_handler_p-> try_CAN_msg_filter(); //Read and filter a CAN message from the CAN bus buffers if it is available

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

/** @brief SPI channel 0 interrupt service routine wrapper
 *  @details
 *  This function links the spi_transfer_complete_isr member of the ProgreSSIV_SPI_task class to the the falling edge of the CS0 (chip select 0) line. 
 */
//These wrapper functions are here so that the interrupt service routines can be members of class SPI_task but still be a callback function for an interrupt
void spi_transfer_complete_isr_wrapper(void){
  
  SPI_task_p -> spi_transfer_complete_isr();
  
}


/** @brief SPI channel 0 interrupt service routine wrapper
 *  @details
 *  This function links the spi0_isr_callback member of the ProgreSSIV_SPI_task class to the spi0 interrupt vector. 
 */
void spi0_isr(void){
 
 SPI_task_p -> spi0_callback();
 
}
