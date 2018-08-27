#ifndef __SHARES_H__
#define __SHARES_H__

#include <stdint.h>
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Shared Variable Struct Definitions - allow all the different tasks to share data with each other*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
 * This file contains struct definitions for structs containing data to be shared between tasks. Each tasks constructor is handed pointers to the data contained in these structs. 
 */

//Actuations received from the SPI task from Master are stored here. They are accessed by tasks that output the actuations such as the motor controller state machine and the servo task. 
typedef volatile struct SPI_actuations_struct { 

  int16_t node_torques[4];
  int16_t servo_out;
  
} SPI_actuations_t;

typedef volatile struct SPI_commands_struct {

  uint8_t init_motor_controllers;
  uint8_t dead_switch;
  uint8_t reset_imu;
  
} SPI_commands_t;

//Sensor readings are stored and updated in this struct
typedef volatile struct SPI_sensor_data_struct { 
  
  int16_t euler_heading;
  int16_t euler_roll;
  int16_t euler_pitch;
  int16_t accl_x;
  int16_t gyro_x;
  int16_t accl_y;
  int16_t gyro_y;
  int16_t accl_z;
  int16_t gyro_z;
  int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
  
} SPI_sensor_data_t;

//Motor Controller operation information is stored in this struct
typedef volatile struct node_info_struct { 

  uint8_t bootup_count; //Holds the number of NMT boot up confirmations received from the nodes
  uint8_t op_mode_SDO_count; //Holds the number of operating mode set SDO message confirmations received from the nodes
  uint8_t inhibit_time_SDO_count; //Holds the number of inhibit time set SDO message confirmations received from the nodes
  uint16_t node_statuswords[4]; //Holds the satusword of each node
  uint16_t node_errors[4]; //Holds the error state of each node
  uint8_t mode_of_op_displays[4]; //Holds the mode of operation object value of each node
  
} node_info_t;

//Radio transeiver throttle and steering readings are stored in this struct
typedef volatile struct radio_struct { 
  
  // throttle input value (ranges from ~-500 to 500) / defined in main
  int16_t THR_in;
  //steering input value (ranges from ~-500 to 500)  / defined in main
  int16_t ST_in;
  
} radio_struct_t;

//Struct of flags that allow tasks to prompt other tasks to perform certain operations
typedef volatile struct flag_struct { 
  
  bool reset_imu_flag; //Allows IMU task to prompt SPI task to clear the imu_reset register
  
} flags_struct_t;

#endif
