/* CAN Firmware Functions made for Teensy 3.6 
	by    */

/*********************************/
/* current functionality works but re-initialization does not work*/
/*********************************/

#include "flexCAN.h"
#include "ProgreSSIV_CAN_write_driver.h"
#include <string.h>
#include "arduino.h"

#define CONFIGURATION_PRINT 1
#define DYNAMIC_PRINT 0


/* ---------------------------------------------------------NETWORK MANAGEMENT (NMT) FUNCTIONS----------------------------------------------------------------------------------------------------------------------*/

/* This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset (same effect as turning on and off the supply voltage).
 *  After the message is sent out, each node will reboot and once a node has entered the Pre-Operational state of the NMT Slave state machine, it will send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the reset was successful. See EPOS4 Communication Guide section 3.3.3.5, NMT Services.
*/
uint8_t reset_nodes()
{
  CAN_message_t msg;
  uint8_t error_count = 0; 

  //reset nodes NMT command
  msg.id = 0;//CAN_id for NMT or network management
  msg.ext = 0;//Signifies whether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 2;
  msg.buf[0] = 0x81;//Command specifier for NMT command "Reset Nodes"
  msg.buf[1] = 0;//Entering a Zero here means send to all nodes (otherwise it would be the node id here)

  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function. 
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }
    
  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (CONFIGURATION_PRINT)
    {

        Serial.println();
        Serial.println("------------------------------------------------------------");
        Serial.println();
        Serial.println("error CAN write during reset_nodes() function call. The CAN statistics are: ");
        Serial.println();
    }
    
  }
  if(error_count==0){
    if (CONFIGURATION_PRINT)
    { 

        Serial.println();
        Serial.println("Successful CAN write during reset_nodes() function call. The CAN statistics are: ");
        Serial.println();
    }
  }

  if(CONFIGURATION_PRINT){
    
    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");   
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    
  }

  return (1-error_count); //May want to change what each of these functions returns
}

/* This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset their communication parameters (cob-ids and such).
 *  After the message is sent out, each node will enter the Pre-Operational state of the NMT Slave state machine, it will also send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the communication reset was successful. 
 *  See EPOS4 Communication Guide section 3.3.3.5, NMT Services.
*/
uint8_t reset_communications()
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //reset communication NMT command
  msg.id = 0;//CAN_id for NMT or network management
  msg.ext = 0;//Signifies whether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 2;
  msg.buf[0] = 0x82;//Command specifier for NMT command "Reset Communication"
  msg.buf[1] = 0;//Entering a Zero here means send to all nodes (otherwise it would be the node id here)

  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function. 

  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }
    
  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (CONFIGURATION_PRINT)
    {

        Serial.println();
        Serial.println("------------------------------------------------------------");
        Serial.println();
        Serial.println("error CAN write during reset_communications() function call. The CAN statistics are: ");
        Serial.println();

    }
    
  }
  if(error_count == 0){
    
    if (CONFIGURATION_PRINT)
    { 

        Serial.println();
        Serial.println("Successful CAN write during reset_communications() function call. The CAN statistics are: ");
        Serial.println();
    }
  }
  
  if(CONFIGURATION_PRINT){
    
    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    
  }

  return (1-error_count); //May want to change what each of these functions returns
}

