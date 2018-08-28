/** @file shares.h
 *  
 *  @brief Shared data struct definitions  
 *  @details
 * 
 * This file contains struct definitions for structs containing data to be shared between tasks. The structs are initialized in @ref PrgreSSIV_Teensy_Firmware.cpp and each tasks constructor is handed pointers to the data contained in these structs. 
 * 
 *  @copyright
 *  
 *  
 */

#ifndef __SHARES_H__
#define __SHARES_H__

#include <stdint.h>
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Shared Variable Struct Definitions - allow all the different tasks to share data with each other*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/** @brief SPI actuations shared data
 *  
 *  @details
 *  Actuations received in the @ref SPI_task from Master are stored in a struct of this type. They are accessed by tasks that output the actuations such as the motor controller state machine and the servo. 
 *  
 */

typedef volatile struct SPI_actuations_struct { 

  int16_t node_torques[4];                                                                                                                      //!< Array of torque actuation setpoints for the Maxon Motor controllers. Entered into the @ref CAN_msg_handler::RxPDO2_torque_write function. 
  int16_t servo_out;                                                                                                                            //!< Servo out actuation. Entered into the @ref initServo() function. 
  
} SPI_actuations_t;

/** @brief SPI commands shared data
 *  
 *  @details
 *  Commands received in the @ref SPI_task from Master are stored in a struct of this type. For now, only the @ref MC_state_machine task class and the @ref IMU_task use this. 
 */
typedef volatile struct SPI_commands_struct {

  uint8_t init_motor_controllers;                                                                                                               //!< Tells Motor Controllers to initialize.
  uint8_t dead_switch;                                                                                                                          //!< Turns the dead switch feature on. 
  uint8_t reset_imu;                                                                                                                            //!< Tells the BNO055 Inertial Measurement Unit to reset. 
  
} SPI_commands_t;

/** @brief SPI sensor shared data
 *  
 *  @details
 *  Sensor readings from the IMU and Motor Controllers  are shared with @ref SPI_task via a struct of this type. 
 */
typedef volatile struct SPI_sensor_data_struct { 
  
  int16_t euler_heading;                                                                                                                        //!< Euler heading reading (1 degrees per 16 bits) from the BNO055 Inertial Measurement Unit.
  int16_t euler_roll;                                                                                                                           //!< Euler roll reading (1 degrees per 16 bits) from the BNO055 Inertial Measurement Unit.
  int16_t euler_pitch;                                                                                                                          //!< Euler pitch reading (1 degrees per 16 bits) from the BNO055 Inertial Measurement Unit.
  int16_t accl_x;                                                                                                                               //!< X acceleration reading (1 m/s^2 per 100 bits) from the BNO055 Inertial Measurement Unit.
  int16_t gyro_x;                                                                                                                               //!< X angular velocity reading (1 rot/s per 900 bits) from the BNO055 Inertial Measurement Unit.
  int16_t accl_y;                                                                                                                               //!< Y acceleration reading (1 m/s^2 per 100 bits) from the BNO055 Inertial Measurement Unit.
  int16_t gyro_y;                                                                                                                               //!< Y angular velocity reading (1 rot/s per 900 bits) from the BNO055 Inertial Measurement Unit.
  int16_t accl_z;                                                                                                                               //!< Z acceleration reading (1 m/s^2 per 100 bits) from the BNO055 Inertial Measurement Unit.
  int16_t gyro_z;                                                                                                                               //!< Z angular velocity reading (1 rot/s per 900 bits) from the BNO055 Inertial Measurement Unit.
  int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left            //!< Average motor angular velocity reading in RPM (from Maxon Motor digital encoders).
  
} SPI_sensor_data_t;

/** @brief Maxon Motor Controller node info
 *  
 *  @details
 *  Node operational information. Data like node status and error states are stored in a struct of this type. This information is recieved via CAN messages in the @ref CAN_msg_handler class. It is
 *  utilized mainly by the @ref MC_state_machine. 
 */
typedef volatile struct node_info_struct { 

  uint8_t bootup_count; //Holds the number of NMT boot up confirmations received from the nodes                                                 //!< Number of @ref NMT bootup confirmations recieved. 
  uint8_t op_mode_SDO_count; //Holds the number of operating mode set SDO message confirmations received from the nodes                         //!< Number of @ref SDO set operating mode confirmations received. 
  uint8_t inhibit_time_SDO_count; //Holds the number of inhibit time set SDO message confirmations received from the nodes                      //!< Number of @ref SDO set TxPDO1 Inhibit Time confirmations received.
  uint16_t node_statuswords[4]; //Holds the satusword of each node                                                                              //!< Array containing the Statuswords of each node. 
  uint16_t node_errors[4]; //Holds the error state of each node                                                                                 //!< Array containing the Error Register values of each node.
  uint8_t mode_of_op_displays[4]; //Holds the mode of operation object value of each node                                                       //!< Array containing the mode of operation display of each node. 
  
} node_info_t;

/** @brief Radio Receiver shared data
 *  
 *  @details
 *  Radio receiver throttle and steering readings are stored in a struct of this type. 
 */

typedef volatile struct radio_struct { 
  
  // throttle input value (ranges from ~-400 to 400) / defined in main
  int16_t THR_in;                                                                                                                               //!< Throttle input value from the radio. Ranges from -400 to 400.
  //steering input value (ranges from ~--350 to 350)  / defined in main
  int16_t ST_in;                                                                                                                                //!< Steering input value from the radio. Ranges from -350 to 350.
  
} radio_struct_t;

//Struct of flags that allow tasks to prompt other tasks to perform certain operations
typedef volatile struct flag_struct { 
  
  bool reset_imu_flag; //Allows IMU task to prompt SPI task to clear the imu_reset register                                                     //!< Flag @ref IMU_task uses to signal @ref SPI_task to clear the @ref reset_imu register. 
  
} flags_struct_t;

#endif
