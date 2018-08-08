
/**
   CAN_Test_Code.ino - Dominic Riccoboni

*/

#include "ProgreSSIV_MC_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus preparation (From ProgreSSIV_MC_Driver)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*loop CAN variables.*/
uint8_t ret = 0;
uint8_t error = NO_ERROR;
int32_t velocity_FR;//stores rpm of node 1 (Front Right wheel)
int32_t velocity_FL;//stores rpm of node 2 (Front Left wheel)
int32_t velocity_RR;//stores rpm of node 3 (Rear Right wheel)
int32_t velocity_RL;//stores rpm of node 4 (Rear Left wheel)
uint16_t statusword_1;//stores statusword of node 1
uint16_t statusword_2;//stores statusword of node 2
uint16_t statusword_3;//stores statusword of node 3
uint16_t statusword_4;//stores statusword of node 4

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both for the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
volatile int16_t THR_in; // instantiate variable for throttle input value (ranges from ~-500 to 500)
volatile int16_t ST_in;  // instantiate variable for steering input value (ranges from ~-500 to 500)


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Debugging/Printing setup*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* General Debugging */
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define GENERAL_PRINT 1

bool CAN_Test_Flag = true;


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.

//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_motors;
unsigned long start_time_servo;
unsigned long start_time_print;
//unsigned long start_time_voltage;//Need to add in the voltage monitoring feature of the motor controllers. FUTURE WORK

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* The setup function runs all start up functions. Any functions that are run only once, always, and at startup should go here. */
void setup() {

  /*begin serial port operation*/
  Serial.begin(115200);
  delay(3000);

  if (GENERAL_PRINT) {
    Serial.println("Hello user. I am your debugging assistant. You may call me TeensyTron5000.");
    delay(500);
  }

  /*Startup CAN network (this is a FlexCAN function)*/
  Can0.begin(1000000); //void FlexCAN::begin (uint32_t baud, const CAN_filter_t &mask, uint8_t txAlt, uint8_t rxAlt)

//  /* Also going to do a little servo testing here*/
//  initPWMin();
//  initServo();

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly.*/
void loop() {

//    //This while loop will make sure there are no lingering NMT boot up messages in the CAN read buffer before beginning the Motor Controller initialization code
//    unsigned long start_time_CAN_check = millis();
//    unsigned long current_time_CAN_check = millis();
//    while(current_time_CAN_check - start_time_CAN_check <=1)
//    {
//      read_available_message(); 
//      current_time_CAN_check = millis();
//    }

  /* MOTOR CONTROLLER STARTUP CODE, WILL ONLY BE RUN ONCE*/
  if(CAN_Test_Flag){

    ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
    
    if (GENERAL_PRINT) {
      Serial <<"reset_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    }

    ret = reset_communications(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
    
    if (GENERAL_PRINT) {
      Serial <<"reset_communications function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    }    
      
    ret = enter_pre_operational(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
    
    if (GENERAL_PRINT) {
    Serial.println();
    Serial <<"enter_pre_operational function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
    Serial.println();
    Serial.println();
    }
    
    ret = set_torque_operating_mode(); // Configure all nodes for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 
    
    if (GENERAL_PRINT) {
      Serial <<"set_torque_operating_mode function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    }

    ret = set_TxPDO1_inhibit_time(); //Set the TxPDO1 inhibit time for all nodes
     
    if (GENERAL_PRINT) {
      Serial <<"set_TxPDO1_inhibit_time function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    } 

//    while(true )
//    {
////
////      read_available_message(); 
////      delay(10);
//    
//   }

//    ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
//    
//    if (GENERAL_PRINT) {
//      Serial <<"start_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//      Serial.println();
////      Serial.println();
////    }
//
//    delay(1); //Wait a little for the motor controllers to change state 
    
    //NEED TO REQUEST THE STATUSWORD OF EACH NODE HERE AND ENSURE THAT EACH IS IN NMT STATE OPERATIONAL (Bit 9 of statusword)
    
//    ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND); //Send out the controlword RxPDO with a shutdown command so that the device state machine transitions to the "Ready to switch on" state 
//    
//    if (GENERAL_PRINT) {
//      Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//      Serial.println();
//      Serial.println();
//    }
//    
//    delay(1); //Wait a little for the motor controllers to change state
//    
//    ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); //Send out the controlword RxPDO with an enable operation command so that the device state machine transitions to the "Operation Enabled" state 
//    
//    if (GENERAL_PRINT) {
//      Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//      Serial.println();
//      Serial.println();
//    }
//    
//    delay(1); //Wait a little for the motor controllers to change state 

    
//// NOW JUST TURNING THINGS OFF SO THAT I CAN READ THE STARTUP MESSAGES HERE BUT ALSO COMMUNICATE THROUGH EPOS STUDIO AFTERWARD
//
//     ret = RxPDO1_controlword_write(QUICK_STOP_COMMAND); //Send out the controlword RxPDO with an enable operation command so that the device state machine transitions to the "Quick Stop Active" state 
//                                                         //and then to the "Switch On Disabled" state
//     if (GENERAL_PRINT) {
//        Serial <<"RxPDO1_controlword_write(QUICK_STOP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//        Serial.println();
//        Serial.println();
//     }
//
//    delay(1000); //Wait a little for the motor controllers to change state (this may take a bit longer if the motors need to spin down to zero velocity (a quick stop action)
//
//     ret = stop_remote_nodes();// Send the NMT CAN message for stopping all CAN nodes. This stops all SDO and PDO exchange to and from the nodes but allows NMT messages. 
//      
//      if (GENERAL_PRINT) {
//        Serial <<"stop_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//      }
//      
//     delay(1); //Wait a little for the motor controllers to change state 
//     
//     ret = enter_pre_operational();// Send the NMT CAN message for the motor controllers to enter the pre-operational state. 
//     
//      if (GENERAL_PRINT) {
//        Serial <<"enter_pre_operational function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//      }
//      
//     delay(1); //Wait a little for the motor controllers to change state 
     
    CAN_Test_Flag = false;
    }
  }

///* BELOW IS CODE THAT WOULD RUN CONTINUOUSLY AS PART OF A TASK IN THE MAIN TEENSY FIRMWARE*/
//
//  //Initialize all timing variables for the loop. 
//  if (timing_init_flag) {
//    // Initialize the Timing Variables so that there is a start time
//    start_time_motors = micros();
//    start_time_servo = millis();
//    start_time_print = millis();
//    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
//    //start_time_voltage = millis();
//    timing_init_flag = false;
//  }
//  


//  unsigned long current_time_motors = micros();
//  if ((current_time_motors - start_time_motors) >= 556)  //556 microseconds => 180hz. Motor torque setpoints will update at this frequency
//  {
//
//    RxPDO2_torque_write(NODE_1, -THR_in);
//    RxPDO2_torque_write(NODE_2, THR_in);
//    RxPDO2_torque_write(NODE_3, -THR_in);
//    RxPDO2_torque_write(NODE_4, THR_in);
//    start_time_motors = current_time_motors;
//  }

//  if (GENERAL_PRINT)
//  {
//  
//    unsigned long current_time_print = millis();
//    if ((current_time_print - start_time_print) >= 5000)  //5,000 ms => 1/5hz. Print the values very slowly
//    {
//      Serial.println();
//      Serial.print("Velocity_FR = ");
//      Serial.println(velocity_FR, DEC);
//      Serial.print("Velocity_FL = ");
//      Serial.println(velocity_FL, DEC);
//      Serial.print("Velocity_RR = ");
//      Serial.println(velocity_RR, DEC);
//      Serial.print("Velocity_RL = ");
//      Serial.println(velocity_RL, DEC);
//      Serial.println();
//      start_time_print = current_time_print;
//    }
//  }

void try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and internal data and update the Teensy memory associated with that data or set a flag accordingly.
  CAN_message_t msg;// Struct defined in FlexCAN
  msg.timeout = 0;// Set timeout to zero so FlexCAN will only check for an incoming message, not wait for one. 
  if(CANbus.read(msg))//If there was something to read, this will be true and msg will be filled with CAN data from the most recent read buffer value (FlexCAN function)
  {
    Serial.println("TRY_CAN_MSG_FILTER READ OCCURED");
    switch(msg.id){
      
      
      case 0x1A1: //If TxPDO1, node 1 (the motor velocity)
      
        
        registers.reg_map.velocity_FR = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 1. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A2: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.velocity_FL = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 2. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A3: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.velocity_RR = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 3. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A4: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.velocity_RL = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 4. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
          
      break;

      case 0x2A1: //If TxPDO2, node 1 (the statusword)
      

        registers.reg_map.node_statuswords[0] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 1 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A2: //If TxPDO2, node 2 (the statusword)
      
        
        registers.reg_map.node_statuswords[1] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 2 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A3: //If TxPDO2, node 3 (the statusword)
      
        registers.reg_map.node_statuswords[2] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 3 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A4: //If TxPDO2, node 4 (the statusword )

        registers.reg_map.node_statuswords[3] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 4 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

      break;

      case 0x581: case 0x582: case 0x583: case 0x0584: //If Service Data Object from one of the nodes

        filter_SDO(&msg); //This function will interpret the Service Data Object and act occordingly. A pointer to the CAN message object is passed in

      break;

      case 0x701: case 0x702: case 0x703: case 0x704://If Network Management (NMT) Boot Up message
      
      break;
      
      default:
      break;
    }
  } 
}

void filter_SDO(CAN_message_t *msg){

  
  int16_t object_index = (msg->buf[2] << 8 | msg->buf[1]); //Concatinate the high and low byte of the object dictionairy index of the recieved SDO message
  int8_t command_specifier = msg->buf[0]; //Grab the command specifier of the recieved SDO message
  uint8_t node_id;
  
  switch (object_index){

    case 0x6040: //Controlword object dictionary index

    break;

    case 0x6041: //Statusword object dictionary index

        node_id = msg->id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_statuswords[node_id] = msg->buf[4]; //The first data byte of the SDO return message is the LSB of the Statusword for the node
        
        Serial.println("Recieved an SDO statusword response");  
        Serial.println();
        Serial.println(msg->id, HEX);
        Serial.println();  
        Serial.println(msg->buf[0], HEX);
        Serial.println();  
    break;

    case 0x6060: //Modes of operation object dictionary index

    break;

    case 0x1001: //Error register object dictionary index
    
      if(command_specifier == 0x4F){//If the command specifier indicates that the message was a read dictionary object reply of 1 byte
        
        node_id = msg->id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_errors[node_id] = msg->buf[4]; //The first data byte of the SDO return message 
        //error_flag = true;  
        
      }


    break;
    
  }
  
}

/* END OF MAIN LOOP*/