/*This function sends the Network Management (NMT) message for "Enter Pre-Operational". It will send the message that signals every node to enter the Pre-Operational state (from either
 * the Operational or Stopped states) of the NMT Slave state machine. There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes 
 * object dictionary will have been cleared as a result. Can check the Statusword for confirmation. In this state, SDO messages, Emergency objects, and NMT messages are permitted. 
 * See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t enter_pre_operational()
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //Enter Pre-Operational state CAN Message
  msg.id = 0;//COB-id for NMT or network management
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 2;
  msg.buf[0] = 0x80; //Command Specifier for "Enter Pre-Operational"
  msg.buf[1] = 0;//when set to zero, all slaves will be started

  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.

  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }

  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (CONFIGURATION_PRINT)
    {

        Serial.println();
        Serial.println("error CAN write during enter_pre_operational() function call. The CAN statistics are: ");
        Serial.println();
    }
    
  }
  if(error_count==0){
    
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during enter_pre_operational() function call");
        Serial.println();
    }
  }
  
  if(CONFIGURATION_PRINT){
    
    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    
  }
  
  return (1-error_count);
}

/*This function sends the Network Management (NMT) message for Starting Remote Nodes. It will send the message that signals every node to enter the Operational state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been set as a result. Can check the Statusword 
 * for confirmation. See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t start_remote_nodes()
{
	CAN_message_t msg;
  uint8_t error_count = 0;

	//"Start Remote Node CAN Message"
	msg.id = 0;//COB-id for NMT or network management
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
	msg.len = 2;
	msg.buf[0] = 0x01; //Command Specifier for "start_remote_node"
	msg.buf[1] = 0;//when set to zero, all slaves will react to the command
 
  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }
  
  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (CONFIGURATION_PRINT)
    {

        Serial.println();
        Serial.println("error CAN write during start_remote_nodes() function call. The CAN statistics are: ");
        Serial.println();
    }
  }
  
  if(error_count == 0){

    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during start_remote_nodes() function call");
        Serial.println();
    }
  }

  if(CONFIGURATION_PRINT){
    
    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    
  }
  
  return (1-error_count);
}

/*This function sends the Network Management (NMT) message for "Stop Remote Nodes". It will send the message that signals every node to enter the Stopped state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been cleared as a result. Can check the Statusword 
 * for confirmation. In this state, only NMT, Heartbeating, and Layer setting service messages are permitted.  
 * See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t stop_remote_nodes()
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //"Stop Remote Node CAN Message"
  msg.id = 0;//COB-id for NMT or network management
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 2;
  msg.buf[0] = 0x02; //Command Specifier for "Stop Remote Node"
  msg.buf[1] = 0;//when set to zero, all slaves will react to the command
 
  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  }
  
  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during stop_remote_nodes function call");
        Serial.println();
    }
    
  }
  if(error_count==0){
  
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during stop_remote_nodes function call");
        Serial.println();
    }
  }

  if(CONFIGURATION_PRINT){
    
    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    
  }

  return (1-error_count);
}


/* ---------------------------------------------------------SERVICE DATA OBJECT FUNCTIONS----------------------------------------------------------------------------------------------------------------------*/

/* This function sends the Servide Data Object (SDO) message for accessing the "Modes of Operation" object in the object dictionary of all 4 nodes. The function will attempt to write
 *  the message to one of the nodes and if successful it will wait up to 1 second for the SDO confirmation message to be returned by the node. It will do this for each node and 
 *  notify through a print statement if there was a read message timeout and one of the nodes did not respond to the message within 1 second of successfully sending it. This 
 *  should likely be changed from a print statement to some kind of error checking variable to be used by the main Teensy firmware's error code. See EPOS4 Firmware Specification
 *  pg 6-164 (Modes of Operation) and pg 3-38 (Cyclic Synchronous Torque mode). SDO's MUST BE 8 BYTES LONG
*/
uint8_t SDO_set_operating_mode(uint8_t operating_mode)
{
  CAN_message_t msg;
  uint8_t error_count = 0;
  
  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  } 
  
  //Send out 4 SDO's, one for each node to request a write to each's Operating Mode Object. Configures each to Torque mode
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
    msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
    msg.rtr = 0;//Remote Transmit Request bit is low
    msg.len = 8;
    msg.buf[0] = 0x2F; //Command specifier for expedited one byte write request
    msg.buf[2] = 0x60; //High byte of index for Modes of Operation dictionary object
    msg.buf[1] = 0x60; //Low byte of index for Modes of Operation dictionary object 
    msg.buf[3] = 0; //Sub-index
    msg.buf[4] = operating_mode; //Pound defined earlier. To set torque mode, write a 10
    msg.buf[5] = 0;//MUST WRITE ZEROES HERE
    msg.buf[6] = 0;//MUST WRITE ZEROES HERE
    msg.buf[7] = 0;//MUST WRITE ZEROES HERE
    
    if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
    {
      error_count++;
      if (CONFIGURATION_PRINT)
      {
  
          Serial.println();
          Serial.println("error CAN write during SDO_set_operating_mode() function call. The CAN statistics are: ");
          Serial.println();
      } 
    }
  }

  if(error_count == 0){
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("All CAN writes were successful during the SDO_set_operating_mode() function call");
        Serial.println();
    }
  }

  if(CONFIGURATION_PRINT){

    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");    
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();

  }
  
  return (4-error_count);//Probably want to have returned whether or not the confirmation SDO was recieved or not
}

