/* CAN Firmware Functions made for Teensy 3.6 
	by the uLaren Senior Project Team    */

/*********************************/
/* current functionality works but re-initialization does not work*/
/*********************************/

#include "flexCAN.h"
#include "ProgreSSIV_CAN_driver.h"
#include <string.h>

#define CONFIGURATION_PRINT 1
#define DYNAMIC_PRINT 1

extern FlexCAN CANbus;

/* ---------------------------------------------------------NETWORK MANAGEMENT (NMT) FUNCTIONS----------------------------------------------------------------------------------------------------------------------*/

/* This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset (same effect as turning on and off the supply voltage).
 *  After the message is sent out, each node will reboot and once a node has entered the Pre-Operational state of the NMT Slave state machine, it will send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the reset was successful. See EPOS4 Communication Guide section 3.3.3.5, NMT Services.
*/
uint8_t reset_nodes()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR; //This variable is being returned by the function and signals whether a successful CAN write occured or not. Error checking variable that may change later. 
  uint8_t bootup_count = 0; //This variable will keep track of the number of node NMT boot up confirmations recieved. 

  //reset nodes NMT command
  msg.id = 0;//CAN_id for NMT or network management
  msg.ext = 0;//Default is zero and I'm not sure what this does so I'm keeping it at zero always
  msg.len = 2;
  msg.buf[0] = 0x81;//Command specifier for NMT command "Reset Nodes"
  msg.buf[1] = 0;//Entering a Zero here means send to all nodes (otherwise it would be the node id here)

  msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during reset_nodes() function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (CONFIGURATION_PRINT)
    { 
        Serial.println();
        Serial.println("Successful CAN write during reset_nodes() function call");
        Serial.println();
        delay(500);
    }
  }

  if(ret == NO_ERROR){//If the CAN write was successful, attempt to read the boot up messages from the CAN bus 
    
    //The following code will filter out each node's boot up confirmation from other messages that may be in the CAN read buffer. It expects 4 total boot up confirmations
    for(uint8_t index = 1; index <= 4 ; index++){

      msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message (wait a maximum of 1000 milliseconds, the timeout period, for a read message to arrive
      if (CANbus.read(msg) == 0){//If the read message timeout was reached and a message was not available to read.
        
        if(CONFIGURATION_PRINT)
        {
          Serial.println();
          Serial.println("A read message timeout has occured during the reset_nodes function call. One of the nodes may not be on the CAN bus.");
          Serial.println();
        }
        
      }
      
      else{//Else, the read message timeout wasn't reached and a message was available to read.
        if(msg.id == 0x701 || msg.id == 0x702 || msg.id == 0x703 || msg.id == 0x704){// If the recieved message is a nodes NMT boot up message, the COB-id will be between 0x701 and 0x704
          
          bootup_count++; //A bootup message has been recieved, increment the bootup count.
          
          if(CONFIGURATION_PRINT)
            {
            Serial.println();
            Serial.println("An NMT boot up confirmation has been recieved during the reset_nodes function call. The recieved message is: ");
            Serial.println();
            print_CAN_message(msg);
            }
        }
        
        else{// Else the recieved message was not an NMT boot up message and what was recieved may be a lingering PDO or an SDO response or something. 

          index--; //Decrement the index so that this non-boot-up message is ignored and the for loop will iterate the proper number of times
          Serial.print("A non-boot up message was recieved during the reset_nodes function call and was ignored. The COB-id was: ");
          Serial.println(msg.id, HEX);
          
        } 
      }
    }
  }
  return ret; //May want to change what each of these functions returns
}

