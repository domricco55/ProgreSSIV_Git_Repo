/** @file ProgreSSIV_CAN_msg_handler.cpp
 *  
 *  @brief Maxon EPOS4 Motor Controller CANopen read filter cpp file.  
 *  @details
 *  
 *  @copyright
 */



/*********************************/

#include "ProgreSSIV_CAN_msg_handler.h"


/*General Debugging*/
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

/** @brief
 *  @details
 *  
 *  @param node_info 
 *  @param node_rpms 
 */
CAN_msg_handler::CAN_msg_handler(node_info_t *node_info, volatile int16_t *node_rpms):

  node_info(node_info),
  node_rpms(node_rpms)//Initializer list 
  {
  
}

/** @brief CAN open read filter task 
 *  @details
 *  Runs the Can0.read(msg) function that will read from the CAN ring buffers of FlexCAN.cpp if a CAN read message is available. The message's COB-id is used to decide what to do with the message. 
 *  The first level of the filter is deciding the type of message object the read was, Network Management (NMT), Service Data Object (SDO), Process Data Object (PDO), or Emergency Object (EMCY). 
 *  This task should be run often to prevent read buffer overruns and lost data but the exact frequency will depend on your specific application and the CAN bus load. For more information on
 *  the different communication object types, see EPOS4 Communication Guide Section 3 CAN Communication and <http://www.canopensolutions.com/english/about_canopen/about_canopen.shtml>
 *  
 */
void CAN_msg_handler::try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and jump to the function associated with the message object type.
  CAN_message_t msg;// Struct defined in FlexCAN 
  if(Can0.read(msg))//If there was something to read, this will be true and msg will be filled with CAN data from the most recent read buffer value (FlexCAN function)
  {

    switch(msg.id){

      case 0x701: case 0x702: case 0x703: case 0x704: //if the message was an NMT related message
      
        filter_NMT(msg);
     

      break;

      case 0x581: case 0x582: case 0x583: case 0x0584: //If the message was a Service Data Object from one of the nodes

        filter_SDO(msg);
    

      break;

      case 0x1A1: case 0x1A2: case 0x1A3: case 0x1A4: case 0x2A1: case 0x2A2: case 0x2A3: case 0x2A4: case 0x3A1: case 0x3A2: case 0x3A3: case 0x3A4: //If the message was a process data object from one of the nodes
        
        filter_PDO(msg);
        
      break;


      case 0x81: case 0x82: case 0x83: case 0x084: //If the message was and EMCY object from one of the nodes

        filter_EMCY(msg); 

      break;
      
      default:
  
        if(CAN_FILTER_PRINT){
          Serial.println();
          Serial.print("A message was received during the try_CAN_msg_filter() function call that was not accounted for: ");
          Serial.println();
          print_CAN_message(msg);
        }
      
      break;
      

    }
  } 
}

/** @brief Filter a Service Data Object
 *  @details
 *  Further filters out the details of a received Service Data Object. The identifying elements of an SDO are the object index, the command specifier, and the node id. 
 *  The data is extracted and placed in the shared data structs defined in shares.h according to these elements. 
 *  
 *  @param msg CAN message object defined by the CAN_message_t struct definition that contains the CAN messages' extracted and grouped information. 
 */
void CAN_msg_handler::filter_SDO(CAN_message_t &msg){

  
  uint16_t object_index = (msg.buf[2] << 8 | msg.buf[1]); //Concatinate the high and low byte of the object dictionairy index of the recieved SDO message             //!< brief
  uint8_t command_specifier = msg.buf[0]; //Grab the command specifier of the recieved SDO message                                                                    //!< brief 
  uint8_t node_id;                                                                                                                                                    //!< brief
  
  switch (object_index){

    case 0x6040: //Controlword object dictionary index

    break;

    case 0x6041: //Statusword object dictionary index

        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
        node_info -> node_statuswords[node_id-1] = (uint16_t)(msg.buf[5] << 8 | msg.buf[4]); //Store the FULL 16 bit statusword for local Teensy use 

        if(CAN_FILTER_PRINT){
          Serial.println("Recieved an SDO statusword response");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);  
        }

    break;

    case 0x6060: //Modes of operation object dictionary index

      if(command_specifier == 0x60){//If the SDO was an expedited write confirmation (command specifier of 0x60)
        
        ++node_info -> op_mode_SDO_count;
        
        if(CAN_FILTER_PRINT){
          Serial.println("Recieved an SDO operating mode write confirmation");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);
        }  
      }
        

        
    break;

    case 0x1800:

      if((command_specifier == 0x60) && (msg.buf[3] == 0x03)){//If the SDO was an expedited write confirmation (command specifier of 0x60) AND the subindex was that of the inhibit time (3)
        
        ++node_info -> inhibit_time_SDO_count;
        
        if(CAN_FILTER_PRINT){
          
          Serial.println("Recieved an SDO TxPDO1 inhibit time write confirmation");  
          Serial.println();
          Serial.print("The COB-id was: ");
          Serial.print(msg.id, HEX);
          Serial.println(); 
          Serial.print("The command specifier was: "); 
          Serial.println(command_specifier, HEX);
          Serial.print("The object index was: "); 
          Serial.println(object_index, HEX);
          Serial.println();
          print_CAN_message(msg);
        }   
      }

    break;

    default:
    
      if(CAN_FILTER_PRINT){
        Serial.println();
        Serial.print("A message was received during the try_CAN_msg_filter() function call that was not accounted for: ");
        Serial.println();
        print_CAN_message(msg);
      }
      
      break;
  }
  
}

