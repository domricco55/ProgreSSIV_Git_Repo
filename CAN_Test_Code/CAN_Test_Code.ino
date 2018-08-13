 
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
  volatile int16_t throttle_front_right;
  volatile int16_t throttle_front_left;
  volatile int16_t throttle_rear_right;
  volatile int16_t throttle_rear_left;
  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
  volatile int16_t velocity_FR;//stores rpm of node 1 (Front Right wheel)
  volatile int16_t velocity_FL;//stores rpm of node 2 (Front Left wheel)
  volatile int16_t velocity_RR;//stores rpm of node 3 (Rear Right wheel)
  volatile int16_t velocity_RL;//stores rpm of node 4 (Rear Left wheel)
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


/*loop CAN variables.*/
uint8_t ret = 0;
int32_t velocity_FR;//stores rpm of node 1 (Front Right wheel)
int32_t velocity_FL;//stores rpm of node 2 (Front Left wheel)
int32_t velocity_RR;//stores rpm of node 3 (Rear Right wheel)
int32_t velocity_RL;//stores rpm of node 4 (Rear Left wheel)
uint16_t statuswords[4];//stores statuswords locally
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*Radio Preparation*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Steering and Throttle (both from the radio) variable instantiation. These are EXTERNS found in input_handler and are updated in an interrupt service routine in that code*/
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
#define CAN_FILTER_PRINT 0

bool CAN_Test_Flag = true;


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/* Timing/Frequency setup */
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

bool timing_init_flag = true; //This flag allows the timing variables to be initialized only once in spi task.

