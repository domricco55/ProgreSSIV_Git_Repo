 
/**
   CAN_Test_Code.ino - Dominic Riccoboni

*/

#include "ProgreSSIV_CAN_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Register Union for testing CAN interaction with SPI registers*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


///* Spi Register Setup*/
////Create a register struct to define data that will be read from, and written to over SPI. Values are volatile because the register map is being accessed during an interrupt
////service routine
typedef struct __attribute__ ((__packed__)) reg_struct {
  volatile uint8_t init_motor_controllers;
  volatile uint8_t dead_switch;
  //volatile uint8_t watchdog;
  volatile int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
  volatile int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
  //CAN Error Code Registers
  volatile uint8_t node_errors[4];//Array of node error messages
  //CAN Statusword Registers 
  volatile uint8_t node_statuswords[4];//Array of node statuswords
} reg_struct_t ;

//Union type definition linking the above reg_struct type to a 128 byte array. This will allow the same memory to be accessed by both the struct and the array. The above reg_struct_t defines names and types
//of variables that will be stored in the memory, or the "registers". The registers will be 128 bytes of memory that can be accessed in two different ways, one through the name as defined in the struct and
//another by simply indexing an array
typedef union __attribute__ ((__packed__)) reg_union {

  volatile uint8_t bytes[128];//Allocate 128 bytes of memory. The registers ARE these bytes.

  reg_struct_t reg_map; //Maps the 128 registers to data names and types as defined in the reg_struct above.

} reg_union_t;

reg_union_t registers;//Instantiate the register union (the registers will be filled with zeros by default)

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*CAN bus preparation (From ProgreSSIV_MC_Driver)*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/


/*CAN variables.*/
uint8_t ret = 0;
int32_t rpm_FR;//stores rpm of node 1 (Front Right wheel)
int32_t rpm_FL;//stores rpm of node 2 (Front Left wheel)
int32_t rpm_BR;//stores rpm of node 3 (Back Right wheel)
int32_t rpm_BL;//stores rpm of node 4 (Back Left wheel)
uint16_t statuswords[4];//stores statuswords locally
int32_t torque_write_error_cnt = 0;
int32_t torque_write_attempts = 0;

/* Motor Controller state machine setup */
enum MC_state{

  MC_state_0,  
  MC_state_1, 
  MC_state_2, 
  MC_state_3,
  MC_state_4,
  MC_state_5,
  MC_state_6,
  MC_state_7,
  MC_state_8,
  MC_state_9,
  MC_state_10,
  MC_state_11,
  MC_state_12
};

MC_state MC_state_var = MC_state_0; //First state to be entered

uint8_t bootup_count; 
uint8_t op_mode_SDO_count;
uint8_t inhibit_time_SDO_count;

/* Controlword values that drive the state transitions within the Device Control state machine. See EPOS4 Firmware Specification documentation for information on the controlword and state machine. */
#define SHUTDOWN_COMMAND 0x0006 //Controlword for shutdown. Takes the Device Control state machine from the "switch-on disabled" (post initialization state) to the "Ready to switch on" state. 
#define ENABLE_OP_COMMAND 0x000F //Controlword for switch on and enable. Puts Device Control state machine into "Operation enabled state" under MOST conditions. 
#define QUICKSTOP_COMMAND 0x000B //Controlword for Quick stop. Takes the Device Control state machine from the "Operation enabled" state to the "Quick stop active" state. The motors will decelerate to zero 
                                  //velocity at the quick stop deceleration value (index 0x6085). 