/* This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset their communication parameters (cob-ids and such).
 *  After the message is sent out, each node will enter the Pre-Operational state of the NMT Slave state machine, it will also send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the communication reset was successful. 
 *  See EPOS4 Communication Guide section 3.3.3.5, NMT Services.
*/
uint8_t reset_communications()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR; //This variable is being returned by the function and signals whether a successful CAN write occured or not. Error checking variable that may change later. 
  uint8_t bootup_count = 0; //This variable will keep track of the number of node NMT boot up confirmations recieved. 

  //reset communication NMT command
  msg.id = 0;//CAN_id for NMT or network management
  msg.ext = 0;//Default is zero and I'm not sure what this does so I'm keeping it at zero always
  msg.len = 2;
  msg.buf[0] = 0x82;//Command specifier for NMT command "Reset Communication"
  msg.buf[1] = 0;//Entering a Zero here means send to all nodes (otherwise it would be the node id here)

  msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during reset_communication() function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during reset_communication() function call");
        Serial.println();
        delay(500);
    }
  }

  if(ret == NO_ERROR){//If the CAN write was successful, attempt to read the boot up messages from the CAN bus 
    
    //The following code will filter out each node's boot up confirmation from other messages that may be in the CAN read buffer. It expects 4 total boot up confirmations
    for(uint8_t index = 1; index <= 4 ; index++){

      msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message (wait a maximum of 1000 milliseconds, the timeout period, for a read message to arrive
      if (CANbus.read(msg) == 0){//If the read message timeout was reached and a message was not available to read.
        
        if(CONFIGURATION_PRINT)
        {
          Serial.println();
          Serial.println("A read message timeout has occured during the reset_communications function call. One of the nodes may not be on the CAN bus.");
          Serial.println();
        }
        
      }
      
      else{//Else, the read message timeout wasn't reached and a message was available to read.
        if(msg.id == 0x701 || msg.id == 0x702 || msg.id == 0x703 || msg.id == 0x704){// If the recieved message is a nodes NMT boot up message, the COB-id will be between 0x701 and 0x704
          
          bootup_count++; //A bootup message has been recieved, increment the bootup count.
          
          if(CONFIGURATION_PRINT)
            {
            Serial.println();
            Serial.println("An NMT boot up confirmation has been recieved during the reset_communications function call. The recieved message is: ");
            Serial.println();
            print_CAN_message(msg);
            }
        }
        
        else{// Else the recieved message was not an NMT boot up message and what was recieved may be a lingering PDO or an SDO response or something. 

          index--; //Decrement the index so that this non-boot-up message is ignored and the for loop will iterate the proper number of times
          Serial.print("A non-boot up message was recieved during the reset_communications function call and was ignored. The COB-id was: ");
          Serial.println(msg.id, HEX);
          
        } 
      }
    }
  }
  
  return ret; //May want to change what each of these functions returns
}

