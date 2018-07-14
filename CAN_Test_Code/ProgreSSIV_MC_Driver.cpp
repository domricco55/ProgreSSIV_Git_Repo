/* CAN Firmware Functions made for Teensy 3.6 
	by the uLaren Senior Project Team    */

/*********************************/
/* current functionality works but re-initialization does not work*/
/*********************************/

#include "flexCAN.h"
#include "ProgreSSIV_MC_Driver.h"
#include <string.h>

#define PRINT 0

extern FlexCAN CANbus;

uint8_t reset_nodes()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR; //This variable is currently the one being returned by the function but this may change. 
  uint8_t bootup_count = 0; //This variable will keep track of the number of node NMT boot up confirmations recieved. 

  //reset nodes NMT command
  msg.id = 0;
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x81;
  msg.buf[1] = 0;

  msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during reset_nodes() function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (PRINT)
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
        
        if(PRINT)
        {
          Serial.println();
          Serial.println("A read message timeout has occured during the reset_nodes function call. One of the nodes may not be on the CAN bus.");
          Serial.println();
        }
        
      }
      
      else{//Else, the read message timeout wasn't reached and a message was available to read.
        if(msg.id == 0x701 || msg.id == 0x702 || msg.id == 0x703 || msg.id == 0x704){// If the recieved message is a nodes NMT boot up message, the COB-id will be between 0x701 and 0x704
          
          bootup_count++; //A bootup message has been recieved, increment the bootup count.
          
          if(PRINT)
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

uint8_t reset_communications()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR; //This variable is currently the one being returned by the function but this may change. 
  uint8_t bootup_count = 0; //This variable will keep track of the number of node NMT boot up confirmations recieved. 

  //reset communication NMT command
  msg.id = 0;
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x82;
  msg.buf[1] = 0;

  msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during reset_communication() function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (PRINT)
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
        
        if(PRINT)
        {
          Serial.println();
          Serial.println("A read message timeout has occured during the reset_communications function call. One of the nodes may not be on the CAN bus.");
          Serial.println();
        }
        
      }
      
      else{//Else, the read message timeout wasn't reached and a message was available to read.
        if(msg.id == 0x701 || msg.id == 0x702 || msg.id == 0x703 || msg.id == 0x704){// If the recieved message is a nodes NMT boot up message, the COB-id will be between 0x701 and 0x704
          
          bootup_count++; //A bootup message has been recieved, increment the bootup count.
          
          if(PRINT)
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

uint8_t set_torque_operating_mode()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR;

  //Set the operating mode variable of each node to torque mode
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id;
    msg.len = 5;
    msg.buf[0] = 0x2F;
    msg.buf[2] = 0x60;
    msg.buf[1] = 0x60;
    msg.buf[3] = 0;
    msg.buf[4] = TORQUE_MODE;
    
    msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      ret = ERROR_CAN_WRITE;
      if (PRINT)
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
    
          if(PRINT)
          {
            Serial.println();
            Serial.println("A read message timeout has occured during the set_torque_operating_mode call.");
            Serial.println();
          }
            
        } 
    
        else{

          if((msg.buf[2] << 8 | msg.buf[1]) == 0x6060 && msg.id == 0x580 + node_id){ //If the returned message was an SDO response (COB-id of 0x580 + node id) and the OD main index was that of the Set Operating Mode object (index of 0x6060)
            if (PRINT)
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
        if (PRINT)
        {
            Serial.println();
            Serial.println("successful CAN write during set_torque_operating_mode function call");
            Serial.println();
            delay(500);
        }
    }

  return ret;//Probably want to have returned whether or not the confirmation SDO was recieved or not

}



uint8_t set_TxPDO1_inhibit_time()
{
  CAN_message_t msg;
  uint8_t ret = NO_ERROR;

  //Set the TxPDO1 inhibit time for each node
  for( uint8_t node_id = 1; node_id <=4; node_id++ )
  {
    msg.id = 0x600 + node_id;//SDO COB-id for the node
    msg.len = 6;
    msg.buf[0] = 0x2B;//Command specifier for writing 2 bytes
    msg.buf[2] = 0x18;//High byte of TxPDO1 Parameter Index
    msg.buf[1] = 0x00;//Low byte of TxPDO1 Parameter Index
    msg.buf[3] = 0x03;//Sub-index of TxPDO1 Parameter Object, the INHIBIT TIME
    msg.buf[5] = 0x00;//High byte of data is zero
    msg.buf[4] = 0x37;//Low byte of data - 55 multiples of 100uS produces an inhibit time of 0.0055 seconds or 180hz
    
    msg.timeout = 1000;//Milliseconds before giving up on sending out a message. The write will fail if there was no buffer available before 1000 milliseconds - plenty of time.
    if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
    {
      ret = ERROR_CAN_WRITE;
      if (PRINT)
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
    
          if(PRINT)
          {
            Serial.println();
            Serial.println("A read message timeout has occured during the set_TxPDO1_inhibit_time function call.");
            Serial.println();
          }
            
        } 
    
        else{
          if((msg.buf[2] << 8 | msg.buf[1]) == 0x1800 && msg.id == 0x580 + node_id && msg.buf[3] == 0x03)
          { //If the returned message was an SDO response (COB-id of 0x580 + node id) and the OD main index was that of the TxPDO1 parameter object (0x1800) and the sub-index was that of the inhibit time (0x03).
            if (PRINT)
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
      if (PRINT)
      {
          Serial.println();
          Serial.println("All CAN writes successful during set_TxPDO1_inhibit_time function call");
          Serial.println();
          delay(500);
      }
    }
    
  return ret;//Probably want to have returned wether or not the confirmation SDO was recieved or not
}


uint8_t start_remote_nodes()
{
	CAN_message_t msg;
  uint8_t ret = 0;

	//"Start Remote Node CAN Message"
	msg.id = 0;//COB-id for NMT or network management
	msg.ext = 0;
	msg.len = 2;
	msg.timeout = 0; //Tells how long the system should wait for a response to this CAN message? LOOK AT FLEXCAN README FOR ANSWER TO THIS
	msg.buf[0] = 0x01; //Command Specifier for "start_remote_node"
	msg.buf[1] = 0;//when set to zero, all slaves will be started
 

  msg.timeout = 1;//Milliseconds before giving up on broadcasting CAN message
  if (CANbus.write(msg) == 0)// Test if the CAN write was successful and set the return variable accordingly
  {
    ret = ERROR_CAN_WRITE;
    if (PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during start_remote_nodes function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during start_remote_nodes function call");
        Serial.println();
        delay(500);
    }
  }

//There is no message broadcast from the Motor Controllers as a direct result of an NMT transition to the "operational" state. 
//You can however check bit 9 of the statusword at this point to verify that the NMT state is in fact "operational".
  return ret;

}

uint8_t RxPDO1_controlword_write(uint16_t control_command) //Send out the RxPDO1 message that updates the node's controlword object
{
  CAN_message_t msg;
  uint8_t error_count = 0;
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
      error_count++;
      if (PRINT)
      {
          Serial.println();
          Serial.print("error CAN write during RxPDO1_controlword_write function call, node ");
          Serial.println(node_id);
          Serial.println();
          delay(500);
      }
    }
  }

  if(error_count = 0){
    if (PRINT)
    {
        Serial.println();
        Serial.println("successful CAN writes during RxPDO1_controlword_write function call");
        Serial.println();
        delay(500);
    }
  }
  return (4-error_count);
}

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
    if (PRINT)
    {
        Serial.println();
        Serial.println("error CAN write during RxPDO2_torque_write function call");
        Serial.println();
        delay(500);
    }
    
  }
  else{
    ret = NO_ERROR;
    if (PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during RxPDO2_torque_write function call");
        Serial.println();
        delay(500);
    }
  }
  
  return ret;
}



