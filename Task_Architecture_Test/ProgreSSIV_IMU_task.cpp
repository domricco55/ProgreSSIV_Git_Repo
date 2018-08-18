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

IMU_task::IMU_task(SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data){
  
  SPI_commands = SPI_commands;
  SPI_sensor_data = SPI_sensor_data;
  
  Adafruit_BNO055 bno = Adafruit_BNO055(); 
  
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

  
void IMU_task::take_data(){
  
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


  //MOVE THIS INTO AN INIT FUNTION IN THE BNO DRIVER FILE
//  //This code will cause the bno to initialize. If it did not, it will print the error message
//  if (!bno.begin()) {
//    if (GENERAL_PRINT) {
//      //There was a problem detecting the BNO055 ... check your connections
//      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
//      //while(1);
//    }
//  }
//  else {
//    if (GENERAL_PRINT) {
//      //Display the current IMU temperature
//      int8_t temp = bno.getTemp();
//      Serial.print("Current Temperature: ");
//      Serial.print(temp);
//      Serial.println(" C");
//      Serial.println("");
//      Serial.println("You may want to calibrate your bno055");
//    }
//    bno.setExtCrystalUse(true);
//  }

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