#define RESET_FAULT_COMMAND 0x0080 //Controlword for reset fault. Takes the Device Control state machine from the "fault" state to the "Switch on disabled state"
#define DISABLE_VOLTAGE_COMMAND 0x0000 //Controlword for disable voltage. Takes the Device Control state machine from the "quick stop active" state to the "Switch on disabled" state

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and throttle (both from the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
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
#define CAN_FILTER_PRINT 1

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.

//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_motors;
unsigned long start_time_servo;
unsigned long start_time_print;

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

  registers.reg_map.init_motor_controllers = 1;
  registers.reg_map.dead_switch = 1;
  
  /*Startup CAN network (this is a FlexCAN function)*/
  Can0.begin(1000000); //void FlexCAN::begin (uint32_t baud, const CAN_filter_t &mask, uint8_t txAlt, uint8_t rxAlt)
  Can0.startStats();//Begin gathering CAN statistics. FlexCAN function. 
  uint8_t num_mailboxes = Can0.setNumTxBoxes(1); //Set the number of transmit mailboxes. There are 16 mailboxes available in the CAN hardware. Anything not used for transmitting will be used for receiving. If set to 1, strict in order transmission occurs
  if (GENERAL_PRINT){
    Serial.println();
    Serial.print("The number of CAN Tx Mailboxes is: ");
    Serial.println(num_mailboxes);
    Serial.println();
  }
  /* Also going to do a little servo testing here*/
  initPWMin();
  initServo();
  writeServo(0);

}

/* Once setup has run its one time only code, loop() will begin executing. Loop should be run through continuously, with nothing halting its iterations indefinitely. Be careful
  when using delays and try to have tasks run quickly.*/
