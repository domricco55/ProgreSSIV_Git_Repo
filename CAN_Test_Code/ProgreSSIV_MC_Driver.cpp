/* CAN Firmware Functions made for Teensy 3.6 
	by the uLaren Senior Project Team    */

/*********************************/
/* current functionality works but re-initialization does not work*/
/*********************************/

#include "flexCAN.h"
#include "ProgreSSIV_MC_Driver.h"
#include <string.h>

#define WAIT_FOR_RESPONSE_TIME_SLOW_US 100
#define WAIT_FOR_RESPONSE_TIME_FAST_US 50


extern FlexCAN CANbus;

int reset_nodes()
{
  CAN_message_t msg;
  int ret = 0;

  //reset nodes NMT command
  msg.id = 0;
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x81;
  msg.buf[1] = 0;

  msg.timeout = 1;//Milliseconds before giving up on message
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

//  if(ret == NO_ERROR){//If the CAN write was successful, attempt to read the boot up messages from the CAN bus 
//    for(uint8_t index = 0; index<4 ; index++){
//      
//      msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message (wait for a response from each node on the bus
//      if (CANbus.read(msg) != 0){//If the read message timeout wasnt reached and a message was available to read
//        if (PRINT)
//        {
//          Serial.println();
//          Serial.println("Message read during reset_nodes function call:");
//          Serial.println();
//          print_CAN_message(msg);
//        }
//      }
//  
//      else{
//        if(PRINT)
//        {
//          Serial.println();
//          Serial.println("A read message timeout has occured during the reset_nodes function call.");
//          Serial.println();
//        }
//      }
//    }
//  }

  if(ret == NO_ERROR){//If the CAN write was successful, attempt to read the boot up messages from the CAN bus 

    //The following code will filter out each node's boot up confirmation from other messages that may be in the CAN read buffer. It expects 4 total boot up confirmations
    for(uint8_t index = 0; index<4 ; index++){
      
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
          Serial.print("A non-boot up message was recieved during the reset_nodes function all and was ignored. The COB-id was: ");
          Serial.println(msg.id, HEX);
        } 
      }
    }
  }
  return ret; //May want to change what each of these functions returns
}

int reset_communications()
{
  CAN_message_t msg;
  int ret = 0;

  //reset communication NMT command
  msg.id = 0;
  msg.ext = 0;
  msg.len = 2;
  msg.buf[0] = 0x82;
  msg.buf[1] = 0;

  msg.timeout = 1;//Milliseconds before giving up on broadcastimng CAN message
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
    
    for(uint8_t index = 0; index<4 ; index++){
      
      msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message
      if (CANbus.read(msg) != 0){//If the read message timeout wasnt reached and a message was available to read
        if (PRINT)
        {
          Serial.println();
          Serial.println("Message read during reset_communications function call:");
          Serial.println();
          print_CAN_message(msg);
        }
      }
  
      else{
        if(PRINT)
        {
          Serial.println();
          Serial.println("A read message timeout has occured during the reset_communications function call.");
          Serial.println();
        }
      }
    }
  }
  
  return ret; //May want to change what each of these functions returns
}

int set_torque_operating_mode(int node_id)
{
  CAN_message_t msg;
  int ret = 0;

    //initialize MC's to torque mode
  msg.id = 0x600 + node_id;
  msg.len = 5;
  msg.timeout = 0;
  msg.buf[0] = 0x2F;
  msg.buf[2] = 0x60;
  msg.buf[1] = 0x60;
  msg.buf[3] = 0;
  msg.buf[4] = TORQUE_MODE;

  msg.timeout = 1;//Milliseconds before giving up on broadcastimng CAN message
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
  else{
    ret = NO_ERROR;
    if (PRINT)
    {
        Serial.println();
        Serial.println("successful CAN write during set_torque_operating_mode function call");
        Serial.println();
        delay(500);
    }
  }
  
  if(ret == NO_ERROR){//If the CAN write was successful, attempt to read the boot up messages from the CAN bus 
      
    msg.timeout = 1000;//Milliseconds before giving up on reading a CAN message
    if (CANbus.read(msg) != 0){//If the read message timeout wasnt reached and a message was available to read
      if (PRINT)
      {
        Serial.println();
        Serial.println("Message read during set_torque_operating_mode function call:");
        Serial.println();
        print_CAN_message(msg);
      }
    }

    else{
      if(PRINT)
      {
        Serial.println();
        Serial.println("A read message timeout has occured during the set_torque_operating_mode function call.");
        Serial.println();
      }
    }
  }

  return ret;

}

