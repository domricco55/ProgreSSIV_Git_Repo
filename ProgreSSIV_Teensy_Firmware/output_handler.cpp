/* 
 *  This .cpp file defines the content of functions to be called by the main routine
 */

// Allow access to arduino specific datatypes 
#include <arduino.h>
#include <Servo.h>

// Servo-------------------------------------------------- 
// Pin numbers for IO
#define servo_out_pin 21
#define motor_out_pin 7
//--------------------------------------------------------

// Functions to initialize and actuate Servo-------------------------------------------------------------------------------------------------
void initServo(){
  // Set data direction
  pinMode(servo_out_pin, OUTPUT);

  // Set PWM freq and resolution
  analogWriteFrequency(21,400); //Note this also changes PWM freq on LED pins to 400Hz 
  analogWriteFrequency(7,400); //Note this also changes PWM freq on LED pins to 400Hz 
  analogWriteRes(12);           //Note this also changes PWM res on all pins to 12 bit
}

// maps -500 to 500 to the appropriate pwm out for 1ms pulse to 2ms pulse
void writeServo(int16_t pos){
//  analogWrite(servo_out_pin, map(pos,-1500,1000,0,4096));
  analogWrite(servo_out_pin, map(pos,-500,500,1639,3279));
}

// maps -500 to 500 to the appropriate pwm out for 1ms pulse to 2ms pulse
void writetempMotor(int16_t pos){
  analogWrite(motor_out_pin, map(pos,-1500,1000,0,4096));
}
//-------------------------------------------------------------------------------------------------------------------------------