void loop() {

  //Initialize all timing variables for the loop. 
  if (timing_init_flag) {
    // Initialize the Timing Variables so that there is a start time
    start_time_motors = micros();
    start_time_servo = micros();
    start_time_print = millis();
    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
    //start_time_voltage = millis();
    timing_init_flag = false;
  }


/* MOTOR CONTROLLER STARTUP AND OPERATION STATE MACHINE*/


  //This tasks stack variables
  int16_t torque_actuate[4];
  unsigned long current_time_motors;

      
  switch(MC_state_var) {

    case MC_state_0: //Init

      bootup_count = 0; 
      op_mode_SDO_count = 0;
      inhibit_time_SDO_count = 0;

      MC_state_var = MC_state_1;
      if(GENERAL_PRINT){
        Serial.println();
        Serial.println("Transitioning to MC_state_1");
        Serial.println();
      }
    
    break;

    case MC_state_1: //Wait for init MCs flag - SPI task has access to this flag

      if(registers.reg_map.init_motor_controllers){
        
        ret = reset_nodes();// Send the NMT CAN message for resetting all CAN nodes. This has same effect as turning the power off and then on again.
    
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"reset_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }

        registers.reg_map.init_motor_controllers = 0; //Can be made true again by writing to SPI register location

        MC_state_var = MC_state_2;
        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_2");
          Serial.println();
        }
      }
    
    break;

    case MC_state_2: //Wait for reset node complete - A bootup confirmation should be received from each node 

      if(bootup_count == 4){

        bootup_count = 0; //Make sure this is cleared BEFORE sending reset_communications command
        
        ret = reset_communications(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"reset_communications() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_3;
        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_3");
          Serial.println();
        }
      }
    
    break;

    case MC_state_3: //Wait for reset communication complete - A bootup confirmation should be received from each node 

      if(bootup_count == 4){

        bootup_count = 0; 
        
        ret = enter_pre_operational(); // Send the NMT CAN message for resetting the communication. This calculates all the communication addresses and sets up the dynamic PDO mapping.
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"enter_pre_operational() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        delay(1); //Just want to be sure that they have time to transition before sending set torque operating mode command (nothing can confirm this NMT command)

        ret = set_torque_operating_mode(); // Configure all nodes for cyclic synchronous torque mode. This is an SDO to the operating mode object of the object dictionary. 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"set_torque_operating_mode() function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_4;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_4");
          Serial.println();
        }
        
      }
    
    break;

    case MC_state_4: //Wait for set torque mode Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(op_mode_SDO_count == 4){
        
        ret = set_TxPDO1_inhibit_time(); //Set the TxPDO1 inhibit time for all nodes
         
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"set_TxPDO1_inhibit_time() function call successfully wrote this many SDO's:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        op_mode_SDO_count = 0;
        
        MC_state_var = MC_state_5;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_5");
          Serial.println();
        }
      }
    
    break;

    case MC_state_5: //Wait for set inhibit time Service Data Object confirmation - SDO confirmations should be picked up by the CAN filter task 

      if(inhibit_time_SDO_count == 4){
        
        ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
 
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"start_remote_nodes() function call successfully wrote this many NMT commands:  "  << ret;
          Serial.println();
          Serial.println();
    
        }

        inhibit_time_SDO_count = 0;
        
        MC_state_var = MC_state_6;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_6");
          Serial.println();
        }
      }
    
    break;

    case MC_state_6: //Wait for remote nodes startup confirmation - the Statuswords of each node should indicate "Switch on disabled" device control state 

      if(statuswords[0] >> 8 & statuswords[1] >> 8 & statuswords[2] >> 8 & statuswords[3] >> 8 & 0b01000000){

        ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND);
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_7;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_7");
          Serial.println();
        }
        
      }
    
    break;

    case MC_state_7: //Wait for "Ready to switch on" device control state - the Statuswords of each node will indicate state 

      if(statuswords[0] >> 8 & statuswords[1] >> 8 & statuswords[2] >> 8 & statuswords[3] >> 8 & 0b00100001){

        if(!registers.reg_map.dead_switch){//If the dead switch feature is off
          
          ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
          
          if (GENERAL_PRINT) {
            Serial.println();
            Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
            Serial.println();
            Serial.println();
          }

          MC_state_var = MC_state_8;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_8");
            Serial.println();
          }
        }

        else{//The dead switch feature is on
           
          MC_state_var = MC_state_9;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_9");
            Serial.println();
          }
        }
        
      }
    
    break;

    case MC_state_8: //Wait for "Operation enabled" device control state = the Statuswords of each node will indicate state 

      if(registers.reg_map.node_statuswords[0] & registers.reg_map.node_statuswords[1] & registers.reg_map.node_statuswords[2] & registers.reg_map.node_statuswords[3] & 0b00100111 ){

        registers.reg_map.node_torques[0] = 0;
        registers.reg_map.node_torques[1] = 0;
        registers.reg_map.node_torques[2] = 0;
        registers.reg_map.node_torques[3] = 0;

        torque_actuate[0] = 0;
        torque_actuate[1] = 0;
        torque_actuate[2] = 0;
        torque_actuate[3] = 0;

        MC_state_var = MC_state_10;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_10");
          Serial.println();
        }       
      }


    break;

    case MC_state_9: //Wait for throttle - the dead switch flag is true and waiting for user to pull the throttle on the radio transeiver 

      if( THR_in >= 200){
        
        ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_8;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_8");
          Serial.println();
        }
      }
    
    
    break;

    case MC_state_10: //"Operation enabled" device control state, actuate torque - Send out the torque actuations at a set frequency of about 180hz 
      
      current_time_motors = micros();
      if ((current_time_motors - start_time_motors) >= 5555)  //5,555 microseconds => 180hz. Motor torque setpoints will update at this frequency (this frequency should prevent buffer overruns on the nodes
      {
        //If SPI task ends up being a task with access to the MC state machine data, this chunk of code will not need to be here
        torque_actuate[0] = -saturate_torque(registers.reg_map.node_torques[0]); //Front right wheel
        torque_actuate[1] = saturate_torque(registers.reg_map.node_torques[1]); //Front left wheel
        torque_actuate[2] = -saturate_torque(registers.reg_map.node_torques[2]); //Back right wheel
        torque_actuate[3] = saturate_torque(registers.reg_map.node_torques[3]); //Back left wheel

        for( uint8_t node_id = 1; node_id <= 4; node_id++ ){
          //Write saturated torque actuation values
          ret = RxPDO2_torque_write(node_id, torque_actuate[node_id-1]);
          
          if(!ret){
            torque_write_error_cnt++;
          }
          
          torque_write_attempts++;
        }

        start_time_motors = current_time_motors;
      }


      if(registers.reg_map.dead_switch){
        if(THR_in < 200){
        //If conditions for quickstop have been met

          if (GENERAL_PRINT){
            Serial.println();
            Serial.print("The Torque write error count was: ");
            Serial.println(torque_write_error_cnt);
            Serial.println();
            Serial.print("The Torque write attempt count was: ");
            Serial.println(torque_write_attempts);
            Serial.println();
          }
          torque_write_error_cnt = 0;
          torque_write_attempts = 0;
          
          //Write zero torque actuation values
          RxPDO2_torque_write(NODE_1, 0);
          RxPDO2_torque_write(NODE_2, 0);
          RxPDO2_torque_write(NODE_3, 0);
          RxPDO2_torque_write(NODE_4, 0);
          
          delayMicroseconds(10);
          
          ret = RxPDO1_controlword_write(QUICKSTOP_COMMAND); 
          
          if (GENERAL_PRINT) {
            Serial.println();
            Serial <<"RxPDO1_controlword_write(QUICKSTOP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
            Serial.println();
            Serial.println();
          }
          
          MC_state_var = MC_state_11;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_11");
            Serial.println();
          }
        }
      }
          
    break;

    case MC_state_11: //Wait for "Quickstop active" device control state - the Statuswords of each node will indicate state 
      
      if(statuswords[0] >> 8 & statuswords[1] >> 8 & statuswords[2] >> 8 & statuswords[3] >> 8 & 0b00000111 ){
      //If MCs have reached the "Quickstop active" device control state, transition
          
          MC_state_var = MC_state_12;

          if(GENERAL_PRINT){
            Serial.println();
            Serial.println("Transitioning to MC_state_12");
            Serial.println();
          }
      }

    break;

    case MC_state_12: //"Quickstop active" device control state - the dead switch flag is true and waiting for user to pull the throttle on the radio transeiver 

      if(THR_in >= 200){
        
        ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); 
        
        if (GENERAL_PRINT) {
          Serial.println();
          Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
          Serial.println();
          Serial.println();
        }
        
        MC_state_var = MC_state_8;

        if(GENERAL_PRINT){
          Serial.println();
          Serial.println("Transitioning to MC_state_8");
          Serial.println();
        }
      }
      
    break;
  }

  try_CAN_msg_filter(); //This will run as often as loop runs...which should be REALLY fast...checking for received CAN messages often