//These will act as the previous clock value for which to compare the current value to. These are used to let code run at specified frequencies.
unsigned long start_time_motors;
unsigned long start_time_servo;
unsigned long start_time_print;
unsigned long start_time_error_check;

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

  /* MOTOR CONTROLLER STARTUP CODE, WILL ONLY BE RUN ONCE*/
  if(CAN_Test_Flag){

    //This while loop will make sure there are no lingering NMT boot up messages in the CAN read buffer before beginning the Motor Controller initialization code
    unsigned long start_time_CAN_check = millis();
    unsigned long current_time_CAN_check = millis();
    while(current_time_CAN_check - start_time_CAN_check <=1000)
    {
      read_available_message(); 
      current_time_CAN_check = millis();
    }

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

    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
     
    if (GENERAL_PRINT) {
      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    } 

    unsigned long start_time_statuswait = millis();
    unsigned long current_time_statuswait = millis(); 
    while(current_time_statuswait - start_time_statuswait < 100)
    {
      try_CAN_msg_filter();
      current_time_statuswait = millis();
    }

    if(GENERAL_PRINT)
    { 
      Serial.println();
      Serial.println("After the enter pre operational function call, the statusword values were: ");
      Serial.println();
      Serial.print("  Statusword 1 = 0x");
      Serial.println(statuswords[0], HEX);
      Serial.print("  Statusword 2 = 0x");
      Serial.println(statuswords[1], HEX);
      Serial.print("  Statusword 3 = 0x");
      Serial.println(statuswords[2], HEX);
      Serial.print("  Statusword 4 = 0x");
      Serial.println(statuswords[3], HEX);
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

    
    ret = start_remote_nodes(); // Send the NMT CAN message for starting all remote nodes. This will put each node into the NMT operational state and PDO exchange will begin. 
    
    if (GENERAL_PRINT) {
      Serial <<"start_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    }
    

    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
     
    if (GENERAL_PRINT) {
      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    } 

    start_time_statuswait = millis();
    current_time_statuswait = millis(); 
    while(current_time_statuswait - start_time_statuswait < 100)
    {
      try_CAN_msg_filter();
      current_time_statuswait = millis();
    }

    if(GENERAL_PRINT)
    {
      Serial.println();
      Serial.println("After the start remote nodes function call, the statusword values were: ");
      Serial.println();
      Serial.print("  Statusword 1 = 0x");
      Serial.println(statuswords[0], HEX);
      Serial.print("  Statusword 2 = 0x");
      Serial.println(statuswords[1], HEX);
      Serial.print("  Statusword 3 = 0x");
      Serial.println(statuswords[2], HEX);
      Serial.print("  Statusword 4 = 0x");
      Serial.println(statuswords[3], HEX);
      Serial.println();       
    }
    
    ret = RxPDO1_controlword_write(SHUTDOWN_COMMAND); //Send out the controlword RxPDO with a shutdown command so that the device state machine transitions to the "Ready to switch on" state 
    
    if (GENERAL_PRINT) {
      Serial <<"RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
      Serial.println();
      Serial.println();
    }

    delay(1);//Wait a little bit for the motor controllers to change state and then request the statuswords

    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
     
    if (GENERAL_PRINT) {
      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    } 

    start_time_statuswait = millis();
    current_time_statuswait = millis(); 
    while(current_time_statuswait - start_time_statuswait < 100)
    {
      try_CAN_msg_filter();
      current_time_statuswait = millis();
    }

    if(GENERAL_PRINT)
    {
      Serial.println();
      Serial.println("After the RxPDO1_controlword_write(SHUTDOWN_COMMAND) function call, the statusword values were: ");
      Serial.println();
      Serial.print("  Statusword 1 = 0x");
      Serial.println(statuswords[0], HEX);
      Serial.print("  Statusword 2 = 0x");
      Serial.println(statuswords[1], HEX);
      Serial.print("  Statusword 3 = 0x");
      Serial.println(statuswords[2], HEX);
      Serial.print("  Statusword 4 = 0x");
      Serial.println(statuswords[3], HEX);
      Serial.println();           
    }
    
    
    ret = RxPDO1_controlword_write(ENABLE_OP_COMMAND); //Send out the controlword RxPDO with an enable operation command so that the device state machine transitions to the "Operation Enabled" state 
    
    if (GENERAL_PRINT) {
      Serial <<"RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
      Serial.println();
      Serial.println();
    }    
    
    delay(1);//Wait a little bit for the motor controllers to change state and then request the statuswords
    
    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
     
    if (GENERAL_PRINT) {
      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
      Serial.println();
      Serial.println();
    } 

    start_time_statuswait = millis();
    current_time_statuswait = millis(); 
    while(current_time_statuswait - start_time_statuswait < 100)
    {
      try_CAN_msg_filter();
      current_time_statuswait = millis();
    }

    if(GENERAL_PRINT)
    {
      Serial.println();
      Serial.println("After the RxPDO1_controlword_write(ENABLE_OP_COMMAND) function call, the statusword values were: ");
      Serial.println();
      Serial.print("  Statusword 1 = 0x");
      Serial.println(statuswords[0], HEX);
      Serial.print("  Statusword 2 = 0x");
      Serial.println(statuswords[1], HEX);
      Serial.print("  Statusword 3 = 0x");
      Serial.println(statuswords[2], HEX);
      Serial.print("  Statusword 4 = 0x");
      Serial.println(statuswords[3], HEX);
      Serial.println();     
    }
    
//    
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
//    delay(1); //Wait a little for the motor controllers to change state and then request the statuswords
//
//    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
//     
//    if (GENERAL_PRINT) {
//      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//      Serial.println();
//      Serial.println();
//    } 
//
//    start_time_statuswait = millis();
//    current_time_statuswait = millis(); 
//    while(current_time_statuswait - start_time_statuswait < 100)
//    {
//      try_CAN_msg_filter();
//      current_time_statuswait = millis();
//    }
//
//    if(GENERAL_PRINT)
//    {
//      Serial.println();
//      Serial.println("After the RxPDO1_controlword_write(QUICK_STOP_COMMAND) function call, the statusword values were: ");
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
//    
//     ret = RxPDO1_controlword_write(DISABLE_VOLTAGE_COMMAND); //Send out the controlword RxPDO with an enable operation command so that the device state machine transitions to the "Quick Stop Active" state 
//                                                         //and then to the "Switch On Disabled" state
//     if (GENERAL_PRINT) {
//        Serial <<"RxPDO1_controlword_write(DISABLE_VOLTAGE_COMMAND) function call successfully wrote this many PDO's:  "  << ret;
//        Serial.println();
//        Serial.println();
//     }
//
//    delay(1); //Wait a little for the motor controllers to change state and then request the statuswords
//
//    ret = request_statuswords(); //Send out an expedited statusword read request to all nodes
//     
//    if (GENERAL_PRINT) {
//      Serial <<"request_statusword function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//      Serial.println();
//      Serial.println();
//    } 
//
//    start_time_statuswait = millis();
//    current_time_statuswait = millis(); 
//    while(current_time_statuswait - start_time_statuswait < 100)
//    {
//      try_CAN_msg_filter();
//      current_time_statuswait = millis();
//    }
//
//    if(GENERAL_PRINT)
//    {
//      Serial.println();
//      Serial.println("After the RxPDO1_controlword_write(QUICK_STOP_COMMAND) function call, the statusword values were: ");
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
//     ret = stop_remote_nodes();// Send the NMT CAN message for stopping all CAN nodes. This stops all SDO and PDO exchange to and from the nodes but allows NMT messages. 
//      
//      if (GENERAL_PRINT) {
//        Serial <<"stop_remote_nodes function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//      }
//      
//    delay(10); //Wait a little for the motor controllers to change state and then request the statuswords


     //STOP
     
//     ret = enter_pre_operational();// Send the NMT CAN message for the motor controllers to enter the pre-operational state. 
//     
//      if (GENERAL_PRINT) {
//        Serial <<"enter_pre_operational function call returned error code "  << ret << " which may later be used for error checking in the main Teensy firmware";
//        Serial.println();
//        Serial.println();
//      }
//      
//     delay(1); //Wait a little for the motor controllers to change state 

      

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

      
      CAN_Test_Flag = false;
    }
  

  
///* BELOW IS CODE THAT WOULD RUN CONTINUOUSLY AS PART OF A TASK IN THE MAIN TEENSY FIRMWARE*/

  //Initialize all timing variables for the loop. 
  if (timing_init_flag) {
    // Initialize the Timing Variables so that there is a start time
    start_time_motors = micros();
    start_time_servo = micros();
    start_time_print = millis();
    start_time_error_check = millis();
    //Need to implement the motor controller voltage sensing again. The uLaren team had implemented this but I have not been able to get to it yet. Refer to their code for help.
    //start_time_voltage = millis();
    timing_init_flag = false;
  }
  

//  unsigned long current_time_error_check = millis();
//  if ((current_time_error_check - start_time_error_check) >= 2000) 
//  {
//    
////    request_error_registers(); //Send out an expedited error register read request to all nodes 
////    //request_statuswords();
//
//    
//    start_time_error_check = current_time_error_check;
//  }
    

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

    unsigned long current_time_servo = micros();
    if ((current_time_servo - start_time_servo) >= 3000) 
    {
      writeServo(ST_in);
      Serial.println(ST_in);
      start_time_servo = current_time_servo;
    }


     
  }
/* END OF MAIN LOOP*/


void try_CAN_msg_filter()
{

  //Read a single message from the CAN read register if it is available. Filter it according to COB-id and internal data and update the Teensy memory associated with that data or set a flag accordingly.
  CAN_message_t msg;// Struct defined in FlexCAN 
  if(Can0.read(msg))//If there was something to read, this will be true and msg will be filled with CAN data from the most recent read buffer value (FlexCAN function)
  {
    if(CAN_FILTER_PRINT){
      Serial.println("TRY_CAN_MSG_FILTER READ OCCURED");
    }
    
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

      case 0x701: case 0x702: case 0x703: case 0x704://If Network Management (NMT) Boot Up message
      
      break;
      
      default:
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
        registers.reg_map.node_statuswords[node_id--] = msg.buf[4]; //The first data byte of the SDO return message is the LSB of the Statusword for the node. For storage in SPI registers
        statuswords[node_id--] = (uint16_t)(msg.buf[5] << 8 | msg.buf[4]); //Store the FULL 16 bit statusword for local Teensy use
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

    break;

    case 0x1001: //Error register object dictionary index
    
      //if(command_specifier == 0x4B){//If the command specifier indicates that the message was a read dictionary object reply of 1 byte
        
        node_id = msg.id & 0x000F; //the last byte of the COB-id is the node id
        registers.reg_map.node_errors[node_id--] = msg.buf[4]; //The first data byte of the SDO return message 
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
    
  }
  
}








