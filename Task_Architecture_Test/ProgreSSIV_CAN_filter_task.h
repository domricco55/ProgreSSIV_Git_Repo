#ifndef __PROGRESSIV_CAN_FILTER_TASK_H__
#define __PROGRESSIV_CAN_FILTER_TASK_H__

#include <stdint.h>
#include "shares.h"
#include "flexCAN.h"
//#include "arduino.h"

#define CAN_FILTER_PRINT 0

class CAN_filter_task
{
  
  private:
  
    node_info_t *node_info; //Pointer to a node_info_t type struct. This task will fill it with node information such as statusword value and error messages.
    int16_t *node_rpms; //Pointer to an array of node rpms within an SPI_sensor_data_t type struct. This task will fill it with wheel velocities to be sent over spi.
      
    void filter_SDO(CAN_message_t &msg);
    void filter_PDO(CAN_message_t &msg);
    void filter_NMT(CAN_message_t &msg);
    void filter_EMCY(CAN_message_t &msg);    
    
  public:

    CAN_filter_task(node_info_t *node_info, int16_t *node_rpms);
    void try_CAN_msg_filter();
 
};

#endif
