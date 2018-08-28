/** @file ProgreSSIV_CAN_msg_handler.h
 *  
 *  @brief Maxon EPOS4 Motor Controller CANopen message handler h file.  
 *  @details
 *  
 *  @copyright
 *  
 *  @page CAN0pen_and_MMC CANopen and Maxon Motor Controller Information
 *  
 *  This file contains the ... 
 *  
 *  @section CAN CAN communication objects utilized
 *  
 *  @subsection NMT Network Management Object
 *  
 *  See [EPOS4 Communication Guide](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Communication-Guide-En.pdf) 
 *  "NMT Services" section 3.3.3.5.
 *  
 *  @subsection SDO Service Data Object
 *  
 *  See [EPOS4 Communication Guide](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Communication-Guide-En.pdf) 
 *  "SDO Object" section 3.3.3.2.
 *  
 *  @subsection PDO Process Data Object
 *  
 *  See [EPOS4 Communication Guide](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Communication-Guide-En.pdf) 
 *  "PDO Object" section 3.3.3.1.
 *  
 *  @subsection EMCY Emergency Object
 *  
 *  See [EPOS4 Communication Guide](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Communication-Guide-En.pdf) 
 *  "EMCY Object" section 3.3.3.4.
 *  
 *  For further explanation of the different communication object types, see <http://www.canopensolutions.com/english/about_canopen/about_canopen.shtml>
 *  
 *  @section MMC_sm Maxon Motor Controllers state machines
 *  
 *  @subsection NMT_sm Network Management state machine
 *  
 *  @subsection DC_sm Device Control state machine
 *  
 *  See [EPOS4 Firmware Specification](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Firmware-Specification-En.pdf) Device Control section 2.2. 
 */

#ifndef __PROGRESSIV_CAN_MSG_HANDLER_H__
#define __PROGRESSIV_CAN_MSG_HANDLER_H__

#include <stdint.h>
#include "shares.h"
#include "flexCAN.h"

/*Read related defines*/
#define CAN_FILTER_PRINT 1
#define CONFIGURATION_PRINT 1
#define DYNAMIC_PRINT 0

/*Write related defines*/
#define CORRECT 0
#define NOT_CORRECT 1

/*Define the data bytes available for selecting the modes of operation*/
#define PROFILE_VELOCITY_MODE 3                                                                                     //!< Profile Velocity Mode value for writing to a motor controller's Modes of Operation object. 
#define TORQUE_MODE 10                                                                                              //!< Torque Mode value for writing to a motor controller's Modes of Operation object.           

/** @brief %Class for broadcasting CAN messages to the bus and filtering received messages. 
 *  @details
 *  
 *  
 */
class CAN_msg_handler
{
  
  private:
  
    node_info_t *node_info; //Pointer to a node_info_t type struct. This task will fill it with node information such as statusword value and error messages.                                                           //!< brief
    volatile int16_t *node_rpms; //Pointer to an array of node rpms within an SPI_sensor_data_t type struct. This task will fill it with wheel velocities to be sent over spi.                                          //!< brief

    //Read Related 
    void filter_SDO(CAN_message_t &msg);                                                                                                                                                                                
    void filter_PDO(CAN_message_t &msg);                                                                                                                                                                                
    void filter_NMT(CAN_message_t &msg);
    void filter_EMCY(CAN_message_t &msg); 
    
  public:
  
    //Prototype of constuctor
    CAN_msg_handler(node_info_t *node_info, volatile int16_t *node_rpms);
    
    /*Read related*/
    void try_CAN_msg_filter();

    /*Write related*/
    //NETWORK MANAGEMENT (NMT) FUNCTIONS
    uint8_t reset_nodes();
    uint8_t reset_communications();
    uint8_t start_remote_nodes();
    uint8_t stop_remote_nodes();
    uint8_t enter_pre_operational();
    //SERVICE DATA OBJECT FUNCTIONS
    uint8_t SDO_set_operating_mode(uint8_t operating_mode);
    uint8_t set_TxPDO1_inhibit_time();
    uint8_t request_statuswords();
    //RECIEVE PROCESS DATA OBJECT (RxPDO) FUNCTIONS
    uint8_t RxPDO1_controlword_write(uint16_t control_command);
    uint8_t RxPDO2_torque_write(int node_id,int32_t torque);
    uint8_t RxPDO3_mode_and_TV_write(int node_id, uint8_t mode, int32_t target_velocity);
    //MISCELLANEOUS
    void print_CAN_message(CAN_message_t msg);
    uint8_t CAN_read_wait(unsigned long int timeout_millis);
    uint8_t CAN_write_wait(uint16_t timeout_millis, CAN_message_t &msg);
    void print_CAN_statistics();
    
 
};

#endif