/** @brief Filter a Process Data Object
 *  @details
 *  Further filters out the details of a received Process Data Object. The identifying element of a PDO is the message id. The data is extracted and placed in the shared data structs defined in shares.h according to this element. 
 *  
 *  @param msg CAN message object defined by the CAN_message_t struct definition that contains the CAN messages' extracted and grouped information. 
 */
void CAN_msg_handler::filter_PDO(CAN_message_t &msg){

  switch(msg.id){
    
      case 0x1A1: //If TxPDO1, node 1 (the motor velocity)
        
        node_rpms[0] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 1, the FRONT RIGHT motor. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)   
      break;

      case 0x1A2: //If TxPDO1, node 1 (the motor velocity)

        
        node_rpms[1] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 2, the FRONT LEFT motor. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A3: //If TxPDO1, node 1 (the motor velocity)
        
        node_rpms[2] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 3, the BACK RIGHT motor. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A4: //If TxPDO1, node 1 (the motor velocity)
        
        node_rpms[3] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 4, the BACK LEFT motor. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
          
      break;

      case 0x2A1: //If TxPDO2, node 1 (the statusword)
      
        node_info -> node_statuswords[0] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 1
          
      break;

      case 0x2A2: //If TxPDO2, node 2 (the statusword)
      
        node_info -> node_statuswords[1] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 2

      break;

      case 0x2A3: //If TxPDO2, node 3 (the statusword)
      
        node_info -> node_statuswords[2] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 3
          
      break;

      case 0x2A4: //If TxPDO2, node 4 (the statusword ).

        node_info -> node_statuswords[3] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 4

      break;

      case 0x3A1: //If TxPDO3, node 1 (the statusword)

        node_info -> mode_of_op_displays[0] = msg.buf[0];
          
      break;

      case 0x3A2: //If TxPDO3, node 2 (the statusword)
      
        node_info -> mode_of_op_displays[1] = msg.buf[0];
          
      break;

      case 0x3A3: //If TxPDO3, node 3 (the statusword)
      
        node_info -> mode_of_op_displays[2] = msg.buf[0];
          
      break;

      case 0x3A4: //If TxPDO3, node 4 (the statusword )

        node_info -> mode_of_op_displays[3] = msg.buf[0];

      break;
  }
}

/** @brief Filter Netowrk Management message
 *  @details
 *  Further filters out the details of a received Network Management message. So far only a bootup confirmation is accounted for - an id of 700 + node id followed by zeros in the data buffer. 
 *  Further work should include heartbeat monitoring where a message containing each nodes NMT communication satus byte is recieved occassionally (0x00 - bootup, 0x04 stopped, 0x05 - operational, and 0x7F Pre-Operational).
 *  See EPOS4 Communication Guide section 3.3.3.5, NMT Services for NMT Slave state machine information.
 *  
 *  @param msg CAN message object defined by the CAN_message_t struct definition that contains the CAN messages' extracted and grouped information.  
 */
void CAN_msg_handler::filter_NMT(CAN_message_t &msg){

  //So far this is the only NMT message being filtered but other NMT messages can be added. For instance, heartbeating is currently active on the nodes and can be filtered as part of this function
  if(msg.buf[0] == 0 && msg.buf[1] == 0 && msg.buf[2] == 0 && msg.buf[3] == 0 && msg.buf[4] == 0 && msg.buf[5] == 0 &&msg.buf[6] == 0 &&msg.buf[7] == 0){ //If Network Management (NMT) Boot Up message
   
    ++node_info -> bootup_count;
    
    if(CAN_FILTER_PRINT){
    Serial.println();
    Serial.println("Recieved a bootup confirmation");  
    Serial.println();
    print_CAN_message(msg);
    }  
  }
}

