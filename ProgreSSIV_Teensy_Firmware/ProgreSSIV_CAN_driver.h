#ifndef __ULAREN_CAN_DRIVER_H__
#define __ULAREN_CAN_DRIVER_H__

#include "FlexCAN.h"

/* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

/* Controlword values that drive the state transitions within the Device Control state machine. See EPOS4 Firmware Specification documentation for information on the controlword and state machine. */
#define SHUTDOWN_COMMAND 0x0006 //Controlword for shutdown. Takes the Device Control state machine from the "switch-on disabled" (post initialization state) to the "Ready to switch on" state. 
#define ENABLE_OP_COMMAND 0x000F //Controlword for switch on and enable. Puts Device Control state machine into "Operation enabled state" under MOST conditions. 
#define QUICKSTOP_COMMAND 0x000B //Controlword for Quick stop. Takes the Device Control state machine from the "Operation enabled" state to the "Quick stop active" state. The motors will decelerate to zero 
                                  //velocity at the quick stop deceleration value (index 0x6085). 
#define RESET_FAULT_COMMAND 0x0080 //Controlword for reset fault. Takes the Device Control state machine from the "fault" state to the "Switch on disabled state"
#define DISABLE_VOLT_COMMAND 0x0000 //Controlword for disabling voltage. Takes Device Control state machine form "quick stop active" to the "Switch on disabled state"

#define NO_ERROR 0
#define ERROR_CAN_WRITE 1
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
uint8_t set_torque_operating_mode();
uint8_t request_error_registers();
//uint8_t set_velocity_units();//I dont think you can actually set the velocity units :(
uint8_t set_TxPDO1_inhibit_time();
/*RECIEVE PROCESS DATA OBJECT (RxPDO) FUNCTIONS*/
uint8_t RxPDO1_controlword_write(uint16_t control_command);
uint8_t RxPDO2_torque_write(int node_id, uint16_t throttle);

void print_CAN_message(CAN_message_t msg);

#endif



