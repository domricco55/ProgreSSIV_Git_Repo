/* 
 *  This .cpp file defines the content of functions to be called by the main routine
 */

// Allow access to arduino specific datatypes 
#include <arduino.h>
#include "structs.h"
#include "fault_handler.h"

// Define variables and constants. Voltatile is used for variables that are only modified in ISRs
// as the compiler is liable to treat them as constants.

// Fault / Indicator LED---------------------------------- 
// Pin numbers for IO
#define LED_r 5
#define LED_g 6 
#define LED_b 9
extern uint8_t errorState;
extern IMUstruct IMUdat;

// define external variables used to check for faults
// throttle input value (ranges from ~-500 to 500) / defined in main
extern volatile int16_t THR_in;
//steering input value (ranges from ~-500 to 500)  / defined in main
extern volatile int16_t ST_in;
//--------------------------------------------------------

// Specify contents of functions to be called by main routine

// Set LED using indicatorSet(0x00RRGGBB)
void indicatorSet(uint32_t RGBval){
  analogWrite(LED_r,map((RGBval & 0x00ff0000),0,256,0,4096));
  analogWrite(LED_g,map((RGBval & 0x0000ff00),0,256,0,4096));
  analogWrite(LED_b,map((RGBval & 0x000000ff),0,256,0,4096));
}
// ----------------------------------

// Functions to initialize and detect fault states-------------------------------------------------------------------------------
// initialize indicator LED pins
void initFault(){
  // Set led pins to output
  pinMode(LED_r,OUTPUT); 
  pinMode(LED_g,OUTPUT); 
  pinMode(LED_b,OUTPUT);   
}

// passively detects predefined fault states due to bad data etc 
void detectFault(){
  if (false){//if ( (THR_in > 600 || THR_in < 600) || (ST_in > 600 || ST_in < 600) ) {
    // receiver error, LED red errorstate 1
    indicatorSet(rgbRED);
    errorState = 1;
  }
  else if (IMUdat.err == 1){
    // IMU comm error, LED purple errorstate 2
    indicatorSet(rgbPURPLE);
    errorState = 2;
  }
  else { 
    // no known fault
    indicatorSet(rgbGREEN);
    errorState = 0;
  }
}
//-------------------------------------------------------------------------------------------------------------------------------
