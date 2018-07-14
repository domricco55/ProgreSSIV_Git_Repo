#ifndef __ULAREN_CAN_DRIVER_H__
#define __ULAREN_CAN_DRIVER_H__

#include "FlexCAN.h"

#define NO_ERROR 0
#define ERROR_CAN_WRITE 1

/*Define the data bytes available for selecting the modes of operation*/
#define PROFILE_VELOCITY_MODE 3
#define TORQUE_MODE 10

uint8_t reset_nodes();
uint8_t reset_communications();
uint8_t start_remote_nodes();
uint8_t set_torque_operating_mode();
uint8_t set_TxPDO1_inhibit_time();

uint8_t RxPDO1_controlword_write(uint16_t control_command);
uint8_t RxPDO2_torque_write(int node_id, uint16_t throttle);

void print_CAN_message(CAN_message_t msg);

//void check_available_msg();
//void process_available_msgs();
int  stop_remote_node(int node_id);

int  query_voltage_level(int node_id);
int  shutdown_MC(int node_id);

#endif



