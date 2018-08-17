#ifndef __SHARES_H__
#define __SHARES_H__

#include <stdint.h>
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Shared Variable Struct Definitions - allow all the different tasks to share data with each other*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

typedef struct SPI_actuations {

  int16_t SPI_torque_actuations[4];
  int16_t SPI_steering_command;
  
} SPI_actuations_t;

typedef struct SPI_commands {

  uint8_t init_motor_controllers;
  uint8_t dead_switch;
  uint8_t reset_imu;
  
} SPI_commands_t;

typedef struct sensor_data{
    volatile int16_t euler_heading;
    volatile int16_t euler_roll;
    volatile int16_t euler_pitch;
    volatile int16_t accl_x;
    volatile int16_t gyro_x;
    volatile int16_t accl_y;
    volatile int16_t gyro_y;
    volatile int16_t accl_z;
    volatile int16_t gyro_z;
    volatile int16_t radio_throttle;
    volatile int16_t radio_steering;
    volatile int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
} SPI_sensor_data_t;

typedef struct node_info {

      uint8_t bootup_count; 
      uint8_t op_mode_SDO_count;
      uint8_t inhibit_time_SDO_count;
      uint16_t node_statuswords[4];
      uint16_t node_errors[4];
  
} node_info_t;



#endif
