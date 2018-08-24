/* Maxon EPOS4 Motor Controller CANopen filter designed by Dominic Riccoboni 
of the ProgreSSIV senior project team - Cal Poly San Luis Obispo  */

/*********************************/

#include "ProgreSSIV_CAN_filter_task.h"
#include "ProgreSSIV_CAN_write_driver.h"

/*General Debugging*/
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

CAN_filter_task::CAN_filter_task(node_info_t *node_info, volatile int16_t *node_rpms):

  node_info(node_info),
  node_rpms(node_rpms)//Initializer list 
  {
  
}

void CAN_filter_task::try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and internal data and update the Teensy memory associated with that data or set a flag accordingly.
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


//      case 0x81: case 0x82: case 0x83: case 0x084: //If the message was and EMCY object from one of the nodes
//
//        filter_EMCY(msg); 
//
//      break;
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

void CAN_filter_task::filter_SDO(CAN_message_t &msg){

  
  uint16_t object_index = (msg.buf[2] << 8 | msg.buf[1]); //Concatinate the high and low byte of the object dictionairy index of the recieved SDO message
  uint8_t command_specifier = msg.buf[0]; //Grab the command specifier of the recieved SDO message
  uint8_t node_id;
  
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

void CAN_filter_task::filter_PDO(CAN_message_t &msg){

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

void CAN_filter_task::filter_NMT(CAN_message_t &msg){

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

//void CAN_filter_task::filter_EMCY(CAN_message_t &msg){
//
//  //NOT YET IMPLEMENTED BUT SHOULD BE, EMCY OBJECTS WILL CONTAIN ERROR MESSAGES FROM NODES THAT GO INTO FAULT STATES
//  
//}