/** @brief Filter Emergency Message
 *  @details
 *  Further filters out the details of a received Emergency Message. An Emergency message is broadcast from a node whenever a fault occurs and the node transitions into a device control state machine fault state. 
 *  The identifying elements of an EMCY message are the node id, the error code (detailed description of each can be found in the EPOS 4 firmware specification document section 7 Error handling), and the nodes error register value 
 *  (EPOS4 Firmware Specification section 6.2.2 Error Register object). 
 *  
 *  @param msg CAN message object defined by the CAN_message_t struct definition that contains the CAN messages' extracted and grouped information. 
 */
void CAN_msg_handler::filter_EMCY(CAN_message_t &msg){

  uint8_t node_id = msg.id - 0x80; //The node id of an EMCY object is the object id minus 0x80
  uint16_t error_code = (msg.buf[1] << 8 | msg.buf[0]); //The first two bytes of the message make up the Error code
  uint8_t error_register = msg.buf[2]; //The third byte is the contents of the nodes error register object, the error cause. A single bit of this, the one associated with the error, cause will be set if an error occured.
  
  switch (node_id){
        
    if(CAN_FILTER_PRINT){
      Serial.println();
      Serial.println("Recieved an EMCY object: ");  
      Serial.println();
      print_CAN_message(msg);
    }

    case 1:

      node_info -> node_errors[0] = error_register;

    break;

    case 2:

      node_info -> node_errors[1] = error_register;

    break;

    case 3:

      node_info -> node_errors[2] = error_register;

    break;

    case 4:

      node_info -> node_errors[3] = error_register;

    break;
  }
}

/* ---------------------------------------------------------NETWORK MANAGEMENT (NMT) FUNCTIONS----------------------------------------------------------------------------------------------------------------------*/

/** @brief Reset Nodes Network Management message
 *  
 *  @details
 *  This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset (same effect as turning on and off the supply voltage).
 *  After the message is sent out, each node will reboot and once a node has entered the Pre-Operational state of the NMT Slave state machine, it will send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the reset was successful. See @ref NMT. 
 *  
 *  @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::reset_nodes()
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

  return (1-error_count); 
}

/** @brief Reset Communications Network Management message
 *  
 *  @details
 *  This function sends out a Netword Management (NMT) broadcast to all nodes signaling them to reset their communication parameters (cob-ids and such).
 *  After the message is sent out, each node will enter the Pre-Operational state of the NMT Slave state machine, it will also send out a boot up message
 *  whose cob-id is 700 + node_id. These messages will be used as confirmations that the communication reset was successful. 
 *  See @ref NMT. 
 *  
 *  @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::reset_communications()
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

  return (1-error_count); 
}

/** @brief Enter Pre Operational Network Management message
 *  
 * @details
 * This function sends the Network Management (NMT) message for "Enter Pre-Operational". It will send the message that signals every node to enter the Pre-Operational state (from either
 * the Operational or Stopped states) of the NMT Slave state machine. There will be no messages broadcast as a direct response to this command. In this state, SDO messages, Emergency objects, 
 * and NMT messages are permitted. See @ref NMT. 
 * 
 *  @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::enter_pre_operational()
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

/** @brief Start Remote Nodes Network Management message
 *  
 * @details
 * This function sends the Network Management (NMT) message for Starting Remote Nodes. It will send the message that signals every node to enter the Operational state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been set as a result. Can check the Statusword 
 * for confirmation. See [EPOS4 Communication guide](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Communication-Guide-En.pdf) "NMT Services" section 3.3.3.5 for NMT Slave state machine info.  
 * See [EPOS4 Firmware Specification](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Firmware-Specificatioin-En.pdf) "Statusword" section 6.2.73 and "Device Control" section 2.2 for more information
 * on the statusword.
 * 
 * @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::start_remote_nodes()
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

/** @brief Stop Remote Nodes Network Management message
 *  
 * @details
 * This function sends the Network Management (NMT) message for "Stop Remote Nodes". It will send the message that signals every node to enter the Stopped state of the NMT Slave state machine.
 * There will be no messages broadcast as a direct response to this command but bit 9 of the Statusword in each nodes object dictionary will have been cleared as a result. Can check the Statusword 
 * for confirmation. In this state, only NMT, Heartbeating, and Layer setting service messages are permitted.  
 * See [EPOS4 Firmware Specification](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Firmware-Specificatioin-En.pdf) "Statusword" section 6.2.73 and "Device Control" section 2.2 for more information
 * on the statusword.
 * 
 * @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::stop_remote_nodes()
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

/** @brief Set Operating Mode Service Data Object
 *  
 * @details
 *  This function sends the Servide Data Object (SDO) message for accessing the "Modes of Operation" object in the object dictionary of all 4 nodes. It will send an expedited one byteIt will send 4 expedited one byte
 *  write request SDOs. Confirmation of a successful write should be received by CAN_filter_task. [EPOS4 Firmware Specification](..\Documentation\CAN_and_Motor_Controllers\EPOS4-Firmware-Specificatioin-En.pdf)
 *  "Modes of Operation" section 6.2.78 for more information. 
 *  
 * @param operating_mode A one byte value signaling the operating mode the nodes are to be configured to. TORQUE_MODE (10) and PROFILE_VELOCITY_MODE (3) are the two options currently in use by the firmware. 
 *  
 * @return Returns the number of successful CAN writes.
*/
uint8_t CAN_msg_handler::SDO_set_operating_mode(uint8_t operating_mode)
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
  
  return (4-error_count);
}

