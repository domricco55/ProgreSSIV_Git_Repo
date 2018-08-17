#ifndef __PROGRESSIV_CAN_DRIVER_H__
#define __PROGRESSIV_CAN_DRIVER_H__

#include "FlexCAN.h"

///* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

#define CORRECT 0
#define NOT_CORRECT 1

/*Define the data bytes available for selecting the modes of operation*/
#define PROFILE_VELOCITY_MODE 3
#define TORQUE_MODE 10

/*NETWORK MANAGEMENT (NMT) FUNCTIONS*/
uint8_t reset_nodes();
uint8_t reset_communications();
uint8_t start_remote_nodes();
uint8_t stop_remote_nodes();
uint8_t enter_pre_operational();
/*SERVICE DATA OBJECT FUNCTIONS*/
uint8_t SDO_set_operating_mode(uint8_t operating_mode);
uint8_t set_TxPDO1_inhibit_time();
uint8_t request_statuswords();
uint8_t request_error_registers();
/*RECIEVE PROCESS DATA OBJECT (RxPDO) FUNCTIONS*/
uint8_t RxPDO1_controlword_write(uint16_t control_command);
uint8_t RxPDO2_torque_write(int node_id,int32_t torque);
uint8_t RxPDO3_mode_and_TV_write(int node_id, uint8_t mode, int32_t target_velocity);
/*MISCELLANEOUS*/
void read_available_message();
void print_CAN_message(CAN_message_t msg);
uint8_t CAN_read_wait(unsigned long int timeout_millis);
uint8_t CAN_write_wait(uint16_t timeout_millis, CAN_message_t &msg);
void print_CAN_statistics();


#endif



