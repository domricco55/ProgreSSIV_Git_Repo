#ifndef __PROGRESSIV_SPI_TASK_H__
#define __PROGRESSIV_SPI_TASK_H__

/* SPI memory map setup definitions */
#define SPI_MODE0     0x00//00 mode0, 01 mode1
#define CS0           0x0A//0x0A //Should be 0x0A pin 10. changed from 0x01

#include <stdint.h>

class MC_state_machine
{
 private:


  /*Class attributes*/
  
  /* Spi Register Setup*/
  //Create a register struct to define data that will be read from, and written to over SPI. Values are volatile because the register map is being accessed during an interrupt
  //service routine
  typedef struct __attribute__ ((__packed__)) reg_struct {
    volatile uint8_t init_motor_controllers;
    volatile uint8_t reset_imu;//Will re-run the bno055 initialization code...the intitial conditions of the euler angle readings will change when you reset...may want to integrate this into the dead switch logic
    volatile uint8_t dead_switch;
    // IMU
    volatile int16_t euler_heading;
    volatile int16_t euler_roll;
    volatile int16_t euler_pitch;
    volatile int16_t accl_x;
    volatile int16_t gyro_x;
    volatile int16_t accl_y;
    volatile int16_t gyro_y;
    volatile int16_t accl_z;
    volatile int16_t gyro_z;
    //Servo and Radio
    volatile int16_t radio_throttle;
    volatile int16_t radio_steering;
    // Output/Actuation Registers
    volatile int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
    volatile int16_t servo_out;
    //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
    volatile int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
    //CAN Motor Controller Commands
    volatile uint8_t shutdown_MCs;//Not yet implemented but will need to be at some point.
    //CAN Error Code Registers
    volatile uint8_t node_errors[4];//Array of node error messages
    //CAN Statusword Registers 
    volatile uint8_t node_statuswords[4];//Array of node statuswords
  } reg_struct_t ;
  
  //Union type definition linking the above reg_struct type to a 128 byte array. This will allow the same memory to be accessed by both the struct and the array. The above reg_struct_t defines names and types
  //of variables that will be stored in the memory, or the "registers". The registers will be 128 bytes of memory that can be accessed in two different ways, one through the name as defined in the struct and
  //another by simply indexing an array
  typedef union __attribute__ ((__packed__)) reg_union {
  
    volatile uint8_t bytes[128];//Allocate 128 bytes of memory. The registers ARE these bytes.
  
    reg_struct_t reg_map; //Maps the 128 registers to data names and types as defined in the reg_struct above.
  
  } reg_union_t registers; 

  /*
    can access exact same data like this:
      registers.bytes[1]
    OR like this:
      registers.reg_map.init_motor_controllers
  */
  
  /* spi0_isr buffer related */
  volatile uint8_t spi_address_buf;//The address byte sent at the beginning of every spi message contains a 7 bit address and a single read/write bit, the MSB.
  volatile uint8_t spi_rw_bit;//stores the information of whether the master is sending a read or write message
  #define RW_MASK 0b10000000
  #define ADDRESS_MASK 0b01111111
  
  /*Spi Task/isr Flags */
  bool first_interrupt_flag = true;
  
  /* Teensy Status Byte */
  volatile uint8_t Teensy_Status_Byte = 25;//NOT YET IMPLEMENTED CODE TO HANDLE A TEENSY STATUS BYTE.

  /*SPI Debugging Setup*/
  // SPI Printing Related
  uint32_t first_pointer;
  uint32_t next_pointer;
  uint8_t message_cnt = 0x01;
  
  //These are used to tell how much time the isr is taking to run
  volatile long isrStartTime;
  volatile long isrEndTime;
  
  //These are used to tell how much time is elapsing between messages
  volatile long messageStartTime;
  volatile long message_delta_t;

  
 public:
 SPI_task(SPI_ *SPI_torque_actuations, node_info_t *CAN_read_struct ); //Prototype of the constructor
 void handle_registers(); //The register struct is being accessed by the spi0_isr, handle its data
};  

#endif



