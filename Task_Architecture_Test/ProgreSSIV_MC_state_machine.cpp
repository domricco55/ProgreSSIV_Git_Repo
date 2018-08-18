/* Maxon EPOS4 Motor Controller State machine designed by Dominic Riccoboni 
of the ProgreSSIV senior project team - Cal Poly San Luis Obispo  */

/*********************************/

#include "ProgreSSIV_MC_state_machine.h"
#include "ProgreSSIV_CAN_driver.h"

/*General Debugging*/
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}

#define MC_STATE_MACHINE_PRINT 1  



MC_state_machine::MC_state_machine( SPI_commands_t *SPI_commands_struct, int16_t *SPI_torque_actuations, node_info_t *node_info, radio_struct_t *radio_struct ){

  /* Initialize member attribute pointers to shared structs */
  SPI_commands_struct = SPI_commands_struct;
  int16_t *torque_actuations = SPI_torque_actuations;
  node_info = node_info; //Contains statuswords, modes of operation displays, error messages, etc. Data read in CAN filter task is placed into this struct 
  radio_struct = radio_struct;

  /* Initialize other member attributes */
  int32_t write_error_cnt = 0;
  int32_t torque_write_attempts = 0;
  unsigned long start_time_motors = millis();
  MC_state MC_state_var = MC_state_0; //First state to be entered - intitializing the state variable
}



