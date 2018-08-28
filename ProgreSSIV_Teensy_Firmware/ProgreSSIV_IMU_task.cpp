/** @file ProgreSSIV_IMU_task.cpp
 *  
 *  @brief Adafruit BN055 data gathering task cpp file.  
 *  @details
 *  
 *  @copyright
 *  
 *  
 */

/* Adafruint BNO055 sensor data gathering task designed by Dominic Riccoboni 
of the ProgreSSIV senior project team - Cal Poly San Luis Obispo  */

/*********************************/

#include "ProgreSSIV_IMU_task.h"
#include "ProgreSSIV_IMU_task.h"

/*General Debugging*/
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

/** @brief %IMU_task constructor.
 *  @details
 *  
 *  @param SPI_commands Pointer to an SPI_commands_t shared data struct. 
 *  @param SPI_sensor_data Pointer to an SPI_sensor_data_t shared data struct.  
 *  @param flags_struct Pointer to a flags_struct_t shared data struct. 
 */
IMU_task::IMU_task(SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data, flags_struct_t *flags_struct):

  SPI_commands(SPI_commands),
  SPI_sensor_data(SPI_sensor_data),
  flags_struct(flags_struct)//Initializer list  
  {
  
  bno = Adafruit_BNO055(); 
  
  //This code will cause the bno to initialize. If it did not, it will print the error message
  if (!bno.begin()) {
    if (IMU_GENERAL_PRINT) {
      //There was a problem detecting the BNO055 ... check your connections
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      //while(1);
    }
  }
  else {
    if (IMU_GENERAL_PRINT) {
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
}

  
void IMU_task::take_data(){
  //Gather the IMU sensor data. These functions are from Adafruit_BNO055_ProgreSSIV.cpp
  
  uint8_t bno_buffer[6]; //Used to store the I2C message containting the imu data

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_EULER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of EULER data

  //Load the struct with the I2C euler data (concatinate high and low byte before putting the value in)
  SPI_sensor_data -> euler_heading = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  SPI_sensor_data -> euler_roll = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  SPI_sensor_data -> euler_pitch = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_ACCELEROMETER, bno_buffer, 6); //Send and I2C message to request the 6 bytes of ACCELEROMETER data

  //Load the struct with the I2C acceleration data (concatinate high and low byte before putting the value in)
  SPI_sensor_data -> accl_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  SPI_sensor_data -> accl_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  SPI_sensor_data -> accl_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

  bno.readLen((Adafruit_BNO055::adafruit_bno055_reg_t)Adafruit_BNO055::VECTOR_GYROSCOPE, bno_buffer, 6); //Send and I2C message to request the 6 bytes of GYROSCOPE data

  //Load the struct with the I2C gyroscope data (concatinate high and low byte before putting the value into the register)
  SPI_sensor_data -> gyro_x = ((int16_t)bno_buffer[0]) | (((int16_t)bno_buffer[1]) << 8);
  SPI_sensor_data -> gyro_y = ((int16_t)bno_buffer[2]) | (((int16_t)bno_buffer[3]) << 8);
  SPI_sensor_data -> gyro_z = ((int16_t)bno_buffer[4]) | (((int16_t)bno_buffer[5]) << 8);

 if (SPI_commands -> reset_imu){
  reset_imu();
  SPI_commands -> reset_imu = 0;
  flags_struct -> reset_imu_flag = true;
 }

} 

void IMU_task::reset_imu(){

  if (!bno.begin()) { //This code will cause the bno to initialize. If it did not, it will print the error message
    if (IMU_GENERAL_PRINT) {
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!"); //Should likely add some error handling code here. Nothing to protect for this occurence.
    }
  }
  else {
    if (IMU_GENERAL_PRINT) {
      //Display the current IMU temperature
      int8_t temp = bno.getTemp();
      Serial.print("Current Temperature: ");
      Serial.print(temp);
      Serial.println(" C");
      Serial.println("");
      Serial.println("You may want to calibrate your bno055");
    }
  }
}

//THINK ABOUT WHAT TO DO HERE -> THE IMU FLAG IS BEING LOWERED HERE BUT THE SPI TASK MAY JUST RAISE IT AGAIN EVEN IF SPI MASTER HASNT RAISED IT. MAYBE I SHOULD GIVE THIS TASK 
//DIRECT ACCESS TO THE REGISTERS OR MAYBE I SHOULD HAVE THE SPI TASK ITSELF CALL A FUNCTION OF THE IMU TASK AND HAVE IT CLEAR THE FLAG ITSELF AFTER!!! YES THIS IS MUCH BETTER...DO 
//THIS FOR ALL COMMANDS

//Wait, this scheme wont work well for flag type commands that dont have an immediate function to run such as the motor_controllers_on flag...In SPI task, I could only update the state
//of the struct if the SPI command register value is different than that in the struct -> if value has a 1 when there is already a 1 in the struct then don't update

