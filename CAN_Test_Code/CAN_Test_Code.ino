
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

     ret = set_torque_operating_mode(NODE_1); // Configure node 1 for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 

     if (GENERAL_PRINT) {
        Serial <<"set_torque_operating_mode(NODE_1) function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
      }      

     ret = set_torque_operating_mode(NODE_2); // Configure node 2 for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 

     if (GENERAL_PRINT) {
        Serial <<"set_torque_operating_mode(NODE_2) function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     }    

     ret = set_torque_operating_mode(NODE_3); // Configure node 3 for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 

     if (GENERAL_PRINT) {
        Serial <<"set_torque_operating_mode(NODE_3) function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     }   
       
     ret = set_torque_operating_mode(NODE_4); // Configure node 4 for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 

     if (GENERAL_PRINT) {
        Serial <<"set_torque_operating_mode(NODE_4) function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     }   

     ret = start_remote_nodes(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
     
     if (GENERAL_PRINT) {
        Serial <<"start_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     }


     ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again. Doing this again after nodes being operational
                         //So that I can test read message filtering in the reset_nodes function. 
      
     if (GENERAL_PRINT) {
        Serial <<"reset_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
        Serial.println();
        Serial.println();
     }
      
    CAN_Test_Flag = false;
  }


////If a CAN message is available immediately, then read it (done every time through main, so need to make sure that main loop frequency is much slower than the rate at which PDO's are being broadcast. 
//  CAN_message_t msg;
//  msg.timeout = 0;
//  if (CANbus.read(msg) != 0){//If the read message timeout wasnt reached and a message was available to read
//    if (PRINT)
//    {
//      Serial.println();
//      Serial.println("Message recently broadcast to CAN bus");
//      Serial.println();
//      print_CAN_message(msg);
//    }
//  }
  




/* END OF MAIN LOOP*/

}