int start_remote_nodes()
{
	CAN_message_t msg;
  int ret = 0;

	//"Start Remote Node CAN Message"
	msg.id = 0;//CAN_id for NMT or network management
	msg.ext = 0;
	msg.len = 2;
	msg.timeout = 0; //Tells how long the system should wait for a response to this CAN message? LOOK AT FLEXCAN README FOR ANSWER TO THIS
	msg.buf[0] = 0x01; //Command Specifier for "start_remote_node"
	msg.buf[1] = 0;//when set to zero, all slaves will be started
 

  msg.timeout = 1;//Milliseconds before giving up on broadcastimng CAN message
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

//MY FUNCTIONS ABOVE HERE

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


int controlword_operation_enabled(int node_id)
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

  //tell MC's to go to operation enabled state
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
  msg.buf[5] = 0x01;//Controlword high byte
  msg.buf[4] = 0b00001111;//Controlword low byte.

  if (CANbus.write(msg) == 0)
  {
    ret = ERROR_CAN_WRITE;
  }
  /*else {
    //print_CAN_message(msg);
    delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
    if (CANbus.read(msg) != 0)
    {
      Serial.println("Received Operation Enabled Confirmation");
      //print_CAN_message(msg);
    }
    else
    {
      Serial.println("DID NOT Receive Operation Enabled Confirmation");
    }
  }*/
  return ret;
}




int write_torque_and_enable_op(int node_id, int throttle)
{
  CAN_message_t msg;
  int ret = 0;
  int error = 0;

  //make sure throttle does not exceed limits
  if (throttle > (500 * SCALE_FACTOR + 200))  
  {
    throttle = 500 * SCALE_FACTOR;
  }
  else if (throttle < (-500 * SCALE_FACTOR - 200))
  {
    throttle = -500 * SCALE_FACTOR;
  }

  //initiate throttle dead zone
  if (throttle < (10 * SCALE_FACTOR) && throttle > (-10 * SCALE_FACTOR))
  {
    throttle = 0;
  }
  
  //RxPDO 3, setting the controlword value and updating the target torque
  msg.id = 0x400 + node_id; //COB-id of RxPDO 3 for this specific node
  msg.ext = 0;
  msg.len = 6;
  msg.timeout = 0;
  //Control Word bytes
  msg.buf[0] = 0x0F;
  msg.buf[1] = 0x00;
  //Target torque bytes
  memcpy(&(msg.buf[2]), (void *)(&throttle), 1);
  memcpy(&(msg.buf[3]), ((char *)(&throttle) + 1), 1);
  memcpy(&(msg.buf[4]), ((char *)(&throttle) + 2), 1);
  memcpy(&(msg.buf[5]), ((char *)(&throttle) + 3), 1);

  if (PRINT)
  {
    //print_CAN_message(msg);
  }

  ret = CANbus.write(msg);
  if (ret == 1)
  {
    error = NO_ERROR;
  }
  else {
    error = ERROR_CAN_WRITE;
  }

  return 0;
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

//int send_statusword_request(int node_id)
//{
//  CAN_message_t msg;
//  int ret = 0;
//  
//  msg.id = 0x600 + node_id;
//  msg.ext = 0;
//  msg.len = 8;//Changed this to 8 so that the command specifier, index, subindex, and four bytes of junk data are sent (buf 0 - 7)
//  msg.timeout = 1;
//  msg.buf[0] = 0x40;
//  msg.buf[2] = 0x60;
//  msg.buf[1] = 0x41;
//  msg.buf[3] = 0x00;
//  msg.buf[4] = 0x00;
//
//  if (CANbus.write(msg) == 0)
//  {
//    if (PRINT)
//    {
//      Serial.println("error writing CAN message");
//    }
//    
//    exit(0);
//  }
//  
////  msg.timeout = 100;
////  if (CANbus.read(msg) != 0)
////  {
////    if (PRINT)
////    {
////      Serial.println("Received Statusword");
////    }
////    
////    print_CAN_message(msg);
////    ret = 1;
////  }
////  else
////  {
////    if (PRINT)
////    {
////      Serial.println("DID NOT Receive Statusword");
////    }
//    
//    ret = 0;
//  }*/
//
//  return ret;
//}

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
  delayMicroseconds(WAIT_FOR_RESPONSE_TIME_SLOW_US);
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



