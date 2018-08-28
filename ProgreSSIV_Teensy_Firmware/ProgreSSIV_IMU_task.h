/** @file ProgreSSIV_IMU_task.h
 *  
 *  @brief Adafruit BN055 data gathering task h file.  
 *  @details
 *  
 *  @copyright
 *  
 *  
 */

#ifndef __PROGRESSIV_IMU_TASK_H__
#define __PROGRESSIV_IMU_TASK_H__

#include <stdint.h>
#include "shares.h"
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055_ProgreSSIV.h"
#include "imumaths.h"

#define IMU_GENERAL_PRINT 0

/** @brief %Class for gathering sensor data from the BNO055 Inertial Measurement Unit.
 *  @details
 *  
 */
class IMU_task
{
  private:
  
    /*Give access to shared data via structs defined in shared.h*/
    SPI_sensor_data_t *SPI_sensor_data;
    SPI_commands_t *SPI_commands;
    flags_struct_t *flags_struct;
  
    /*Local use only*/
    // Declare an Adafruit_BNO055 object.
    Adafruit_BNO055 bno;

    /*Private Functions*/
    void reset_imu(); //Gets run if the imu_flag is non-zero
    
  public:
  
    IMU_task(SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data, flags_struct_t *flags_struct); 
    void take_data(); //normal operation - takes sensor data and calls reset_imu function if the flag is non-zero

}; 

#endif
