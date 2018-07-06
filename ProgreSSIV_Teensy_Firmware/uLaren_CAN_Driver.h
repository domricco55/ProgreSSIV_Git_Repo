#ifndef __ULAREN_CAN_DRIVER_H__
#define __ULAREN_CAN_DRIVER_H__

#include "FlexCAN.h"

#define NO_ERROR 0
#define ERROR_CAN_WRITE 1

/*Define the data bytes available for selecting the modes of operation*/
#define PROFILE_VELOCITY_MODE 3
#define TORQUE_MODE 10
//#define CURRENT_MODE 253 //0xfd


#define PRINT 0

#define SCALE_FACTOR 2

int  initialize_CAN();
int  initialize_MC(int node_id);
int  arm_MC(int node_id);
int  write_throttle_to_MC(int node_id, int throttle);
int  initiate_target_velocity (int node_id);
int  write_velocity(int node_id, int throttle);
void print_outgoing_CAN_message(CAN_message_t msg);
void print_incoming_CAN_message(CAN_message_t msg);
int  send_statusword_request(int node_id);
void check_available_msg();
int  reset_nodes();
void process_available_msgs();
int  stop_remote_node(int node_id);
int  diagnose_controller_message(CAN_message_t msg);
int  link_node(int node_id);
int  rearm_MC(int node_id);
int  query_voltage_level(int node_id);
int  shutdown_MC(int node_id);

#endif