//MY FUNCTIONS ABOVE HERE
/*--------------------------------------------------------------------------------------------------------------------------------------------------------------*/

int resetFault (int node_id) 
{
    CAN_message_t msg;
  int ret = 0;

  //make sure node_id is valid!
  if (node_id > 0 && node_id < 127)
  {
    
  }
  else 
  {
    if (PRINT)
    {
      Serial.print("***** I received a bad node_id of: ");
      Serial.println(node_id);
    }
    
    exit(0);
  }

  //tell MC's to reset faults
  msg.id = 0x600 + node_id;
  msg.ext = 0;
  msg.len = 6;
  msg.timeout = 0;
  //
  msg.buf[0] = 0x2B; 
  msg.buf[2] = 0x60; 
  msg.buf[1] = 0x40;
  msg.buf[3] = 0x00;
  //
  msg.buf[5] = 0x00;
  msg.buf[4] = 0b10000000;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  if (CANbus.write(msg) == 0)
  {
    ret = ERROR_CAN_WRITE;
    if (PRINT)
    {
      Serial.println("ERROR: CAN Write.");
      Serial.print("Node id: ");
      Serial.println(node_id);
    }
    
  }
  else {
//    //print_CAN_message(msg);
//    delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
//    if (CANbus.read(msg) != 0)
//    {
//      if (PRINT)
//      {
//        Serial.println("Received Shutdown Confirmation");
//      }
//      
//    }
//    else
//    {
//      if (PRINT)
//      {
//        Serial.println("DID NOT Receive Shutdown Confirmation");
//      }
//      
//    }
  }
    //tell MC to reset communication
  msg.id = 0x00;
  msg.ext = 0;
  msg.len = 2;
  msg.timeout = 0;
  //
  msg.buf[0] = 0x01;  //68
  msg.buf[2] = 0x00 + node_id;  //60
  msg.buf[1] = 0x00;
  msg.buf[3] = 0x00;
  //
  msg.buf[5] = 0x00;
  msg.buf[4] = 0x00;
  msg.buf[6] = 0;
  msg.buf[7] = 0;

  if (CANbus.write(msg) == 0)
  {
    ret = ERROR_CAN_WRITE;
    if (PRINT)
    {
      Serial.println("ERROR: CAN Write.");
      Serial.print("Node id: ");
      Serial.println(node_id);
    }
    
  }
  else {
//    //print_CAN_message(msg);
//    delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
//    if (CANbus.read(msg) != 0)
//    {
//      if (PRINT)
//      {
//        Serial.println("Received Shutdown Confirmation");
//      }
//      
//    }
//    else
//    {
//      if (PRINT)
//      {
//        Serial.println("DID NOT Receive Shutdown Confirmation");
//      }
//      
//    }
  }
}