/*This function sends the Network Management (NMT) message for "Enter Pre-Operational". It will send the message that signals every node to enter the Pre-Operational state (from either
 * the Operational or Stopped states) of the NMT Slave state machine. There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes 
 * object dictionary will have been cleared as a result. Can check the Statusword for confirmation. In this state, SDO messages, Emergency objects, and NMT messages are permitted. 
 * See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t enter_pre_operational()
{
  CAN_message_t msg;
  uint8_t ret = 0;

  //Enter Pre-Operational state CAN Message
  msg.id = 0;//COB-id for NMT or network management
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x80; //Command Specifier for "Enter Pre-Operational"
  msg.buf[1] = 0;//when set to zero, all slaves will be started
 

  msg.timeout = 1000;//Milliseconds before giving up on broadcasting CAN message
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during enter_pre_operational function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during enter_pre_operational function call");
        Serial.println();
        delay(500);
    }
  }
  return ret;

}

/*This function sends the Network Management (NMT) message for Starting Remote Nodes. It will send the message that signals every node to enter the Operational state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been set as a result. Can check the Statusword 
 * for confirmation. See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t start_remote_nodes()
{
	CAN_message_t msg;
  uint8_t ret = 0;

	//"Start Remote Node CAN Message"
	msg.id = 0;//COB-id for NMT or network management
	msg.len = 2;
	msg.buf[0] = 0x01; //Command Specifier for "start_remote_node"
	msg.buf[1] = 0;//when set to zero, all slaves will react to the command
 

  msg.timeout = 1000;//Milliseconds before giving up on broadcasting CAN message
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during start_remote_nodes function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during start_remote_nodes function call");
        Serial.println();
        delay(500);
    }
  }
  return ret;
}

/*This function sends the Network Management (NMT) message for "Stop Remote Nodes". It will send the message that signals every node to enter the Stopped state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been cleared as a result. Can check the Statusword 
 * for confirmation. In this state, only NMT, Heartbeating, and Layer setting service messages are permitted.  
 * See EPOS4 Communication Guide section 3.3.3.5, NMT Services (NMT SLave state machine info) and EPOS4 Firmware Specification pg6-161 (Statusword).
*/
uint8_t stop_remote_nodes()
{
  CAN_message_t msg;
  uint8_t ret = 0;

  //"Stop Remote Node CAN Message"
  msg.id = 0;//COB-id for NMT or network management
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x02; //Command Specifier for "Stop Remote Node"
  msg.buf[1] = 0;//when set to zero, all slaves will react to the command
 

  msg.timeout = 1000;//Milliseconds before giving up on broadcasting CAN message
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during stop_remote_nodes function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during stop_remote_nodes function call");
        Serial.println();
        delay(500);
    }
  }

  return ret;
}



/* ---------------------------------------------------------SERVICE DATA OBJECT FUNCTIONS----------------------------------------------------------------------------------------------------------------------*/

/* This function sends the Servide Data Object (SDO) message for accessing the "Modes of Operation" object in the object dictionary of all 4 nodes. The function will attempt to write
 *  the message to one of the nodes and if successful it will wait up to 1 second for the SDO confirmation message to be returned by the node. It will do this for each node and 
 *  notify through a print statement if there was a read message timeout and one of the nodes did not respond to the message within 1 second of successfully sending it. This 
 *  should likely be changed from a print statement to some kind of error checking variable to be used by the main Teensy firmware's error code. See EPOS4 Firmware Specification
 *  pg 6-164 (Modes of Operation) and pg 3-38 (Cyclic Synchronous Torque mode). 
*/
uint8_t set_torque_operating_mode()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR;

  //Set the operating mode variable of each node to torque mode
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
    msg.len = 5;
    msg.buf[0] = 0x2F; //Command specifier for writing one byte dictionary object
    msg.buf[2] = 0x60; //High byte of index for Modes of Operation dictionary object
    msg.buf[1] = 0x60; //Low byte of index for Modes of Operation dictionary object 
    msg.buf[3] = 0; //Sub-index
    msg.buf[4] = TORQUE_MODE; //Pound defined earlier. To set torque mode, write a 10
    
    msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      ret = ERROR_CAN_WRITE;
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.println("error CAN write during set_torque_operating_mode function call");
          Serial.println();
          delay(500);
      }
      
    }

    if(ret == NO_ERROR)//If the CAN write was successful
    {
  
      //The following code will filter out any message that is not an SDO confirmation resulting from the Set Torque Operating Mode SDO written above
      for(uint8_t index = 1; index <= 1 ; index++)
      {
  
        msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message
        if (CANbus.read(msg) == 0){//If the read message timeout was reached and a message was not available to read
    
          if(CONFIGURATION_PRINT)
          {
            Serial.println();
            Serial.print("A read message timeout has occured during the set_torque_operating_mode call, node: ");
            Serial.print(node_id);
            Serial.println();
          }
            
        } 
    
        else{

          if((msg.buf[2] << 8 | msg.buf[1]) == 0x6060 && msg.id == 0x580 + node_id){ //If the returned message was an SDO response (COB-id of 0x580 + node id) and the OD main index was that of the Set Operating Mode object (index of 0x6060)
            if (CONFIGURATION_PRINT)
            {
              Serial.println();
              Serial.print("Message read during set_torque_operating_mode function call, node ");//MAY WANT TO CHANGE THIS PRINT STATEMENT TO BETTER REFLECT WHAT'S HAPPENING
              Serial.print(node_id);
              Serial.println(":");
              Serial.println();
              print_CAN_message(msg);
            }
          }

          else{// Else the recieved message was not an SDO confirmation 
  
            index--; //Decrement the index so that the loop runs again and checks for the next read message
            Serial.print("A non-sdo-confirmation message was recieved during the set_torque_operating_mode function call and was ignored. The COB-id was: ");
            Serial.println(msg.id, HEX);
            
          }
        }
      }
    }  
  }

    if(ret = NO_ERROR){
        if (CONFIGURATION_PRINT)
        {
            Serial.println();
            Serial.println("successful CAN write during set_torque_operating_mode function call");
            Serial.println();
            delay(500);
        }
    }

  return ret;//Probably want to have returned whether or not the confirmation SDO was recieved or not

}