/* This function will send out an SDO write message to the "Transmit PDO 1 parameter" object of each node and wait a maximum of 1 second for a confirmation message from each node to return. 
 *  The inhibit time is the minimum time between broadcasts of this particular PDO on each node. It is being set to a maximum frequency of about 180 hz. See EPOS4 Firmware Specification 
 *  pgs 6-85/86. For more information on Process Data Objects and inhibit time, see http://www.canopensolutions.com/english/about_canopen/pdo.shtml CANopen Basics - Process Data Exchange. 
*/
uint8_t set_TxPDO1_inhibit_time()
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
  } 
  
  //Set the TxPDO1 inhibit time for each node
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id;//SDO COB-id for the node
    msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
    msg.rtr = 0;//Remote Transmit Request bit is low
    msg.len = 8;
    msg.buf[0] = 0x2B;//Command specifier for writing 2 bytes
    msg.buf[2] = 0x18;//High byte of TxPDO1 Parameter Index
    msg.buf[1] = 0x00;//Low byte of TxPDO1 Parameter Index
    msg.buf[3] = 0x03;//Sub-index of TxPDO1 Parameter Object, the INHIBIT TIME
    msg.buf[5] = 0x00;//High byte of data is zero
    msg.buf[4] = 0x37;//Low byte of data -> 55 multiples of 100uS produces an inhibit time of 0.0055 seconds or 180hz
    msg.buf[6] = 0;//MUST WRITE ZEROES HERE
    msg.buf[7] = 0;//MUST WRITE ZEROES HERE    
    
    if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
    {
      error_count++;
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.println("error CAN write during set_TxPDO1_inhibit_time function call");
          Serial.println();
                
      } 
    }
  }

  if(error_count == 0){
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("All CAN writes were successful during the set_TxPDO1_inhibit_time function call");
        Serial.println();
    }
  }
  
  if(CONFIGURATION_PRINT){

    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();

  }  
  
  return (4-error_count);//Probably want to have returned whether or not the confirmation SDO was recieved or not
}

uint8_t request_statuswords()//This function requests the statusword of a node through SDO read request and confirmation.
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  Can0.clearStats(); //Want to look at the stats of this message alone
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
  
  if(CONFIGURATION_PRINT){
    
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();
    Serial.println();
  } 
  
  for(uint8_t node_id = 1; node_id <=4; node_id++)
  {
    
    //Send a statusword request to the node and wait for the SDO confirmation (will contain the nodes statusword). Mostly for debugging purposes. 
    msg.id = 0x600 + node_id;
    msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
    msg.rtr = 0;//Remote Transmit Request bit is low
    msg.len = 8;// Message length is 8 because I think I'm supposed to send 4 empty bytes during an SDO read request. Not certain this is necessary though.
    msg.buf[0] = 0x40;// Command Specifier for object dictionary read of 2 bytes
    msg.buf[2] = 0x60;
    msg.buf[1] = 0x41;
    msg.buf[3] = 0;//Sub-index
    msg.buf[4] = 0;//MUST WRITE ZEROES HERE  
    msg.buf[5] = 0;//MUST WRITE ZEROES HERE  
    msg.buf[6] = 0;//MUST WRITE ZEROES HERE  
    msg.buf[7] = 0;//MUST WRITE ZEROES HERE  
    //Must send zeros on a read request 

    if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
    {
      error_count++;
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during request_statusword function call, node: ");
          Serial.println(node_id);
          Serial.println();
                
      } 
    }
  }
  if(error_count==0){
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("All CAN writes were successful during the request_statusword function call");
        Serial.println();
    }
  }

  
  if(CONFIGURATION_PRINT){

    print_CAN_statistics();
    Serial.print("Overrun flag after function call: ");
    Serial.println(msg.flags.overrun);
    Serial.println();
    Serial.println("------------------------------------------------------------");
    Serial.println();

  } 
  
  return (4-error_count);
}

/* ---------------------------------------------------------RECEIVE PROCESS DATA OBJECT (RxPDO) FUNCTIONS------------------------------------------------------------------------------------------------------*/

//These messages should only be sent while nodes are in the NMT Slave state "Operational" and represent normal data transfer that happens on a pre-defined and consistent basis while the motor controllers 
//are operating. The RxPDO's currently set up are 1 and 2, one for the controlword and one for updating the torque setpoint. The RxPDO's here (and the TxPDO's the other nodes broadcast) are configured
//in EPOS studio at the moment but can be configured using SDO messages while the MC's are in NMT state Pre-Operational. 

/*
 * This function writes to the controlword of every node (one at a time in a for loop) using a Recieve Process Data Object message, RxPDO1 (cob-id designated by myself to be of 200 + node_id).  
 * It takes a control command which has been pound-defined in the .h file from a set of available command codes specified in the EPOS4 documentation. Writing a particular command code to the controlword of a 
 * node triggers a transition in the "Device Control" state machine. Each transition also triggers a change in the Statusword of each node. The function returns the number of SDO confirmations (nodes responded 
 * that they recieved the command) that were recieved back. See EPOS4 Firmware specification pg 2-13 for informatino on the "Device Control" state machine and Statusword and Controlword definitions and see 
 * pg 6-160 for information on the Controlword Object. 
 */