void MC_state_machine::run_sm(){

/* MOTOR CONTROLLER STARTUP AND OPERATION STATE MACHINE*/

  //This tasks stack variables
  unsigned long current_time_motors;
  uint8_t ret = 0;
     
  switch(MC_state_var) {

    case MC_state_0: //Init

      node_info -> bootup_count = 0; 
      node_info -> op_mode_SDO_count = 0;
      node_info -> inhibit_time_SDO_count = 0;
      
      ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
  
      if (MC_STATE_MACHINE_PRINT) {
        Serial.println();
        Serial <<"reset_nodes() function call successfully wrote this many NMT commands:  "  << ret;
        Serial.println();
        Serial.println();
      }
      
      MC_state_var = MC_state_1;
      if(MC_STATE_MACHINE_PRINT){
        Serial.println();
        Serial.println("Transitioning to MC_state_1");
        Serial.println();
      }
    
    break;

    case MC_state_1: //Wait for init MCs flag - SPI task has access to this flag

      if(node_info -> bootup_count == 4){

        node_info -> bootup_count = 0; //Make sure this is cleared BEFORE sending reset_communications command
        
        ret = reset_communications(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"reset_communications() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_2;
        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state2");
          Serial.println();
        }
      }
    
    break;

    case MC_state_2: //Wait for reset node complete - A bootup confirmation should be received from each node 
    
      if(SPI_commands_struct -> init_motor_controllers && node_info -> bootup_count==4){
        
        node_info -> bootup_count = 0; 
        
        ret = enter_pre_operational(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"enter_pre_operational() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)

        ret = SDO_set_operating_mode(TORQUE_MODE); // Configure all nodes for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"SDO_set_operating_mode(TORQUE_MODE) function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        SPI_commands_struct -> init_motor_controllers = 0; //Can be made true again by writing to SPI register location

        MC_state_var = MC_state_3;
        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_3");
          Serial.println();
        }
      }


             
    
    break;

    case MC_state_3: //Wait for set torque mode Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(node_info -> op_mode_SDO_count == 4){
        
        delayMicroseconds(10);
        ret = set_TxPDO1_inhibit_time(); //Set the TxPDO1 inhibit time for all nodes
         
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"set_TxPDO1_inhibit_time() function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        node_info -> op_mode_SDO_count = 0;
        
        MC_state_var = MC_state_4;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_4");
          Serial.println();
        }
      }
    
    break;

    case MC_state_4: //Wait for set inhibit time Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(node_info -> inhibit_time_SDO_count == 4){

        delayMicroseconds(10);
        ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
 
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"start_remote_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"start_remote_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        node_info -> inhibit_time_SDO_count = 0;
        
        MC_state_var = MC_state_5;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_5");
          Serial.println();
        }
      }
    
    break;

    case MC_state_5: //Wait for remote nodes startup confirmation - the Statuswords of each node should indicate "Switch on disabled" device control state 

      if(node_info -> node_statuswords[0] & node_info -> node_statuswords[1]  & node_info -> node_statuswords[2] & node_info -> node_statuswords[3] & 0b01000000){
        
        delayMicroseconds(10);
        ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND);
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_6;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_6");
          Serial.println();
        }
        
      }
    
    break;

    case MC_state_6: //Wait for "Ready to switch on" device control state - the Statuswords of each node will indicate state 

      if(node_info -> node_statuswords[0] & node_info -> node_statuswords[1]  & node_info -> node_statuswords[2] & node_info -> node_statuswords[3] & 0b00100001){

        if(!SPI_commands_struct -> dead_switch){//If the dead switch feature is off
          
          ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
          
          if (MC_STATE_MACHINE_PRINT) {
            Serial.println();
            Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
            Serial.println();
            Serial.println();
          }

          MC_state_var = MC_state_7;

          if(MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_7");
            Serial.println();
          }
        }

        else{//The dead switch feature is on
           
          MC_state_var = MC_state_8;

          if(MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_8");
            Serial.println();
          }
        }
        
      }
    
    break;

    case MC_state_7: //Wait for "Operation enabled" device control state = the Statuswords of each node will indicate state 

      if(node_info -> node_statuswords[0] & node_info -> node_statuswords[1]  & node_info -> node_statuswords[2] & node_info -> node_statuswords[3] & 0b00100111 ){

        torque_actuations[0] = 0;
        torque_actuations[1] = 0;
        torque_actuations[2] = 0;
        torque_actuations[3] = 0;

        MC_state_var = MC_state_9;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_9");
          Serial.println();
        }       
      }


    break;

    case MC_state_8: //Wait for throttle - the dead switch flag is true and waiting for user to pull the throttle on the radio transeiver 

      if( radio_struct -> THR_in >= 200){
        
        ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
        
        if (MC_STATE_MACHINE_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_7;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_7");
          Serial.println();
        }
      }
    
    
    break;

    case MC_state_9: //"Operation enabled" device control state, actuate torque - Send out the torque actuations at a set frequency of about 180hz 
      
      current_time_motors = micros();
      if ((current_time_motors - start_time_motors) >= 5555)  //5,555 microseconds => 180hz. Motor torque setpoints will update at this frequency (this frequency should prevent buffer overruns on the nodes
      {
        //Load the SPI task torque actuations into the local torque actuation array
        saturated_casted_torques[0] = (int32_t)(-saturate_torque(torque_actuations[0])); //Front right wheel
        saturated_casted_torques[1] = (int32_t)saturate_torque(torque_actuations[1]); //Front left wheel
        saturated_casted_torques[2] = (int32_t)(-saturate_torque(torque_actuations[2])); //Back right wheel
        saturated_casted_torques[3] = (int32_t)saturate_torque(torque_actuations[3]); //Back left wheel

        for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
          //Write saturated torque actuation values
          ret = RxPDO2_torque_write(node_id,saturated_casted_torques[node_id-1]);
          
          if(!ret){
            write_error_cnt++;
          }
          
          torque_write_attempts++;
        }

        start_time_motors = current_time_motors;
      }


      if(SPI_commands_struct -> dead_switch){
        if(radio_struct -> THR_in < 200){
        //If conditions for quickstop have been met

          if (MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.print("The Torque write error count was: ");
            Serial.println(write_error_cnt);
            Serial.println();
            Serial.print("The Torque write attempt count was: ");
            Serial.println(torque_write_attempts);
            Serial.println();
          }
          write_error_cnt = 0;
          torque_write_attempts = 0;
          
          //Write zero torque actuation values
          RxPDO2_torque_write(NODE_1, 0);
          RxPDO2_torque_write(NODE_2, 0);
          RxPDO2_torque_write(NODE_3, 0);
          RxPDO2_torque_write(NODE_4, 0);
          
          delayMicroseconds(10);

          //Write 4 RxPDO3's, one for each node telling to go to Profile Velocity Mode and set each's target velocity to zero
          for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
            //Write saturated torque actuation values
            ret = RxPDO3_mode_and_TV_write(node_id, PROFILE_VELOCITY_MODE, 0 );
            
            if(!ret){
              write_error_cnt++;
            }
          }  

          if (MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.print("4 RxPDO3 write messages attempted - the write error count was: ");
            Serial.println(write_error_cnt);
            Serial.println();
          }
          
          write_error_cnt = 0;
          
          MC_state_var = MC_state_10;

          if(MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_10");
            Serial.println();
          }
        }
      }
          
    break;

    case MC_state_10: //Wait for Velocity Profile Mode confirmation - TxPDO3 Modes of Operation Display
      
      if(node_info -> mode_of_op_displays[0] & node_info -> mode_of_op_displays[1] & node_info -> mode_of_op_displays[2] & node_info -> mode_of_op_displays[3] & PROFILE_VELOCITY_MODE ){
      //If MCs are now in Profile Velocity Mode
          
          MC_state_var = MC_state_11;

          if(MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_11");
            Serial.println();
          }
      }

    break;

    case MC_state_11: //Velocity Profile Mode Zero Velocity
      
      if(radio_struct -> THR_in >= 200){
        
          //Write 4 RxPDO3's, one for each node telling to go to Torque Mode. The Target Velocity is irrelevant at this point but it's mapped to the PDO so we will just write a zero
          for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
            //Write saturated torque actuation values
            ret = RxPDO3_mode_and_TV_write(node_id, TORQUE_MODE, 0 );
            
            if(!ret){
              write_error_cnt++;
            }
          }  

          if (MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.print("4 RxPDO3 write messages attempted - the write error count was: ");
            Serial.println(write_error_cnt);
            Serial.println();
          }
          
          write_error_cnt = 0;
        
        MC_state_var = MC_state_12;

        if(MC_STATE_MACHINE_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_12");
          Serial.println();
        }
      }
      
    break;
    
    case MC_state_12: //Wait for Torque Mode confirmation - TxPDO3 Modes of Operation Display will update the mode_of_op_displays array. 
      
      if(node_info -> mode_of_op_displays[0] & node_info -> mode_of_op_displays[1] & node_info -> mode_of_op_displays[2] & node_info -> mode_of_op_displays[3] & TORQUE_MODE ){
      //If MCs are now in Torque Mode
          
          MC_state_var = MC_state_9;

          if(MC_STATE_MACHINE_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_9");
            Serial.println();
          }
      }

    break;
  }
}

int16_t MC_state_machine::saturate_torque(int16_t torque_command)
{

  if (torque_command > 1000){ //Torque command is in units of [MotorRatedTorque/1000] and we want the max user input torque to be the max continutous torque, i.e. the rated torque. 

    torque_command = 1000; 
    
  }

  if (torque_command < -1000){
    torque_command = -1000;
  }

  return torque_command;
}