///* This function will send out an SDO write message to the "SI unit velocity" object of each node and wait a maximum of 1 second for a confirmation message from each node to return. 
// *  The units to be set are 1 deci-rpm per bit so that the maximum allowable speed of about 3200 rpm can fit in a 16 bit signed integer. See EPOS4 Firmware Specification pg 2-16 (System Units)
// *  and pg 6-177 TURNS OUT YOU CANT CHANGE THE VELOCITY UNITS...IM ALMOST CERTAIN OF THIS
//*/
//uint8_t set_velocity_units()
//{
//  CAN_message_t msg;
//  uint8_t ret = NO_ERROR;
//
//  //Set the SI unit velocity variable of each node to one deci-rpm per bit.
//  for( uint8_t node_id = 1; node_id <=4; node_id++ )
//  {
//    msg.id = 0x600 + node_id;
//    msg.len = 8;
//    msg.buf[0] = 0x2F;//
//    msg.buf[2] = 0x60;//High byte of object dictionary index for SI unit velocity
//    msg.buf[1] = 0xA9;//Low byte of object dictionary index for SI unit velocity
//    msg.buf[3] = 0;//Sub-index
//    msg.buf[7] = 0xFF;//Code for prefix of 10^-1 (deci)
//    msg.buf[6] = 0xB4;//Code for a numerator unit of rotations
//    msg.buf[5] = 0x47;//Code for a denominator unit of minutes
//    msg.buf[4] = 0;//Reserved, so write zeros
//
//    
//    msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
//    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
//    {
//      ret = ERROR_CAN_WRITE;
//      if (PRINT)
//      {
//          Serial.println();
//          Serial.println("error CAN write during set_velocity_units function call");
//          Serial.println();
//          delay(500);
//      }
//      
//    }
//
//    if(ret == NO_ERROR)//If the CAN write was successful
//    {
//  
//      //The following code will filter out any message that is not an SDO confirmation resulting from the SI unit velocity SDO written above
//      for(uint8_t index = 1; index <= 1 ; index++)
//      {
//  
//        msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message
//        if (CANbus.read(msg) == 0){//If the read message timeout was reached and a message was not available to read
//    
//          if(PRINT)
//          {
//            Serial.println();
//            Serial.println("A read message timeout has occured during the set_velocity_units call.");
//            Serial.println();
//          }
//            
//        } 
//    
//        else{
//
//          if((msg.buf[2] << 8 | msg.buf[1]) == 0x60A9 && msg.id == 0x580 + node_id){ //If the returned message was an SDO response (COB-id of 0x580 + node id) and the OD main index was that of the Set Operating Mode object (index of 0x60A9)
//            if (PRINT)
//            {
//              Serial.println();
//              Serial.print("Message read during set_velocity_units function call, node ");//MAY WANT TO CHANGE THIS PRINT STATEMENT TO BETTER REFLECT WHAT'S HAPPENING
//              Serial.print(node_id);
//              Serial.println(":");
//              Serial.println();
//              print_CAN_message(msg);
//            }
//          }
//
//          else{// Else the recieved message was not an SDO confirmation 
//  
//            index--; //Decrement the index so that the loop runs again and checks for the next read message
//            Serial.print("A non-sdo-confirmation message was recieved during the set_velocity_units function call and was ignored. The COB-id was: ");
//            Serial.println(msg.id, HEX);
//            
//          }
//        }
//      }
//    }  
//  }
//
//    if(ret = NO_ERROR){
//        if (PRINT)
//        {
//            Serial.println();
//            Serial.println("successful CAN write during set_torque_operating_mode function call");
//            Serial.println();
//            delay(500);
//        }
//    }
//
//  return ret;//Probably want to have returned whether or not the confirmation SDO was recieved or not
//
//}