/* ---------------------------------FEATURES I AM OR WAS EXPERIMENTING WITH AT SOME POINT------------------------------------------------------------------------------------------------------------------------*/
//
//    //This while loop will make sure there are no lingering NMT boot up messages in the CAN read buffer before beginning the Motor Controller initialization code
//    unsigned long start_time_CAN_check = millis();
//    unsigned long current_time_CAN_check = millis();
//    while(current_time_CAN_check - start_time_CAN_check <=1000)
//    {
//      read_available_message(); 
//      current_time_CAN_check = millis();
//    }


//    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
//     
//    if (GENERAL_PRINT) {
//      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//      Serial.println();
//      Serial.println();
//    } 

//    unsigned long start_time_statuswait = millis();
//    unsigned long current_time_statuswait = millis(); 
//    while(current_time_statuswait - start_time_statuswait < 100)
//    {
//      try_CAN_msg_filter();
//      current_time_statuswait = millis();
//    }
//
//    if(GENERAL_PRINT)
//    { 
//      Serial.println();
//      Serial.println("After the enter pre operational function call, the statusword values were: ");
//      Serial.println();
//      Serial.print("  Statusword 1 = 0x");
//      Serial.println(statuswords[0], HEX);
//      Serial.print("  Statusword 2 = 0x");
//      Serial.println(statuswords[1], HEX);
//      Serial.print("  Statusword 3 = 0x");
//      Serial.println(statuswords[2], HEX);
//      Serial.print("  Statusword 4 = 0x");
//      Serial.println(statuswords[3], HEX);
//      Serial.println();     
//    }


      