/** @brief Set TxPDO1 Inhibit Time Service Data Object
 *  
 * @details
 *  This function will send out an SDO write message to the "Transmit PDO 1 parameter" object of each node. It will send 4 expedited two byte
 *  write request SDOs. The inhibit time is the minimum time between broadcasts of this particular PDO on each node. It is being set to a maximum frequency of about 180 hz. See EPOS4 Firmware Specification 
 *  pgs 6-85/86. For more information on Process Data Objects and inhibit time, see http://www.canopensolutions.com/english/about_canopen/pdo.shtml CANopen Basics - Process Data Exchange. 
*/
uint8_t CAN_msg_handler::set_TxPDO1_inhibit_time()
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

uint8_t CAN_msg_handler::request_statuswords()//This function requests the statusword of a node through SDO read request and confirmation.
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
 * It takes a control command which has been pound-defined in the h file from a set of available command codes specified in the EPOS4 documentation. Writing a particular command code to the controlword of a 
 * node triggers a transition in the "Device Control" state machine. Each transition also triggers a change in the Statusword of each node. See EPOS4 Firmware specification section 2.2 Device Control - pg 2-13 
 * for informatino on the "Device Control" state machine and Statusword and Controlword definitions. See section 6.6.2.72 Controlword - pg 6-160 for more information on the Controlword Object. 
 */
uint8_t CAN_msg_handler::RxPDO1_controlword_write(uint16_t control_command) //Send out the RxPDO1 message that updates the node's controlword object
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
 * See EPOS4 Firmware Specification section 6.2.86 Target Torque pg 6-167. 
 */
uint8_t CAN_msg_handler::RxPDO2_torque_write(int node_id, int32_t torque) //Send out the RxPDO1 message that updates the node's controlword object
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
 * of a motor controller's object dictionary. See EPOS4 Firmware Specification section 6.2.78 Modes of Operation - pg 6-164 and Section 6.2.115 Target Velocity - pg 6-188. 
 */
uint8_t CAN_msg_handler::RxPDO3_mode_and_TV_write(int node_id, uint8_t mode, int32_t target_velocity) //Send out an RxPDO3 message to write the operating the mode and the target velocity setpoint
{
  CAN_message_t msg;
  uint8_t error_count = 0;

  //RxPDO 2,updating the target torque
  msg.id = 0x400 + node_id; //COB-id of RxPDO 2 for this specific node
  msg.ext = 0;//Signifies wether the COB-id is 11 bit or 29 bit. Here it is an 11 bit identifier. 
  msg.rtr = 0;//Remote Transmit Request bit is low
  msg.len = 5;
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

void CAN_msg_handler::print_CAN_message(CAN_message_t msg)
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

uint8_t CAN_msg_handler::CAN_read_wait(unsigned long int timeout_millis){

  unsigned long int startMillis = millis();
  while( !Can0.available() ) {
    if ( !timeout_millis || (timeout_millis<=(millis()-startMillis)) ) {
      // early EXIT nothing here
      return 0;
    }
  }

  return 1;
}

uint8_t CAN_msg_handler::CAN_write_wait(uint16_t timeout_millis, CAN_message_t &msg){
  
  unsigned long int startMillis = millis();
  while( !Can0.write(msg) ) {
    if ( !timeout_millis || (timeout_millis<=(millis()-startMillis)) ) {
      // early EXIT nothing here
      return 0;
    }
  }

  return 1;
}

void CAN_msg_handler::print_CAN_statistics(){
  
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