/* This function will send out an SDO write message to the "Transmit PDO 1 parameter" object of each node and wait a maximum of 1 second for a confirmation message from each node to return. 
 *  The inhibit time is the minimum time between broadcasts of this particular PDO on each node. It is being set to a maximum frequency of about 180 hz. See EPOS4 Firmware Specification 
 *  pgs 6-85/86. For more information on Process Data Objects and inhibit time, see http://www.canopensolutions.com/english/about_canopen/pdo.shtml CANopen Basics - Process Data Exchange. 
*/
uint8_t set_TxPDO1_inhibit_time()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR;

  //Set the TxPDO1 inhibit time for each node
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id;//SDO COB-id for the node
    msg.len = 6;
    msg.buf[0] = 0x2B;//Command specifier for writing 2 bytes to the nodes object dictionary
    msg.buf[2] = 0x18;//High byte of TxPDO1 Parameter Index
    msg.buf[1] = 0x00;//Low byte of TxPDO1 Parameter Index
    msg.buf[3] = 0x03;//Sub-index of TxPDO1 Parameter Object, the INHIBIT TIME
    msg.buf[5] = 0x00;//High byte of data is zero
    msg.buf[4] = 0x37;//Low byte of data - 55 multiples of 100uS produces an inhibit time of 0.0055 seconds or 180hz
    
    msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      ret = ERROR_CAN_WRITE;
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.println("error CAN write during set_TxPDO1_inhibit_time function call");
          Serial.println();
          delay(500);
      }
      
    }

    if(ret == NO_ERROR)//If the CAN write was successful
    {
  
      //The following code will filter out any message that is not an SDO confirmation resulting from the Set Torque Operating Mode SDO written above
      for(uint8_t index = 1; index <= 1 ; index++)
      {
  
        msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message
        if (CANbus.read(msg) == 0){//If the read message timeout was reached and a message was not available to read
    
          if(CONFIGURATION_PRINT)
          {
            Serial.println();
            Serial.println("A read message timeout has occured during the set_TxPDO1_inhibit_time function call.");
            Serial.println();
          }
            
        } 
    
        else{
          if((msg.buf[2] << 8 | msg.buf[1]) == 0x1800 && msg.id == 0x580 + node_id && msg.buf[3] == 0x03)
          { //If the returned message was an SDO response (COB-id of 0x580 + node id) and the OD main index was that of the TxPDO1 parameter object (0x1800) and the sub-index was that of the inhibit time (0x03).
            if (CONFIGURATION_PRINT)
            {
              Serial.println();
              Serial.print("Message read during set_TxPDO1_inhibit_time function call, node ");//MAY WANT TO CHANGE THIS PRINT STATEMENT TO BETTER REFLECT WHAT'S HAPPENING
              Serial.print(node_id);
              Serial.println(":");
              Serial.println();
              print_CAN_message(msg);
            }
          }
  
          else{// Else the recieved message was not an SDO confirmation 
  
            index--; //Decrement the index so that the loop runs again and checks for the next read message
            Serial.print("A non-sdo-confirmation message was recieved during the set_TxPDO1_inhibit_time function call and was ignored. The COB-id was: ");
            Serial.println(msg.id, HEX);
            
          }
        }
      }
    }  
  }

    if(ret = NO_ERROR){
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.println("All CAN writes successful during set_TxPDO1_inhibit_time function call");
          Serial.println();
          delay(500);
      }
    }
    
  return ret;//Probably want to have returned wether or not the confirmation SDO was recieved or not
}