//    /* TESTING ERROR REGISTER REQUEST SDO'S AND WRITE BUFFER OVERLOADING*/
//      Can0.clearStats();//Testing out the stats for the error register requests alone
//      Can0.startStats();//Begin gathering CAN statistics. FlexCAN function.
//      uint32_t write_error_count = 0;
//      unsigned long start_time_write = micros();
//      unsigned long start_time_test = millis();
//      Serial.println();
//      Serial.println("------------------------------------------------------------");
//      unsigned long current_time_test = millis();
//      while(current_time_test - start_time_test <5000){
//        
//        try_CAN_msg_filter();
//        
//        unsigned long current_time_write= micros();
//        if ((current_time_write - start_time_write) >= 2000) 
//        {
//          if(request_error_registers()){
//          
//            write_error_count++; //Send out an expedited error register read request to all nodes 
//                    
//          }
//          start_time_write = current_time_write;
//        }
//        
//        current_time_test = millis();
// 
//      }
//
//      print_CAN_statistics();
//
//      try_CAN_msg_filter();
//      
//      Serial.println();
//      Serial.print("The number of write errors during the loop was: ");
//      Serial.println(write_error_count);
//      Serial.println();
//      Serial.println("------------------------------------------------------------");   
//      Serial.println();   

/* -------------------------------------END OF EXPERIMENTAL FEATURES-----------------------------------------------------------------------------------------------------------------------------------------------*/

    

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

//    unsigned long current_time_print = millis();
//    if ((current_time_print - start_time_print) >= 5000)  //5,000 ms => 1/5hz. Print the values very slowly
//    {
//      Serial.println();
//      Serial.print("Statusword 1 = 0x");
//      Serial.println(registers.reg_map.node_statuswords[1], HEX);
//      Serial.print("Statusword 2 = 0x");
//      Serial.println(registers.reg_map.node_statuswords[2], HEX);
//      Serial.print("Statusword 3 = 0x");
//      Serial.println(registers.reg_map.node_statuswords[3], HEX);
//      Serial.print("Statusword 4 = 0x");
//      Serial.println(registers.reg_map.node_statuswords[4], HEX);
//      Serial.println();
//
//      Serial.println();
//      Serial.print("Error 1 = 0x");
//      Serial.println(registers.reg_map.node_errors[1], HEX);
//      Serial.print("Error 2 = 0x");
//      Serial.println(registers.reg_map.node_errors[2], HEX);
//      Serial.print("Error 3 = 0x");
//      Serial.println(registers.reg_map.node_errors[3], HEX);
//      Serial.print("Error 4 = 0x");
//      Serial.println(registers.reg_map.node_errors[4], HEX);
//      Serial.println();
//
//
//      print_CAN_statistics();
//      
//      start_time_print = current_time_print;
//    }

//    unsigned long current_time_servo = micros();
//    if ((current_time_servo - start_time_servo) >= 3000) 
//    {
//      writeServo(ST_in);
//      Serial.println(ST_in);
//      start_time_servo = current_time_servo;
//    }


     
  }
/* END OF MAIN LOOP*/


