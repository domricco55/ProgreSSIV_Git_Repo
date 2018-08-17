/* 
 *  This .cpp file defines the content of functions to be called by the main routine
 */

// Allow access to arduino specific datatypes 
#include <arduino.h>

// Define variables and constants. Voltatile is used for variables that are only modified in ISRs
// as the compiler is liable to treat them as constants.

// RX input----------------------------------------------- 
// Pin numbers for input
#define THROTTLEPIN 22
#define STEERPIN 23
// Variables for throttle start time
uint16_t THR_st;
// Variables for steering start time
uint16_t ST_st;
// throttle input value (ranges from ~-500 to 500) / defined in main
extern volatile int16_t THR_in;
//steering input value (ranges from ~-500 to 500)  / defined in main
extern volatile int16_t ST_in;
//--------------------------------------------------------

// URF---------------------------------------------------- 
// Pin numbers for IO
#define URF_in 17
#define URF_trig 16
extern uint16_t URF_dist;
//--------------------------------------------------------

// Specify contents of functions to be called by main routine

// Functions to initialize URF and output URF value (configured as analog input)--------------------------------------------------
void initURF(){
  // Set data directions
  pinMode(URF_in, INPUT);
  pinMode(URF_trig,OUTPUT); 

  // Put URF in continuous mode
  digitalWrite(URF_trig,HIGH);   
}

void pollURF(){
  URF_dist = analogRead(URF_in) * 5;
  Serial.println(analogRead(URF_in));
}
//-------------------------------------------------------------------------------------------------------------------------------

// Steering ISR to determine the time difference between rising edge and falling edge--------------------------------------------
// Called and run upon the change of the input pin tied to the receiver
void ST_int() {
  int16_t x = 0;
  
  // If the pin is now HIGH, record the current time
  if (digitalRead(STEERPIN) == HIGH) 
  {
      ST_st = micros();
  } 
  else 
  {
      // If the pin is now low, calculate, adjust, and output the time
      // between when the timer was started and now. Range between -500 and 500, approximately
      x = (micros() - ST_st - 1500);
      if (x < 530 && x > -530)  //allow for discrepencies
      {
          if (x > 500)
          {
            x = 500;
          }
          
          if (x < -500)
          {
            x = -500;
          }
          
          ST_in = x;
      }
  }
}

// Functionally Identical to steering ISR
void THR_int() {
  int16_t x;
  
  if (digitalRead(THROTTLEPIN) == HIGH) 
  {
      THR_st = micros();
  } 
  else 
  {
      x = (micros() - THR_st - 1500);
      if (x < 530 && x > -530)  //allow for discrepencies
      {
          if (x > 500)
          {
            x = 500;
          }
          
          if (x < -500)
          {
            x = -500;
          }
            
          THR_in = x;       
       }
  }
}

// This function is called in the primary setup, it initializes the pinmodes and assigns the ISRs to the appropriate pins
void initPWMin() {
    // Set the two pins to be inputs
    pinMode(THROTTLEPIN, INPUT);
    pinMode(STEERPIN, INPUT);
 
    // Attach an ISR to be called whenever
    // the pin changes from LOW to HIGH or vice versa
    attachInterrupt(digitalPinToInterrupt(STEERPIN), ST_int, CHANGE);
    attachInterrupt(digitalPinToInterrupt(THROTTLEPIN), THR_int, CHANGE);
}

//-------------------------------------------------------------------------------------------------------------------------------



