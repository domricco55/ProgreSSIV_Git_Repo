
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
#include "shares.h"

/* Other includes */

#include "FlexCAN.h"
#include "kinetis_flexcan.h"
//libraries for imu
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055_ProgreSSIV.h"
#include "imumaths.h"

/* MAY CHANGE OVER TO TASK STRUCTURE LATER */
#include "ProgreSSIV_CAN_write_driver.h"
#include "input_handler.h"
#include "output_handler.h"
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Task Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Task Object Pointers declared in Static RAM*/
SPI_task *SPI_task_p;
MC_state_machine *MC_state_machine_p;

/* Shared data struct pointers declared in Static RAM */
SPI_actuations_t *SPI_actuations;
SPI_commands_t *SPI_commands;
SPI_sensor_data_t *SPI_sensor_data;
node_info_t *node_info;
radio_struct_t *radio_struct;
    
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

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once
//
//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_print;
unsigned long start_time_motors;
unsigned long start_time_servo;
unsigned long start_time_quickstop;

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*CAN Filter Variables*/
int16_t rpm_FR;//stores rpm of node 1 (Front Right wheel)
int16_t rpm_FL;//stores rpm of node 2 (Front Left wheel)
int16_t rpm_BR;//stores rpm of node 3 (Back Right wheel)
int16_t rpm_BL;//stores rpm of node 4 (Back Left wheel)


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

  //MOVE THIS INTO AN INIT FUNTION IN THE BNO DRIVER FILE
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

  /*Task setup*/
  //Shared variable struct initialization on the heap
  SPI_actuations = new SPI_actuations_t();
  SPI_commands = new SPI_commands_t();
  SPI_sensor_data = new SPI_sensor_data_t();
  node_info = new node_info_t();
  radio_struct = new radio_struct_t();
    
  //SPI task initialization on the heap
  SPI_task_p = new SPI_task(SPI_actuations, SPI_commands, SPI_sensor_data, node_info -> node_statuswords, node_info -> node_errors); //Create an instance of the SPI_task class on the heap. 

  //MC state machine initialization on the heap
  MC_state_machine_p = new MC_state_machine(SPI_commands, SPI_actuations -> SPI_torque_actuations, node_info, radio_struct); //Creat an instance of the MC_state_machine class on the heap
}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Do not use delays in the loop
as dynamic tasks are executing and their timing is reliant upon cooperative multitasking.*/
void loop() {
  
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

  /* CANT QUITE DECIDE IF I WANT THE PRINTING DONE IN MAIN OR IN EACH TASK...BETER FOR ORGANIZING FLOW OF INFORMATION*/
  unsigned long current_time_print = millis();
  if ((current_time_print - start_time_print) >= 10000)  //2000ms => 1/2 hz. All printing will happen at this frequency.
  {
    //Print the entire register map at the print frequency
    if(PRINT_REGISTERS){
      
      SPI_task_p -> spi_registers_print();
      
    }
    
//    //Print the IMU values only at the print frequency
//    if (PRINT_IMU) {
//      print_imu_data();
//    }

    //Print only the registers associated with the radio athe the print frequency
    if (PRINT_RADIO) {
      print_radio_data();
    }

    if(MC_CHECK_PRINT){
      Serial.println();
      Serial.print("Statusword 1 = 0x");
      Serial.println(node_info -> node_statuswords[0], HEX);
      Serial.print("Statusword 2 = 0x");
      Serial.println(node_info -> node_statuswords[1], HEX);
      Serial.print("Statusword 3 = 0x");
      Serial.println(node_info -> node_statuswords[2], HEX);
      Serial.print("Statusword 4 = 0x");
      Serial.println(node_info -> node_statuswords[3], HEX);
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

/* WILL BE IN THE IMU TASK ONCE IT IS CREATED */
//  /*reset_imu register*/
//  //Run the imu initialization code from Adafruit_BNO055 library to reset the IMU readings
//  if (registers.reg_map.reset_imu) {
//    if (!bno.begin()) { //This code will cause the bno to initialize. If it did not, it will print the error message
//      if (GENERAL_PRINT) {
//        Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); //Should likely add some error handling code here. Nothing to protect for this occurence.
//      }
//    }
//    else {
//      if (GENERAL_PRINT) {
//        //Display the current IMU temperature
//        int8_t temp = bno.getTemp();
//        Serial.print("Current Temperature: ");
//        Serial.print(temp);
//        Serial.println(" C");
//        Serial.println("");
//        Serial.println("You may want to calibrate your bno055");
//      }
//    }
//    registers.reg_map.reset_imu = 0;//Clear the register so that reset code does not run continuously.
//  }

  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* OUTPUT ACTUATIONS. The actuation value from Master is located in the data bytes of spi_register_array. This code will send the most recent actuation to the approprate peripheral*/

  //Write the servo value from servo_out register
  writeServo(SPI_actuations -> SPI_servo_out);
  
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

  /* UPDATE SENSOR READINGS. This code will grab the latest sensor values and store them in the registers. */

//THE IMU DATA GATHERING WILL BE IN IMU TASK AND THE STEERING AND THROTTLE COMMAND GATHERING WILL BE IN THE INPUT H
//  //Gather the IMU sensor data. These functions are from Adafruit_BNO055_ProgreSSIV.cpp
//
//  uint8_t bno_buffer[6]; //Used to store the I2C message containting the imu data
//
//  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_EULER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of EULER data
//
//  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
//  registers.reg_map.euler_heading = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
//  registers.reg_map.euler_roll = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
//  registers.reg_map.euler_pitch = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
//
//  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_ACCELEROMETER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of ACCELEROMETER data
//
//  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
//  registers.reg_map.accl_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
//  registers.reg_map.accl_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
//  registers.reg_map.accl_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
//
//  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_GYROSCOPE, bno_buffer, 6); //Send and I2C message to request the 6 bytes of GYROSCOPE data
//
//  //Load the registers with the I2C euler data (concatinate high and low byte before putting the value into the register)
//  registers.reg_map.gyro_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
//  registers.reg_map.gyro_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
//  registers.reg_map.gyro_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);
//
//  //Gather the steering and throttle inputs from the RADIO
//  registers.reg_map.radio_steering = ST_in; //This value is an extern declared in input_handler.h
//  registers.reg_map.radio_throttle = THR_in; //This value is an extern declared in input_handler.h

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
void spi_transfer_complete_isr_wrapper(){
 SPI_task_p -> spi_transfer_complete_isr();
}

void spi0_isr(void){
 SPI_task_p -> spi0_callback();
}