void try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and internal data and update the Teensy memory associated with that data or set a flag accordingly.
  CAN_message_t msg;// Struct defined in FlexCAN 
  if(Can0.read(msg))//If there was something to read, this will be true and msg will be filled with CAN data from the most recent read buffer value (FlexCAN function)
  {
    if(CAN_FILTER_PRINT){
      Serial.print("TRY_CAN_MSG_FILTER READ OCCURED, the id was: ");
      Serial.println(msg.id, HEX);
    }
    
    switch(msg.id){
      
      
      case 0x1A1: //If TxPDO1, node 1 (the motor velocity)
      
        
        registers.reg_map.node_rpms[0] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 1. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A2: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.node_rpms[1] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 2. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A3: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.node_rpms[2] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 3. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
        
      break;

      case 0x1A4: //If TxPDO1, node 1 (the motor velocity)

        registers.reg_map.node_rpms[3] = (int16_t)((msg.buf[1] << 8) | msg.buf[0]); // This is extracting the velocity reading from TxPDO1 node 4. Units are in RPM.
                                                                                   //(original message is 32 bits but we're ignoring 2 high bytes because the motors never spin that fast)
          
      break;

      case 0x2A1: //If TxPDO2, node 1 (the statusword)
      
        statuswords[0] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 1, both high byte and low byte, and storing the whole 16 bit statusword locally.

        registers.reg_map.node_statuswords[0] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 1 (High byte of the statusword is ignored here because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A2: //If TxPDO2, node 2 (the statusword)
      
        statuswords[1] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 2, both high byte and low byte, and storing the whole 16 bit statusword locally.
        
        registers.reg_map.node_statuswords[1] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 2 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A3: //If TxPDO2, node 3 (the statusword)

        statuswords[2] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 3, both high byte and low byte, and storing the whole 16 bit statusword locally.
      
        registers.reg_map.node_statuswords[2] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 3 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

          
      break;

      case 0x2A4: //If TxPDO2, node 4 (the statusword )

        statuswords[3] = (uint16_t)(msg.buf[1] << 8 | msg.buf[0]); //This is extracting the statusword value from TxPDO2 node 4, both high byte and low byte, and storing the whole 16 bit statusword locally.

        registers.reg_map.node_statuswords[3] = (uint8_t)(msg.buf[0]); // This is extracting the statusword value from TxPDO2 node 4 (High byte of the statusword is ignored because Device Control state information is only stored in the low byte)

      break;

      case 0x581: case 0x582: case 0x583: case 0x0584: //If Service Data Object from one of the nodes

        filter_SDO(msg); //This function will interpret the Service Data Object and act occordingly. A reference to the CAN message object is passed in

      break;

      case 0x701: case 0x702: case 0x703: case 0x704:
      
        if(msg.buf[0] == 0 && msg.buf[1] == 0 && msg.buf[2] == 0 && msg.buf[3] == 0 && msg.buf[4] == 0 && msg.buf[5] == 0 &&msg.buf[6] == 0 &&msg.buf[7] == 0){ //If Network Management (NMT) Boot Up message
         
          bootup_count++;
          
          if(CAN_FILTER_PRINT){
          Serial.println();
          Serial.println("Recieved a bootup confirmation");  
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
}

void filter_SDO(CAN_message_t &msg){

  
  uint16_t object_index = (msg.buf[2] << 8 | msg.buf[1]); //Concatinate the high and low byte of the object dictionairy index of the recieved SDO message
  uint8_t command_specifier = msg.buf[0]; //Grab the command specifier of the recieved SDO message
  uint8_t node_id;
  
  switch (object_index){

    case 0x6040: //Controlword object dictionary index

    break;

    case 0x6041: //Statusword object dictionary index

        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_statuswords[node_id-1] = msg.buf[4]; //The first data byte of the SDO return message is the LSB of the Statusword for the node. For storage in SPI registers
        statuswords[node_id-1] = (uint16_t)(msg.buf[5] << 8 | msg.buf[4]); //Store the FULL 16 bit statusword for local Teensy use
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
        
        op_mode_SDO_count++;
        
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

    case 0x1001: //Error register object dictionary index
    
      //if(command_specifier == 0x4B){//If the command specifier indicates that the message was a read dictionary object reply of 1 byte
        
        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_errors[node_id-1] = msg.buf[4]; //The first data byte of the SDO return message 
        //error_flag = true;  
        
        if(CAN_FILTER_PRINT){
          
          Serial.println("Recieved an SDO error register response");  
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
        
     // }


    break;

    case 0x1800:

      if((command_specifier == 0x60) && (msg.buf[3] == 0x03)){//If the SDO was an expedited write confirmation (command specifier of 0x60) AND the subindex was that of the inhibit time (3)
        
        inhibit_time_SDO_count++;
        
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

int16_t saturate_torque(int16_t torque_command)
{

  if (torque_command > 1000){ //Torque command is in units of [MotorRatedTorque/1000] and we want the max user input torque to be the max continutous torque, i.e. the rated torque. 

    torque_command = 1000; 
    
  }

  if (torque_command < -1000){
    torque_command = -1000;
  }

  return torque_command;
}






