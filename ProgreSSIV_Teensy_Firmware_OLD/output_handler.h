/* 
 *  This .h file defines function and class prototypes that are referenced in the main program file
 */
 
// Servo PWM initialization 
void initServo();
  // Pass writeServo -500 to 500 and have it mapped to full left to full right
void writeServo(int16_t pos);

  // Pass writetempMotor -500 to 500 and have it mapped to full reverse to full forward
void writetempMotor(int16_t pos);
//--------------------------------



