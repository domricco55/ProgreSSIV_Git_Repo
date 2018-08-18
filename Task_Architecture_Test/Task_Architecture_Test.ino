
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


/*SPI task instantiation*/
ProgreSSIV_SPI_task SPI_task; //Create an instance of the ProgreSSIV_SPI_task class in static RAM. Must be static because members of the class are mapped to interrupts

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

//bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once
//
////These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
//unsigned long start_time_print;
//unsigned long start_time_motors;
//unsigned long start_time_servo;
//unsigned long start_time_quickstop;

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

      case 0x3A1: //If TxPDO3, node 1 (the statusword)

        mode_of_op_displays[0] = msg.buf[0];
          
      break;

      case 0x3A2: //If TxPDO3, node 2 (the statusword)
      
        mode_of_op_displays[1] = msg.buf[0];
          
      break;

      case 0x3A3: //If TxPDO3, node 3 (the statusword)
      
        mode_of_op_displays[2] = msg.buf[0];
          
      break;

      case 0x3A4: //If TxPDO3, node 4 (the statusword )

        mode_of_op_displays[3] = msg.buf[0];

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

void spi_transfer_complete_isr_wrapper(){
 SPI_task.spi_transfer_complete_isr();
}

void spi0_isr(void){
 SPI_task.spi0_callback();
}