uint8_t request_statusword()//This function requests the statusword of a node through SDO read request and confirmation.
{
  CAN_message_t msg;
  uint8_t write_error_count = 0;
  
  for(uint8_t node_id = 1; node_id <=4; node_id++)
  {
    
    //Send a statusword request to the node and wait for the SDO confirmation (will contain the nodes statusword). Mostly for debugging purposes. 
    msg.id = 0x600 + node_id;
    msg.len = 8;// Message length is 8 because I think I'm supposed to send 4 empty bytes during an SDO read request. Not certain this is necessary though.
    msg.buf[0] = 0x40;// Command Specifier for object dictionary read of 2 bytes
    msg.buf[2] = 0x60;
    msg.buf[1] = 0x41;
    msg.buf[3] = 0;//Sub-index
    msg.buf[4] = 0;//Empty data (junk)
    msg.buf[5] = 0;//Empty data (junk)
    msg.buf[6] = 0;//Empty data (junk)
    msg.buf[7] = 0;//Empty data (junk)

    msg.timeout = 0;//If this is set to zero, write blocking will not occur - the write function will try to send out the message immediately and return a 0 if unsuccessful
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      write_error_count++;
      if (CONFIGURATION_PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during the request_statusword function call, node ");
          Serial.println(node_id);
          Serial.println();
          delay(500);
      }
    }
  }
  
  if(write_error_count == 0){
    if (CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN writes during the request_statusword function call");
        Serial.println();
        delay(500);
    }
  }
  
  else{
    if(CONFIGURATION_PRINT)
    {
        Serial.println();
        Serial.println("at least one CAN write error occured during the request_statusword function call ");
        Serial.println();
        delay(500);
    }
  }

  return (4-write_error_count);
}


/* This function will send out an SDO read request message to the "Error register" object of each node. The SDO confirmation from each node will have a command specifier of 0x4F (read dictionary object reply) 
 *  and an object index of 0x1001 (same as used in the request message below). In your main script there should be a function that checks for an SDO confirmation message and extracts the error message byte appropriately. 
 *  See EPOS4 Firmware Specification pgs 6-59 for information on the error register object.  
*/
uint8_t request_error_registers()
{

  CAN_message_t msg;
  uint8_t write_error_count = 0;

  //Set the TxPDO1 inhibit time for each node
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id;//SDO COB-id for the node
    msg.len = 6;
    msg.buf[0] = 0x40;//Command specifier for read dictionary object request
    msg.buf[2] = 0x10;//High byte of error register object index
    msg.buf[1] = 0x01;//Low byte of error register object index
    msg.buf[3] = 0x00;//No sub-index
//    msg.buf[4] = 0x00;//Empty data (junk)
//    msg.buf[5] = 0x00;//Empty data (junk)
//    msg.buf[6] = 0x00;//Empty data (junk)
//    msg.buf[7] = 0x00;//Empty data (junk)
    //The data sent does not matter for a read request 
    
    msg.timeout = 0;//If this is set to zero, write blocking will not occur - the write function will try to send out the message immediately and return a 0 if unsuccessful
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      write_error_count++;
      if (DYNAMIC_PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during request_error_registers function call, node ");
          Serial.println(node_id);
          Serial.println();
          delay(500);
      }
    }
  }

  if(write_error_count == 0){
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN writes during request_error_registers function call");
        Serial.println();
        delay(500);
    }
  }

  else{
    if(DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("at least one CAN write error occured during the request_error_registers function call ");
        Serial.println();
        delay(500);
    }
  }
  return (4-write_error_count);
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
  uint8_t write_error_count = 0;
  uint8_t command_HB = (uint8_t)(control_command >> 8); //Grab the high byte of the controlword value
  uint8_t command_LB = (uint8_t)(control_command); //Grab the low byte of the controlword value

  for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
    
    //CAN message to update the controlword value of the node.
    msg.id = 0x200 + node_id;//COB-id for RxPDO1 - defined using EPOS Studio software
    msg.ext = 0;
    msg.len = 2;
    msg.buf[1] = command_HB;
    msg.buf[0] = command_LB;
    
    msg.timeout = 0;//If this is set to zero, write blocking will not occur - the write function will try to send out the message immediately and return a 0 if unsuccessful
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      write_error_count++;
      if (DYNAMIC_PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during RxPDO1_controlword_write function call, node ");
          Serial.println(node_id);
          Serial.println();
          delay(500);
      }
    }
  }

  if(write_error_count = 0){
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("successful CAN writes during RxPDO1_controlword_write function call");
        Serial.println();
        delay(500);
    }
  }
  
  else{
    if(DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("at least one CAN write error occured during the request_error_registers function call ");
        Serial.println();
        delay(500);  
    }  
  }
  return (4-write_error_count);
}