void print_CAN_message(CAN_message_t msg)
{
  if (PRINT)
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
  
}


//void check_available_msg()
//{
//  CAN_message_t msg;
//  
//  if (CANbus.available())
//  {
//    if (PRINT)
//    {
//      Serial.println("I have something to receive");
//    }
//    
//    if (CANbus.read(msg) != 0)
//    {
//      if (PRINT)
//      {
//        Serial.println("I read a message!");
//      }
//      
//      print_CAN_message(msg);
//    }
//  }
//  else
//  {
//    if (PRINT)
//    {
//      Serial.println("nothing");
//    }
//    
//  }
//}


//
//void process_available_msgs()
//{
//  CAN_message_t msg;
//  
//  //delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
//  while (CANbus.available()) 
//  {
//
//    if (CANbus.read(msg) != 0)
//    {
//      print_CAN_message(msg);
//    }
//    else
//    {
//      if (PRINT)
//      {
//        Serial.println("***OOPS the CAN read went wrong!***");
//      }
//      
//    }
//  }
//}

int stop_remote_node(int node_id)
{
  CAN_message_t msg;
  int ret = 0;

  //reset node coms
  msg.id = 0;
  msg.ext = 0;
  msg.len = 2;
  msg.timeout = 0;
  msg.buf[0] = 0x02;
  msg.buf[1] = 0;
  msg.buf[2] = 0;
  msg.buf[3] = 0;
  msg.buf[4] = 0;
  msg.buf[5] = 0;
  msg.buf[6] = 0;
  msg.buf[7] = 0;
  
  ret = CANbus.write(msg);
  //print_CAN_message(msg);
//  delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
  if (CANbus.read(msg) != 0)
  {
    if (PRINT)
    {
      Serial.println("Received Stop Node Confirmation");
    }
    
  }
  else
  {
    if (PRINT)
    {
      Serial.println("DID NOT Receive Stop Node Confirmation");
    }
    
  }

  return ret;
}



//int shutdown_MC(int node_id)
//{
//  CAN_message_t msg;
//  int ret = 0;
//
//  //tell MC's to go to shutdown state
//  msg.id = 0x600 + node_id;
//  msg.ext = 0;
//  msg.len = 6;
//  msg.timeout = 0;
//  //
//  msg.buf[0] = 0x2B;  //68
//  msg.buf[2] = 0x60;  //60
//  msg.buf[1] = 0x40;
//  msg.buf[3] = 0x00;
//  //
//  msg.buf[5] = 0x00;
//  msg.buf[4] = 0b00000110;
//  msg.buf[6] = 0;
//  msg.buf[7] = 0;
//
//  if (CANbus.write(msg) == 0)
//  {
//    ret = ERROR_CAN_WRITE;
//    if (PRINT)
//    {
//      Serial.println("ERROR: CAN Write.");
//      Serial.print("Node id: ");
//      Serial.println(node_id);
//    }
//    
//  }
//  else {
//    //print_CAN_message(msg);
//    delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
//    if (CANbus.read(msg) != 0)
//    {
//      if (PRINT)
//      {
//        Serial.println("Received Shutdown Confirmation");
//      }
//      
//    }
//    else
//    {
//      if (PRINT)
//      {
//        Serial.println("DID NOT Receive Shutdown Confirmation");
//      }
//      
//    }
//  }
//
//  return ret; 
//}
//



