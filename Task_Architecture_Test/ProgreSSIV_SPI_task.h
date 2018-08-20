#ifndef __PROGRESSIV_SPI_TASK_H__
#define __PROGRESSIV_SPI_TASK_H__

/* SPI memory map setup definitions */
#define SPI_MODE0     0x00//00 mode0, 01 mode1
#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

#include <stdint.h>
#include "shares.h"
#include "arduino.h"

/* Spi Register Setup*/
//Create register structs to define data that will be read from, and written to over SPI. Write values are volatile because they can be written to in an interrupt service routine
typedef struct __attribute__ ((__packed__)) reg_struct_read {
  // IMU
  int16_t euler_heading;
  int16_t euler_roll;
  int16_t euler_pitch;
  int16_t accl_x;
  int16_t gyro_x;
  int16_t accl_y;
  int16_t gyro_y;
  int16_t accl_z;
  int16_t gyro_z;
  //Servo and Radio
  int16_t radio_throttle;
  int16_t radio_steering;
  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
  int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
  uint8_t node_errors[4];//Array of node error messages
  //CAN Statusword Registers 
  uint8_t node_statuswords[4];//Array of node statuswords
} reg_read_struct_t;

typedef struct __attribute__ ((__packed__)) reg_struct_write {
  volatile uint8_t init_motor_controllers;
  volatile uint8_t reset_imu;//Will re-run the bno055 initialization code...the intitial conditions of the euler angle readings will change when you reset...may want to integrate this into the dead switch logic
  volatile uint8_t dead_switch;
  volatile int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
  volatile int16_t servo_out;
  volatile uint8_t shutdown_MCs;//Not yet implemented but will need to be at some point.
} reg_write_struct_t;

//Union type definition linking the above struct types to a 128 byte array. This will allow the same memory to be accessed by both the struct and the array. The above struct types define names and types
//of variables that will be stored in the memory, or the "registers". The registers will be 128 bytes of memory that can be accessed in two different ways, one through the names as defined in the structs and
//another by indexing an array
typedef union __attribute__ ((__packed__)) reg_union {

  volatile uint8_t bytes[128];//Allocate 128 bytes of memory. The registers ARE these bytes.

  reg_read_struct_t reg_map_read; //Maps the read registers to data names and types as defined in the reg_struct above.
  reg_write_struct_t reg_map_write; //Maps the write registers to data names and types as defined in the reg_struct above.
  
} reg_union_t;

/* CLASS DEFINITION */
class SPI_task
{
 private:

  /*Shared variable structs*/
  SPI_actuations_t *SPI_actuations;
  SPI_commands_t *SPI_commands;
  SPI_sensor_data_t *SPI_sensor_data;
  node_info_t *node_info;
  radio_struct_t *radio_struct;

  /*Registers union*/
  reg_union_t *registers;

  /*Spi Task/isr Flags*/
  bool first_interrupt_flag = true;
  bool updating_write_only;
  /*
   *  can access exact same data like this:
   *    registers.bytes[1]
   *  OR like this:
   *    registers.reg_map.init_motor_controllers
   */
  
  /* spi0_isr buffer related */
  volatile uint8_t spi_address_buf;//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
  volatile uint8_t spi_rw_bit;//stores the information of whether the master is sending a read or write message
  #define RW_MASK 0b10000000
  #define ADDRESS_MASK 0b01111111
  reg_union_t *registers_buf; 

  
  /* Teensy Status Byte */ 
  volatile uint8_t Teensy_Status_Byte = 25;//NOT YET IMPLEMENTED CODE TO HANDLE A TEENSY STATUS BYTE.

  /*SPI Debugging Setup*/
  
  /* SPI Printing Related*/
  uint8_t message_cnt = 0x01;
  
  /*These are used to tell how much time the isr is taking to run*/
  volatile long isrStartTime;
  volatile long isrEndTime;
  
  /*These are used to tell how much time is elapsing between messages*/
  volatile long messageStartTime = 0;
  volatile long message_delta_t = 0;

  /*Private Function Prototypes*/
  void spi_slave_init(void);
  void spi_debug(void);

  
 public:

  /*Public Function Prototypes*/
  SPI_task(SPI_actuations_t *SPI_actuations, SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data, node_info_t *node_info, radio_struct_t *radio_struct); //Prototype of the constructor
  void spi0_callback(void);
  void spi_transfer_complete_isr(void);
  void handle_registers(); //The register struct is being accessed by the spi0_isr, handle its data
  void spi_registers_print(void);

};  

#endif