uint8_t RxPDO1_controlword_write(uint16_t control_command) //Send out the RxPDO1 message that updates the node's controlword object
{
  CAN_message_t msg;
  uint8_t error_count = 0;
  uint8_t command_HB = (uint8_t)(control_command >> 8); //Grab the high byte of the controlword value
  uint8_t command_LB = (uint8_t)(control_command); //Grab the low byte of the controlword value

  for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
    
    //CAN message to update the controlword value of the node.
    msg.id = 0x200 + node_id;//COB-id for RxPDO1 - defined using EPOS Studio software
    msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
    msg.rtr = 0;//Remote Transmit Request bit is low
    msg.len = 2;
    msg.buf[1] = command_HB;
    msg.buf[0] = command_LB;

    if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
    {
      error_count++;
      if (DYNAMIC_PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during RxPDO1_controlword_write function call, node ");
          Serial.println(node_id);
          Serial.println();
          
      }
    }
  }

  if(error_count == 0){
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN writes during RxPDO1_controlword_write function call");
        Serial.println();
        
    }
  }
  return (4-error_count);
}

/*
 * This function writes a PDO message to the CAN bus, RxPDO2 (cob-id designated by myself to be of 300 + node_id) and updates the "Target Torque" object of a motor controller's object dictionary. 
 * See EPOS4 Firmware Specification pg 6-167. 
 */
uint8_t RxPDO2_torque_write(int node_id, int32_t torque) //Send out the RxPDO1 message that updates the node's controlword object
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //RxPDO 2,updating the target torque
  msg.id = 0x300 + node_id; //COB-id of RxPDO 2 for this specific node
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 4;
  msg.buf[3] = (uint8_t)((torque & 0xFF000000) >> 24);
  msg.buf[2] = (uint8_t)((torque & 0x00FF0000) >> 16);  
  msg.buf[1] = (uint8_t)((torque & 0x0000FF00) >> 8);
  msg.buf[0] = (uint8_t)((torque & 0x000000FF));  

  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during RxPDO2_torque_write function call");
        Serial.println();
        
    }
    
  }
  
  if(error_count==0){
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during RxPDO2_torque_write function call");
        Serial.println();
        
    }
  }
  
  return (1-error_count);
}


/*
 * This function writes a PDO message to the CAN bus, RxPDO3 (cob-id designated by myself to be of 400 + node_id) and writes to the "Operating Mode" object as well as the "Target Velocity" object
 * of a motor controller's object dictionary. See EPOS4 Firmware Specification pg 6-164 and . 
 */
uint8_t RxPDO3_mode_and_TV_write(int node_id, uint8_t mode, int32_t target_velocity) //Send out an RxPDO3 message to write the operating the mode and the target velocity setpoint
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //RxPDO 2,updating the target torque
  msg.id = 0x400 + node_id; //COB-id of RxPDO 2 for this specific node
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 1;
  msg.buf[0] = mode;
  msg.buf[4] = (uint8_t)((target_velocity & 0xFF000000) >> 24);
  msg.buf[3] = (uint8_t)((target_velocity & 0x00FF0000) >> 16);  
  msg.buf[2] = (uint8_t)((target_velocity & 0x0000FF00) >> 8);
  msg.buf[1] = (uint8_t)((target_velocity & 0x000000FF));  

  if (Can0.write(msg) == 0)// If the CAN write was unsuccessful, set return variable accordingly
  {
    error_count++;
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during RxPDO3_mode_and_TV_write function call");
        Serial.println();
        
    }
    
  }
  
  if(error_count==0){
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during RxPDO3_mode_and_TV_write function call");
        Serial.println();
        
    }
  }
  
  return (1-error_count);
}

void read_available_message()//Can be used to clear out a stuffed receive buffer
{
  CAN_message_t msg;
  
  if(Can0.available()){
    if(CONFIGURATION_PRINT)
      {
      Serial.println();
      Serial.println("A CAN message was recieved during the read_available_messages function call ");
      Serial.println();
      print_CAN_message(msg);
    }
  }
}

void print_CAN_message(CAN_message_t msg)
{

  Serial.println();
  Serial.print("  ID: ");
  Serial.println(msg.id, HEX);
  Serial.print("  Length: ");
  Serial.println(msg.len);
  Serial.print("  Byte[0]: ");
  Serial.println(msg.buf[0], HEX);
  Serial.print("  Byte[1]: ");
  Serial.println(msg.buf[1], HEX);
  Serial.print("  Byte[2]: ");
  Serial.println(msg.buf[2], HEX);
  Serial.print("  Byte[3]: ");
  Serial.println(msg.buf[3], HEX);
  Serial.print("  Byte[4]: ");
  Serial.println(msg.buf[4], HEX);
  Serial.print("  Byte[5]: ");
  Serial.println(msg.buf[5], HEX);
  Serial.print("  Byte[6]: ");
  Serial.println(msg.buf[6], HEX);
  Serial.print("  Byte[7]: ");
  Serial.println(msg.buf[7], HEX);
  Serial.println();
  
}

