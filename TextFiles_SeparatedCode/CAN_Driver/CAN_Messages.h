/* This text file contains every CAN message used in the uLaren_CAN_driver file.*/

/* NMT Messages
 (look at firmware specification documentation for the NMT state machine)*/

	//reset node communications
	msg.id = 0;//CAN_id for NMT or network management
	msg.ext = 0;//Default is 0...related to FlexCAN
	msg.len = 2;
	msg.timeout = 0;
	msg.buf[0] = 0x82;
	msg.buf[1] = 0;
	msg.buf[2] = 0;
	msg.buf[3] = 0;
	msg.buf[4] = 0;
	msg.buf[5] = 0;
	msg.buf[6] = 0;
	msg.buf[7] = 0;

	//"Start Remote Node CAN Message"
	msg.id = 0;//CAN_id for NMT or network management
	msg.ext = 0;//Default is 0...related to FlexCAN
	msg.len = 2;
	msg.timeout = 0; //Tells how long the system should wait for a response to this CAN message? LOOK AT FLEXCAN README FOR ANSWER TO THIS
	msg.buf[0] = 0x01; //(Command Specifier??) for "start_remote_node"
	msg.buf[1] = 0;//when set to zero, all slaves will be started
  
/* SDO Messages. 
These are run at startup for configuration purposes. A message is returned after sending these.
Must specify a COB-id of 600 plus the node id to send a message to a particular node. Must also send a command specifier
telling whether the message is a read or write and how many bytes. Then must send the object dictionary index and sub-index.
Finally must send the data associated with the write or zeros for each byte to be returned. */

	//Controlword Related
	
	  //tell MC's to go to shutdown state
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.ext = 0;
	  msg.len = 6; //Not certain but I think all SDO's need to be 8 bytes long...4 data bytes plus 4 overhead bytes
	  msg.timeout = 0;
	  msg.buf[0] = 0x2B; //Command Specifier for Write Dictionary Object of 2 bytes
	  msg.buf[2] = 0x60; //High byte of index for controlword dictionary object 
	  msg.buf[1] = 0x40; //Low byte of index for controlword dictionary object  
	  msg.buf[3] = 0x00; //Sub-index
	  msg.buf[5] = 0x00; //High byte of controlword data
	  msg.buf[4] = 0b00000110; //Low byte of controlword - Not sure how to use controlword yet

	  //tell MC's to go to switch-on state
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.ext = 0;
	  msg.len = 6;
	  msg.timeout = 0;
	  msg.buf[0] = 0x2B; //Command Specifier for Write Dictionary Object of 2 bytes
	  msg.buf[2] = 0x60; //High byte of index for controlword dictionary object 
	  msg.buf[1] = 0x40; //Low byte of index for controlword dictionary object
	  msg.buf[3] = 0x00; //Sub-index
	  msg.buf[5] = 0x00; //High byte of controlword data
	  msg.buf[4] = 0b00000111; //Low byte of controlword - Not sure how to use controlword yet
	  
	  //tell MC's to go to operation enabled state
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.ext = 0;
	  msg.len = 6;
	  msg.timeout = 0;
	  msg.buf[0] = 0x2B; //Command Specifier for Write Dictionary Object of 2 bytes
	  msg.buf[2] = 0x60; //High byte of index for controlword dictionary object 
	  msg.buf[1] = 0x40; //Low byte of index for controlword dictionary object
	  msg.buf[3] = 0x00; //Sub-index
	  msg.buf[5] = 0x01; //High byte of controlword data
	  msg.buf[4] = 0b00001111; //Low byte of controlword - Not sure how to use controlword yet
	  
	  //tell MC's to reset faults
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.ext = 0;
	  msg.len = 6;
	  msg.timeout = 0;
	  msg.buf[0] = 0x2B; //Command Specifier for Write Dictionary Object of 2 bytes
	  msg.buf[2] = 0x60; //High byte of index for controlword dictionary object
	  msg.buf[1] = 0x40; //Low byte of index for controlword dictionary object
	  msg.buf[3] = 0x00; //Sub-index
	  msg.buf[5] = 0x00; //High byte of controlword data
	  msg.buf[4] = 0b10000000; //Low byte of controlword - Not sure how to use controlword yet
	
	//Other SDO's
	
	  //initialize MC's to torque mode
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.len = 5;
	  msg.timeout = 0;
	  msg.buf[0] = 0x2F; //Command specifier for writing one byte dictionary object
	  msg.buf[2] = 0x60; //High byte of index for operating mode dictionary object 
	  msg.buf[1] = 0x60; //Low byte of index for operating mode dictionary object 
	  msg.buf[3] = 0; //Sub-index
	  msg.buf[4] = TORQUE_MODE; //Pound defined earlier. To set torque mode, write a 10 to the operating mode dict-ob
	  

	  //Statusword request message - after this message is sent, the reply is broadast to the CAN bus. Must be decoded. 	  
	  msg.id = 0x600 + node_id; //COB-id for an SDO client to server (server to client??) from the Teensy to a node
	  msg.ext = 0;
	  msg.len = 8;//Changed this to 8 so that the command specifier, index, subindex, and four bytes of junk data are sent (buf 0 - 7)
	  msg.timeout = 0;
	  msg.buf[0] = 0x40; //Command specifier for writing one byte dictionary object
	  msg.buf[2] = 0x60; //High byte of index for statusword dictionary object 
	  msg.buf[1] = 0x41; //Low byte of index for statusword dictionary object
	  msg.buf[3] = 0x00; //Sub-index
	  msg.buf[4] = 0x00; //Junk Data - this is a read request
	  msg.buf[5] = 0; //Junk Data - this is a read request
	  msg.buf[6] = 0; //Junk Data - this is a read request
	  msg.buf[7] = 0; //Junk Data - this is a read request
	  
/* PDO Messages.
 These are preconfigured for each motor controller in the EPOS Studio software. They are broadcasts 
to the CAN bus and are not replied to. They consist of a COB-id that indicates the particular PDO to be broadcast. Imediately
following the id are the data bytes of the object dictionary elements determined beforehand. 
Each PDO can write/read to/from up to 4 dictionary objects. There are multiple ways PDO's are broadcast - refer to Maxon 
documentation id "rel7290", the EPOS4 Communication guide, chapter 3 - CAN communication.*/  
	 
  //RxPDO 3, setting the CONTROLWORD value and updating the TARGET TORQUE. Each Motor Controller has been configured
  //to recieve this PDO, the difference in each's COB-id is the node_id in the least signigicant digit. 
  msg.id = 0x400 + node_id; //COB-id of RxPDO 3 for this specific node
  msg.ext = 0;
  msg.len = 6;
  msg.timeout = 0;
  //Control Word bytes (first object accessed with RxPDO 3)
  msg.buf[0] = 0x0F; //High byte of controlword data
  msg.buf[1] = 0x00; //Low byte of controlword data
  //Target torque bytes (second object accessed with RxPDO 3)
  memcpy(&(msg.buf[2]), (void *)(&throttle), 1);
  memcpy(&(msg.buf[3]), ((char *)(&throttle) + 1), 1);
  memcpy(&(msg.buf[4]), ((char *)(&throttle) + 2), 1);
  memcpy(&(msg.buf[5]), ((char *)(&throttle) + 3), 1);	 
  
  