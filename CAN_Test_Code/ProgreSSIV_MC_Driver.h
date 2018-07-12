#ifndef __ULAREN_CAN_DRIVER_H__
#define __ULAREN_CAN_DRIVER_H__

#include "FlexCAN.h"

#define NO_ERROR 0
#define ERROR_CAN_WRITE 1

/*Define the data bytes available for selecting the modes of operation*/
#define PROFILE_VELOCITY_MODE 3
#define TORQUE_MODE 10
//#define CURRENT_MODE 253 //0xfd


#define PRINT 1

#define SCALE_FACTOR 2

int  reset_nodes();
int  reset_communications();
int  start_remote_nodes();
int  set_torque_operating_mode(int node_id);

int controlword_operation_enabled(int node_id);

int  write_torque_and_enable_op(int node_id, int throttle);
void print_CAN_message(CAN_message_t msg);

int  send_statusword_request(int node_id);
//void check_available_msg();
//void process_available_msgs();
int  stop_remote_node(int node_id);

int  query_voltage_level(int node_id);
int  shutdown_MC(int node_id);

#endif