uint8_t CAN_read_wait(unsigned long int timeout_millis){

  unsigned long int startMillis = millis();
  while( !Can0.available() ) {
    if ( !timeout_millis || (timeout_millis<=(millis()-startMillis)) ) {
      // early EXIT nothing here
      return 0;
    }
  }

  return 1;
}

uint8_t CAN_write_wait(uint16_t timeout_millis, CAN_message_t &msg){
  
  unsigned long int startMillis = millis();
  while( !Can0.write(msg) ) {
    if ( !timeout_millis || (timeout_millis<=(millis()-startMillis)) ) {
      // early EXIT nothing here
      return 0;
    }
  }

  return 1;
}

void print_CAN_statistics(){
  
    CAN_stats_t my_CAN_stats = Can0.getStats();
    Serial.println();
    Serial.println("The current CAN statistics are: ");
    Serial.println();
    Serial.print("  Stats enabled parameter: ");
    Serial.println(my_CAN_stats.enabled);
    Serial.print("  Stats ringRxFramesLost: ");
    Serial.println(my_CAN_stats.ringRxFramesLost);
    Serial.print("  Stats ringRxmax: ");
    Serial.println(my_CAN_stats.ringRxMax);  
    Serial.print("  Stats ringRxHighWater: ");
    Serial.println(my_CAN_stats.ringRxHighWater);
    Serial.print("  Stats ringTxMax: ");
    Serial.println(my_CAN_stats.ringTxMax);  
    //Serial.print("  Stats ringTxHighWater: ");
    Serial.println("  I dont think the transfer buffer or mailbox use statistics are working at the moment.");
//
//    Serial.print("  Stats Mailbox 0 Use Count: ");
//    Serial.println(my_CAN_stats.mb[0].refCount);
//    Serial.print("  Stats Mailbox 1 Use Count: ");
//    Serial.println(my_CAN_stats.mb[1].refCount);
//    Serial.print("  Stats Mailbox 2 Use Count: ");
//    Serial.println(my_CAN_stats.mb[2].refCount);
//    Serial.print("  Stats Mailbox 3 Use Count: ");
//    Serial.println(my_CAN_stats.mb[3].refCount);
//    Serial.print("  Stats Mailbox 4 Use Count: ");
//    Serial.println(my_CAN_stats.mb[4].refCount);
//    Serial.print("  Stats Mailbox 5 Use Count: ");
//    Serial.println(my_CAN_stats.mb[5].refCount);
//    Serial.print("  Stats Mailbox 6 Use Count: ");
//    Serial.println(my_CAN_stats.mb[6].refCount);
//    Serial.print("  Stats Mailbox 7 Use Count: ");
//    Serial.println(my_CAN_stats.mb[7].refCount);
//    Serial.print("  Stats Mailbox 8 Use Count: ");
//    Serial.println(my_CAN_stats.mb[8].refCount);
//    Serial.print("  Stats Mailbox 9 Use Count: ");
//    Serial.println(my_CAN_stats.mb[9].refCount);
//    Serial.print("  Stats Mailbox 10 Use Count: ");
//    Serial.println(my_CAN_stats.mb[10].refCount);
//    Serial.print("  Stats Mailbox 11 Use Count: ");
//    Serial.println(my_CAN_stats.mb[11].refCount);
//    Serial.print("  Stats Mailbox 12 Use Count: ");
//    Serial.println(my_CAN_stats.mb[12].refCount);
//    Serial.print("  Stats Mailbox 13 Use Count: ");
//    Serial.println(my_CAN_stats.mb[13].refCount);
//    Serial.print("  Stats Mailbox 14 Use Count: ");
//    Serial.println(my_CAN_stats.mb[14].refCount);
//    Serial.print("  Stats Mailbox 15 Use Count: ");
//    Serial.println(my_CAN_stats.mb[15].refCount);
//    Serial.print("  Stats Mailbox 14 Overrun Count: ");
//    Serial.println(my_CAN_stats.mb[14].overrunCount);
//    Serial.print("  Stats Mailbox 15 Overrun Count: ");
//    Serial.println(my_CAN_stats.mb[15].overrunCount);
    Serial.println();  
}

