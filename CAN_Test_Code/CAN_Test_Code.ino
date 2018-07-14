
/**
   CAN_Test_Code.ino - Dominic Riccoboni

*/

#include "ProgreSSIV_MC_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus preparation (From ProgreSSIV_MC_Driver)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

FlexCAN CANbus(1000000);

/* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

/* Controlword values that drive the state transitions within the Device Control state machine. See EPOS4 Firmware Specification documentation for information on the controlword and state machine. */
#define SHUTDOWN_COMMAND 0x0006 //Controlword for shutdown. Takes the Device Control state machine from the "switch-on disabled" (post initialization state) to the "Ready to switch on" state. 
#define ENABLE_OP_COMMAND 0x000F //Controlword for switch on and enable. Puts Device Control state machine into "Operation enabled state" under MOST conditions. 
#define QUICK_STOP_COMMAND 0x000B //Controlword for Quick stop. Takes the Device Control state machine from the "Operation enabled" state to the "Quick stop active" state. The motors will decelerate to zero 
                                       //velocity at the quick stop deceleration value (index 0x6085). 
#define RESET_FAULT_COMMAND 0x0080 //Controlword for reset fault. Takes the Device Control state machine from the "fault" state to the "Switch on disabled state"

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
/* Debugging/Printing setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define GENERAL_PRINT 1

bool CAN_Test_Flag = true;


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.

//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_motors;
unsigned long start_time_servo;
//unsigned long start_time_voltage;//Need to add in the voltage monitoring feature of the motor controllers. FUTURE WORK

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* The setup function runs all start up functions. Any functions that are run only once, always, and at startup should go here. */
void setup() {

  /*begin serial port operation*/
  Serial.begin(115200);
  delay(3000);

  if (GENERAL_PRINT) {
    Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
    delay(500);
  }

  /*Startup CAN network (this is a FlexCAN function)*/
  CANbus.begin();

  /* Also going to do a little servo testing here*/
  initPWMin();
  initServo();

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly. This is where any finite state machine code may be placed.*/
void loop() {

  if(CAN_Test_Flag){
    
      ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
      
      if (GENERAL_PRINT) {
        Serial <<"reset_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
      }

     ret = reset_communications(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
     
     if (GENERAL_PRINT) {
        Serial <<"reset_communications function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
      }

     ret = set_torque_operating_mode(); // Configure all nodes for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 

     if (GENERAL_PRINT) {
        Serial <<"set_torque_operating_mode function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
      }      


     ret = set_TxPDO1_inhibit_time(); //Set the TxPDO1 inhibit time for all nodes
     
     if (GENERAL_PRINT) {
        Serial <<"set_TxPDO1_inhibit_time function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     } 

//
//     ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
//     
//     if (GENERAL_PRINT) {
//        Serial <<"start_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//     }
//
//     ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND); //Send out the controlword RxPDO with a shutdown command so that the device state machine transitions to the "Ready to switch on" state 
//
//     if (GENERAL_PRINT) {
//        Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//        Serial.println();
//        Serial.println();
//     }
//
//     ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); //Send out the controlword RxPDO with an enable operation command so that the device state machine transitions to the "Operation Enabled" state 
//
//     if (GENERAL_PRINT) {
//        Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//        Serial.println();
//        Serial.println();
//     }
//
//     ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
//      
//      if (GENERAL_PRINT) {
//        Serial <<"reset_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//      }

    CAN_Test_Flag = false;
  }



//  if (timing_init_flag) {
//    // Initialize the Timing Variables so that there is a start time
//    start_time_motors = millis();
//    start_time_servo = millis();
//    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
//    //start_time_voltage = millis();
//    timing_init_flag = false;
//  }
//  
//  /* Update the servo with the radio value. */
//  writeServo(ST_in);
//
//
//  unsigned long current_time_motors = micros();
//  if ((current_time_motors - start_time_motors) >= 556)  //.556 ms => 180hz. Motor torque setpoints will update at this frequency
//  {
//
//    RxPDO2_torque_write(NODE_1, THR_in);
//    RxPDO2_torque_write(NODE_2, THR_in);
//    RxPDO2_torque_write(NODE_3, THR_in);
//    RxPDO2_torque_write(NODE_4, THR_in);
//  }


/* END OF MAIN LOOP*/

}