/*
 * This function writes a PDO message to the CAN bus, RxPDO2 (cob-id designated by myself to be of 300 + node_id) and updates the "Target Torque" object of a motor controller's object dictionary. 
 * See EPOS4 Firmware Specification pg 6-167. 
 */
uint8_t RxPDO2_torque_write(int node_id, uint16_t throttle) //Send out the RxPDO1 message that updates the node's controlword object
{
  CAN_message_t msg;
  uint8_t ret = 0;

  //RxPDO 2,updating the target torque
  msg.id = 0x300 + node_id; //COB-id of RxPDO 2 for this specific node
  msg.ext = 0;
  msg.len = 4;
  memcpy(&(msg.buf[0]), (void *)(&throttle), 1);
  memcpy(&(msg.buf[1]), ((char *)(&throttle) + 1), 1);
  memcpy(&(msg.buf[2]), ((char *)(&throttle) + 2), 1);
  memcpy(&(msg.buf[3]), ((char *)(&throttle) + 3), 1);
  
  msg.timeout = 0;//Milliseconds before giving up on broadcasting CAN message
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during RxPDO2_torque_write function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (DYNAMIC_PRINT)
    {
        Serial.println();
        Serial.print("successful CAN write during RxPDO2_torque_write function call, a value of: ");
        Serial.println(throttle);
        Serial.println();
        delay(500);
    }
  }

  
  return ret;
}

void read_available_message()
{
  CAN_message_t msg;
  msg.timeout = 0;
  if(CANbus.read(msg)){
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
  Serial.print("ID: ");
  Serial.println(msg.id, HEX);
  Serial.print("Length: ");
  Serial.println(msg.len);
  Serial.print("Byte[0]: ");
  Serial.println(msg.buf[0], HEX);
  Serial.print("Byte[1]: ");
  Serial.println(msg.buf[1], HEX);
  Serial.print("Byte[2]: ");
  Serial.println(msg.buf[2], HEX);
  Serial.print("Byte[3]: ");
  Serial.println(msg.buf[3], HEX);
  Serial.print("Byte[4]: ");
  Serial.println(msg.buf[4], HEX);
  Serial.print("Byte[5]: ");
  Serial.println(msg.buf[5], HEX);
  Serial.print("Byte[6]: ");
  Serial.println(msg.buf[6], HEX);
  Serial.print("Byte[7]: ");
  Serial.println(msg.buf[7], HEX);
  Serial.println();
  
}


