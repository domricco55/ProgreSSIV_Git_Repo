
/**
   CAN_Test_Code.ino - Dominic Riccoboni

*/

#include "uLaren_CAN_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"

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
/* Debugging/Printing setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define GENERAL_PRINT 1

///*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
///* Timing/Frequency setup */
///*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
//
//bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.
//
////These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
//unsigned long start_time_print;
//unsigned long start_time_motors;
//unsigned long start_time_servo;
////unsigned long start_time_voltage;//Need to add in the voltage monitoring feature of the motor controllers. FUTURE WORK

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

  /*Startup CAN network*/
  CANbus.begin();

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly. This is where any finite state machine code may be placed.*/
void loop() {

//  if (timing_init_flag) {
//    // Initialize the Timing Variables so that there is a start time
//    start_time_print = millis();
//    start_time_motors = millis();
//    start_time_servo = millis();
//    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
//    //start_time_voltage = millis();
//    timing_init_flag = false;
//  }

/* END OF MAIN LOOP*/

void print_radio_data(void) {

  Serial << "radio_steering: " << registers.reg_map.radio_steering;
  Serial.println();
  Serial.println();

  Serial << "radio_throttle: " << registers.reg_map.radio_throttle;
  Serial.println();
  Serial.println();
}



