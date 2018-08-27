#ifndef __PROGRESSIV_MC_STATE_MACHINE_H__
#define __PROGRESSIV_MC_STATE_MACHINE_H__

#include <stdint.h>
#include "shares.h"
#include "ProgreSSIV_CAN_msg_handler.h"

/* Controlword values that drive the state transitions within the Device Control state machine.*/
#define SHUTDOWN_COMMAND 0x0006 //Controlword for shutdown. Takes the Device Control state machine from the "switch-on disabled" (post initialization state) to the "Ready to switch on" state. 
#define ENABLE_OP_COMMAND 0x000F //Controlword for switch on and enable. Puts Device Control state machine into "Operation enabled state" under MOST conditions. 
#define QUICKSTOP_COMMAND 0x000B //Controlword for Quick stop. Takes the Device Control state machine from the "Operation enabled" state to the "Quick stop active" state. The motors will decelerate to zero 
                                  //velocity at the quick stop deceleration value (index 0x6085). 
#define RESET_FAULT_COMMAND 0x0080 //Controlword for reset fault. Takes the Device Control state machine from the "fault" state to the "Switch on disabled state"
#define DISABLE_VOLTAGE_COMMAND 0x0000 //Controlword for disable voltage. Takes the Device Control state machine from the "quick stop active" state to the "Switch on disabled" state

///* Nodes 1 through 4 indicate which motor driver the firmware is talking to, CAN NODES*/
#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

#define MC_STATE_MACHINE_PRINT 1 

class MC_state_machine
{
  private:
  
  /*Class attributes*/
  
  //Give access to shared data via structs defined in shared.h
  SPI_commands_t *SPI_commands_struct;
  volatile int16_t *node_torques; 
  node_info_t *node_info; 
  radio_struct_t *radio_struct;

  //Gives access to a CAN_msg_handler object
  CAN_msg_handler *CAN_msg_handler_p;
  
  //For use by the state machine only, not shared with other tasks
  int32_t write_error_cnt; //Used for debugging CAN writes
  int32_t torque_write_attempts; //Used for debugging CAN writes
  unsigned long start_time_motors; //Used for motor update frequency
  int32_t saturated_casted_torques[4] = {0}; //Stores the torque actuation values from SPI task after saturating them and casting them into int32 types for use with CAN (the torque setpoint object of each node is 32 bit)
  
  
  /* State Machine state variable enum */
  enum MC_state{
  
    MC_state_0,  
    MC_state_1, 
    MC_state_2, 
    MC_state_3,
    MC_state_4,
    MC_state_5,
    MC_state_6,
    MC_state_7,
    MC_state_8,
    MC_state_9,
    MC_state_10,
    MC_state_11,
    MC_state_12
  
  } MC_state_var; //First state to be entered

  int16_t saturate_torque(int16_t torque_command); //Saturate the torque actuations to the max continuous torque for our motors
  
  public:
  
  MC_state_machine(SPI_commands_t *SPI_commands, volatile int16_t *node_torques, node_info_t *node_info, radio_struct_t *radio_struct, CAN_msg_handler *CAN_msg_handler_p); //Prototype of the constructor. 
  void run_sm(); //Run the state machine

}; 

#endif



