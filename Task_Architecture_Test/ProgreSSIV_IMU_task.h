#ifndef __PROGRESSIV_IMU_TASK_H__
#define __PROGRESSIV_IMU_TASK_H__

#include <stdint.h>
#include "shares.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055_ProgreSSIV.h"
#include "imumaths.h"

#define IMU_GENERAL_PRINT 0

class IMU_task
{
  private:
  
  //Give access to shared data via share structs defined in shared.h
  SPI_sensor_data_t *SPI_sensor_data;
  SPI_commands_t *SPI_commands;

  //Local use only
  /*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*BNO055 Inertial Measurement Unit Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Instantiate and initialize an Adafruit_BNO055 object. */
  Adafruit_BNO055 bno;
  public:
  
  IMU_task(SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data); 
  void take_data();
}; 

#endif
