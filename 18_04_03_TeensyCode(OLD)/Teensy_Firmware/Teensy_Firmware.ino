/**
 * Teensy_Firmware.ino
 * 
 * 
 * Description: This file is the firmware on the TEENSY for the CALPOLY SSIV
 * 
 * Date:                      April 3, 2018
 * Last Edit by:              Paul Rothhammer-Ruiz
 * 
 * Version Description:    
 *                            -This version removes unnecessary sensor values to be sent through SPI (ex. quaternion)
 *                            
 * Errors:                    -None
 * 
 * 
 * TO-DOs:                    
 *                            -
 * 
 * Compiling[Y/N]:            Y
 * 
 * 
 */


#include "uLaren_CAN_Driver.h"
#include "FlexCAN.h"
#include "kinetis_flexcan.h"
#include "input_handler.h"
#include "output_handler.h"
#include "loop.h"
#include "fault_handler.h"
#include "structs.h"
#include "t3spi.h"
//libraries for imu
#include <Wire.h>
#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "imumaths.h"

//new addition to this version
#include "VL53L0X.h"
VL53L0X range_finder_sensor;


/* Set the delay between fresh samples */
#define BNO055_SAMPLERATE_DELAY_MS (100)
Adafruit_BNO055 bno = Adafruit_BNO055();
/*End of IMU changes*/

//Initialize T3SPI class as SPI_SLAVE
T3SPI SPI_SLAVE;

//This sets the amount of bytes sent from the teensy to the raspberry pi. 
//*1st byte is the register address and the second two bytes is the data bytes  
#define dataLength  4

#define NODE_1 1
#define NODE_2 2
#define NODE_3 3
#define NODE_4 4

#define MC_VOLTAGE_THRESHOLD 220

#define SIMULINK 1 // 0 when controlling with remote control/ 1 when controlling with simulink model

/*XXX only turn on remote assist or dead_switch but not both at same time!!!!!*/
#define REMOTE_ASSIST 0    // see functions steer_remote_assist() and throttle_remote_assist()
#define DEAD_SWITCH 0      // when this is on the car only adjusts steer and throttle to simulink commands when trigger on remote is pulled or pushed all the way

/*Register addresses*/
#define EULER_PITCH_READ 78  
#define EULER_ROLL_READ  79
#define EULER_YAW_READ   80

#define ACCL_X_READ      81
#define ACCL_Y_READ      82
#define ACCL_Z_READ      83

#define QUATERNION_W_READ 84
#define QUATERNION_X_READ 85
#define QUATERNION_Y_READ 86
#define QUATERNION_Z_READ 87

#define GYRO_X_READ      88
#define GYRO_Y_READ      89
#define GYRO_Z_READ      90

#define RANGE_FINDER_READ 151

#define THROTTLE_ALL_WRITE 100
#define THROTTLE_RIGHT_FRONT_WRITE 101  
#define THROTTLE_LEFT_FRONT_WRITE  102
#define THROTTLE_RIGHT_REAR_WRITE  103
#define THROTTLE_LEFT_REAR_WRITE   104

#define STEERING_WRITE 121


uint8_t steering_write_array[dataLength] = {STEERING_WRITE,255,255,255};
uint8_t throttle_right_front_array[dataLength] = {THROTTLE_RIGHT_FRONT_WRITE,255,255,255};
uint8_t throttle_left_front_array[dataLength] = {THROTTLE_LEFT_FRONT_WRITE,255,255,255};
uint8_t throttle_right_rear_array[dataLength] = {THROTTLE_RIGHT_REAR_WRITE,255,255,255};
uint8_t throttle_left_rear_array[dataLength] = {THROTTLE_LEFT_REAR_WRITE,255,255,255};
uint8_t throttle_all_array[dataLength] = {THROTTLE_ALL_WRITE,255,255,255};

uint8_t euler_yaw_read_array[dataLength]  = {0,0,0,0};
uint8_t euler_pitch_read_array[dataLength] = {0,0,0,0};        
uint8_t euler_roll_read_array[dataLength]  = {0,0,0,0};

uint8_t accl_x_read_array[dataLength]  = {0,0,0,0};
uint8_t accl_y_read_array[dataLength]  = {0,0,0,0};
uint8_t accl_z_read_array[dataLength]  = {0,0,0,0};

uint8_t gyro_x_read_array[dataLength]  = {0,0,0,0};
uint8_t gyro_y_read_array[dataLength]  = {0,0,0,0};
uint8_t gyro_z_read_array[dataLength]  = {0,0,0,0};

uint8_t quaternion_w_read_array[dataLength]  = {0,0,0,0};
uint8_t quaternion_x_read_array[dataLength]  = {0,0,0,0};
uint8_t quaternion_y_read_array[dataLength]  = {0,0,0,0};
uint8_t quaternion_z_read_array[dataLength]  = {0,0,0,0};

uint8_t range_finder_read_array[dataLength]  = {0,0,0,0};

//main globals
FlexCAN CANbus(1000000);
State next_state;

// throttle input value (ranges from ~-500 to 500)
volatile int16_t THR_in;
//steering input value (ranges from ~-500 to 500)
volatile int16_t ST_in;

/*Code added for SPI Communication*/
//SPI Incoming Data Array
volatile uint8_t data[dataLength] = {};
//SPI Outgoing Data Array
volatile uint8_t default_data_read[dataLength] = {};
uint8_t intitial_array[dataLength] = {255,255,255,255};
uint8_t spi_register = 0;
uint8_t rpi_status = 0;
uint8_t spi_data_low_byte = 0;
uint8_t spi_data_high_byte = 0;
int16_t spi_data = 0;

//Sensor data array that contains pointers to arrays of sensor data
uint8_t *sensor_array[256];

//imu variables
double euler_x;
double euler_y;
double euler_z;
double accl_x;
double accl_y;
double accl_z;
double gyro_x;
double gyro_y;
double gyro_z;
double range;

//status_Data NOT YET IMPLEMENTED
uint8_t status_data; // this data byte is a status update that is sent to the raspberry pi every spi message.
//status_data EXAMPLE: 
/*
Bit:  |     7         |     6      5      |   4     3     1    |     1         0     |
      | battery ok ?  |  autonomous mode  | state machine state|  spi message status |
      | 1= yes,0=no   |  00=remote;01=sim |  ?????             |    ????????         |
      | if no shutdown|  10=adas; 11=?    |   ?????            |   ?????             |
       
*/



int16_t servo_out = 0;
int16_t throttle_out = 0;
int16_t throttle_out_LF = 0;
int16_t throttle_out_RF = 0;
int16_t throttle_out_LR = 0;
int16_t throttle_out_RR = 0;
int16_t steer_angle;

//timing variables
unsigned long start_time_motors;
unsigned long current_time_motors;
unsigned long start_time_servo;
unsigned long current_time_servo;
unsigned long start_time_voltage;
unsigned long current_time_voltage;

//loop variables
int ret = 0;
int error = NO_ERROR;
int voltage = 0;
int data_int = 0;

int emergency = 0;
//unsigned output function
double make_unsigned_output(double data);
//saturate function
int saturate(double value,int min_value, int max_value);
//motor Fucntion
int update_motor_velocity();
//this function adds to the throttle value from the remote to the throttle of each wheel when in simulink
int throttle_remote_assistance(int throttle_value);
//this function adds to the steering value from the remote to the steering value in simulink
int steer_remote_assistance(int steer_value);

//code for safety shut off
int safe = 1;


volatile int print_flag=0; //this flag set in spi interrupt so data pertaining to spi only print out when spi message is received 
volatile int current_register=0; //this is set in interrupt.  The current register is the register address that the last spi message from the PI had.

/*
 * ERROR_CAN_WRITE: a write to can error usually means one controller is offline.
 *        In this scenario we will go to INITIALIZE_CONTROLLERS and try to reboot them
 */ 
 
void setup(void) {
  int i;

  /*new code*/
  Wire.begin();
  range_finder_sensor.init();
  range_finder_sensor.setTimeout(500);
  // Start continuous back-to-back mode (take readings as
  // fast as possible).  To use continuous timed mode
  // instead, provide a desired inter-measurement period in
  // ms (e.g. sensor.startContinuous(100)).
  range_finder_sensor.startContinuous();
  
  

    
  //begin serial port operation
  Serial.begin(115200);
  
  
  /*Start of IMU Changes*/
    Serial.println("Orientation Sensor Raw Data Test"); Serial.println("");
  
    /* Initialise the sensor */
    if(!bno.begin())
    {
      /* There was a problem detecting the BNO055 ... check your connections */
      Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
      while(1);
    }
  
    delay(1000);
  
    /* Display the current temperature */
    int8_t temp = bno.getTemp();
    Serial.print("Current Temperature: ");
    Serial.print(temp);
    Serial.println(" C");
    Serial.println("");
  
    bno.setExtCrystalUse(true);
  
    Serial.println("Calibration status values: 0=uncalibrated, 3=fully calibrated");
    
  /*End of IMU changes*/

  if (SIMULINK)
  {

    /*Code added for SPI communication*/
    //Begin SPI in SLAVE (SCK pin, MOSI pin, MISO pin, CS pin)
    SPI_SLAVE.begin_SLAVE(SCK, MOSI, MISO, CS0); 
    //Set the CTAR0_SLAVE0 (Frame Size, SPI Mode)
    SPI_SLAVE.setCTAR_SLAVE(8, SPI_MODE0);
    //Enable the SPI0 Interrupt
    NVIC_ENABLE_IRQ(IRQ_SPI0);
    /*End SPI Code*/
    
    pinMode(PI_GPIO, OUTPUT);
    delay(10);
    digitalWrite(PI_GPIO, LOW);
  }
  //startup CAN network
  CANbus.begin();
  next_state = INITIALIZE_PERIPHERALS;
  indicatorSet(rgbWHITE);

  /* Populate status array so that there is no segmentation fault later on when an index that hasn't been populated is called*/
  for (i=0;i<256;i++) {
    sensor_array[i] = intitial_array;  
  }
}
  
void loop() {

  
  CAN_message_t msg;


   switch(next_state)
   {

      case(INITIALIZE_PERIPHERALS):
         //initialize other things
         if (PRINT) 
         {
          Serial.println("Initializing Peripherals");
         }
         initPWMin();
         initServo();
         
         next_state = INITIALIZE_CONTROLLERS;
         break;
      case(INITIALIZE_CONTROLLERS):
         if (PRINT)
         {
           Serial.println("Initializing Controllers");
         }
         ret = reset_nodes();
         if (ret > 0)
         {
          error = ret;
         }
         delay(1000);
         
         ret = initialize_CAN();
         if (ret > 0)
         {
          error = ret;
         }
         delay(50);
        
         ret = initialize_MC(NODE_1);
         if (ret > 0)
         {
          error = ret;
         }
 
         process_available_msgs();
         delay(100);
         ret = initialize_MC(NODE_2);
         if (ret > 0)
         {
          error = ret;
         }

        
         process_available_msgs();
         delay(100);
         ret = initialize_MC(NODE_3);
         if (ret > 0)
         {
          error = ret;
         }
         
         process_available_msgs();
         delay(100);
         ret = initialize_MC(NODE_4);
         if (ret > 0)
         {
          error = ret;
         }
 
         if (error == ERROR_CAN_WRITE)
         {
            //reinitialize controllers
            if (PRINT)
            {
              Serial.println("Stopping Nodes.");
            }
            
            delay(500);
  
            stop_remote_node(NODE_1);
  
            stop_remote_node(NODE_2);
  
            stop_remote_node(NODE_3);
            stop_remote_node(NODE_4);
           
            delay(500);
            process_available_msgs();
            if (PRINT)
            {
              Serial.println("Reinitializing Controllers.");
            }
            
            next_state = INITIALIZE_CONTROLLERS;
            error = 0;
         }
         else 
         {
            next_state = WAIT_FOR_ARM;
            indicatorSet(rgbYELLOW);
         }
         break;
      case(WAIT_FOR_ARM):
         if (PRINT)
         {
           Serial.println("Awaiting arming sequence... ");
         }
         
         while (ST_in < 400)
         {
            //do nothing until armed
            if (PRINT)
            {
              Serial.println(ST_in);
            }
            
            delay(500);
         }
         
         if (ST_in >= 400 || 1) //change
         {
            next_state = LINK_COMMUNICATION;
            indicatorSet(rgbRED);
         }
         else
         {
            next_state = WAIT_FOR_ARM;
         }
         
         break;
      case(LINK_COMMUNICATION):
          //arm
          link_node(NODE_1);
          delay(500);
          link_node(NODE_2);
          delay(500);
          link_node(NODE_3);
          delay(500);
          link_node(NODE_4);
          delay(500);
          
          if (SIMULINK)
          {
            next_state = RUNNING_SIMULINK;
            //write simulink pin high (pin 15) (PI_GPIO)
            digitalWrite(PI_GPIO, HIGH);
            indicatorSet(rgbCYAN);
          }
          else{
            next_state = RUNNING_NOMINALLY;
            indicatorSet(rgbGREEN);
          } 
            
           start_time_motors = micros();
           start_time_servo = micros();
           start_time_voltage = millis();
           if (PRINT)
           {
             Serial.println("Running under normal operations.");
           }  
          break;
      case(RUNNING_NOMINALLY):
          //check for messages
          while (CANbus.available())
          {
            if (CANbus.read(msg) != 0)
            {
              //Serial.println("ello matey");
              print_incoming_CAN_message(msg);
            }
          }

          //write to motor controllers
          
          current_time_motors = micros(); 
          if ((current_time_motors - start_time_motors) >= 20000)  //20ms => 50hz
          {
            start_time_motors = micros();
            Serial.print("THR: ");
            Serial.println(THR_in);  
            if (THR_in < 60 && THR_in >= 0) {
              write_velocity_and_enable_MC(NODE_1, 0 * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_2, 0 * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_3, 0 * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_4, 0 * SCALE_FACTOR);
            }
            else {
              write_velocity_and_enable_MC(NODE_1, -THR_in * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_2, THR_in * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_3, -THR_in * SCALE_FACTOR);
              write_velocity_and_enable_MC(NODE_4, THR_in * SCALE_FACTOR);
            }
          }  

          //check voltage level
          current_time_voltage = millis();
          if ((current_time_voltage - start_time_voltage) >= 800)
          {
            voltage = query_voltage_level(NODE_1);
            start_time_voltage = millis();
            
             if (voltage < MC_VOLTAGE_THRESHOLD)
             {
                Serial.println("Voltage to motors is below our threshold. System is shutting down. Charge your battery!");
                //shutdown drivers 
                shutdown_MC(NODE_1);
                shutdown_MC(NODE_2);               
                shutdown_MC(NODE_3);
                shutdown_MC(NODE_4);
                
                //make LED purple
                indicatorSet(rgbPURPLE);
                while(1);
             }
             indicatorSet(rgbGREEN);
          }

        
          // Push Actuator Data---------------------------------------
          // Set steering angle
          current_time_servo = micros();
          if ((current_time_servo - start_time_servo) >= 10000)
          {
            start_time_servo = micros();
            Serial.println();
            Serial.print("ST_IN ");
            Serial.println(ST_in);
            writeServo(ST_in);
          }
          
         break;
      case(RUNNING_SIMULINK):
          //check for CAN messages
          while (CANbus.available())
          {
            if (CANbus.read(msg) != 0)
            {
              //Serial.println("ello matey");
              print_incoming_CAN_message(msg);
            }
          }

          //write to motor controllers if we need to (50Hz)
          current_time_motors = micros(); 
          if ((current_time_motors - start_time_motors) >= 20000)  //20ms => 50hz
          {
            start_time_motors = micros();

            write_velocity_and_enable_MC(NODE_1, -throttle_out_RF * SCALE_FACTOR);
            write_velocity_and_enable_MC(NODE_2, throttle_out_LF * SCALE_FACTOR);
            write_velocity_and_enable_MC(NODE_3, -throttle_out_LR * SCALE_FACTOR);
            write_velocity_and_enable_MC(NODE_4, throttle_out_RR * SCALE_FACTOR);
            Serial.println("I wrote to motors!");
          }   
     
          while (1)  //shouldnt be a while(1) loop.  Because currently it is not going into check battery voltage code block.
          {

            // Dead man's switch.  If throttle is not at full(ish) forward or reverse motors set to zero.
            if (THR_in > 200 || THR_in <-200) {
                safe =1;
            }
            else {
                safe = 0;
            }

            //set variables eaual to spi input (data array is the spi input message from raspberry pi)
            rpi_status = data[0];                // register
            spi_register = data[1];              // status
            spi_data_low_byte = data[2];         // data low byte
            spi_data_high_byte = data[3];        // data high byte
            spi_data = (spi_data_low_byte << 8 | spi_data_high_byte)-500;

            /*
            //IMU gravity - m/s^2 
            imu::Vector<3> gravity = bno.getVector(Adafruit_BNO055::VECTOR_GRAVITY);  
            //IMU linear acceleration - m/s^2 
            imu::Vector<3> lin_accl = bno.getVector(Adafruit_BNO055::VECTOR_LINEARACCEL);             
            //IMU magnetometer - uT
            imu::Vector<3> mag = bno.getVector(Adafruit_BNO055::VECTOR_MAGNETOMETER);  
            */
            //IMU gyroscope - rad/s
            imu::Vector<3> gyro = bno.getVector(Adafruit_BNO055::VECTOR_GYROSCOPE);  
            //IMU euler - degrees
            imu::Vector<3> euler = bno.getVector(Adafruit_BNO055::VECTOR_EULER);  
            //IMU accelration - m/s^2 
            imu::Vector<3> accl = bno.getVector(Adafruit_BNO055::VECTOR_ACCELEROMETER);
            //quaternion
            imu::Quaternion quat = bno.getQuat();

            /*printing spi data and register information the came through from raspberry pi for DEBUGGING purposes*/
            if (print_flag==1 || 1) { //print_flag goes high after each interrupt (each data byte that is received through spi)
                print_flag=0;
            
                Serial.print("*Spi Register: ");
                Serial.println(spi_register); 
                Serial.print("spi_Data: ");
                Serial.println(spi_data);        
               
            }   
            
       
            //if trigger is pulled down or pushed on remote control (when DEAD_SWITCH == 1)           
            if (safe == 1 || DEAD_SWITCH == 1) { //chage DEAD_SWITCH to 1 to have the car only run when trigger on remote is pushed down or pulled.              
              /*should sensor_array be filled with data array instead of having case statement??Possible EDIT?*/  
              switch (spi_register) 
              {                
                //Immediate Brake Stop
                case 255:
                  throttle_out_LF = 0;
                  throttle_out_RF = 0;
                  throttle_out_LR = 0;
                  throttle_out_RR = 0;
                  write_velocity_and_enable_MC(NODE_1, 0 * SCALE_FACTOR);
                  write_velocity_and_enable_MC(NODE_2, 0 * SCALE_FACTOR);
                  write_velocity_and_enable_MC(NODE_3, 0 * SCALE_FACTOR);
                  write_velocity_and_enable_MC(NODE_4, 0 * SCALE_FACTOR);
                  break;             
               //VELOCITY THROTTLE write
               case THROTTLE_LEFT_FRONT_WRITE: //Write motor VELOCITY to left front wheel               
                  throttle_out_LF = ((int16_t)spi_data);
                  throttle_out_LF = throttle_remote_assistance(throttle_out_LF);
                  update_motor_velocity();
                  break; 
               case THROTTLE_RIGHT_FRONT_WRITE: //Write motor VELOCITY to right front wheel
                  throttle_out_RF = ((int16_t)spi_data);
                  throttle_out_RF = throttle_remote_assistance(throttle_out_RF);
                  update_motor_velocity();
                  break;
               case THROTTLE_LEFT_REAR_WRITE: //Write motor VELOCITY to left rear wheel
                  throttle_out_LR = ((int16_t)spi_data);                 
                  throttle_out_LR = throttle_remote_assistance(throttle_out_LR);
                  update_motor_velocity();           
                  break;   
               case THROTTLE_RIGHT_REAR_WRITE: //Write motor VELOCITY to right rear wheel
                  throttle_out_RR = ((int16_t)spi_data);             
                  throttle_out_RR = throttle_remote_assistance(throttle_out_RR);
                  update_motor_velocity();          
                  break;             
               case THROTTLE_ALL_WRITE: 
                  throttle_out_RR = ((int16_t)spi_data);             
                  throttle_out_RR = throttle_remote_assistance(throttle_out_RR); 
                  throttle_out_LF = ((int16_t)spi_data);
                  throttle_out_LF = throttle_remote_assistance(throttle_out_LF);
                  throttle_out_LR = ((int16_t)spi_data);                 
                  throttle_out_LR = throttle_remote_assistance(throttle_out_LR);
                  throttle_out_RF = ((int16_t)spi_data);
                  throttle_out_RF = throttle_remote_assistance(throttle_out_RF);
                  update_motor_velocity(); 
                  break;
               //Steer write   
               case STEERING_WRITE:  
                   steer_angle = ((int16_t)spi_data);
                   //Serial.print("((steer_angle: ");
                   //Serial.println(steer_angle);
                   steer_angle=steer_angle; //steer_remote_assistance(steer_angle);
                   writeServo(steer_angle);
                   Serial.print("steer angle ");
                   Serial.println(steer_angle);
                                
                   break;         
               default: // will go into default when spi_register value does not match any of the cases
             
                  break;
              }
            }
            else {    // trigger not pulled or pushed down on remote controller so just brake to a stop
                throttle_out_LF = 0;
                throttle_out_RF = 0;
                throttle_out_LR = 0;
                throttle_out_RR = 0;
                writeServo(0); 
                update_motor_velocity();
            }

            /*Set status data ****/
            //status_data is a uint8_t number so 0 to 255
            //currently arbitrarily 234
            //NEXT step make a lot of #define CONSTANTS to put in place of the 1s and 0s that actually is relevant data about teensy status
            status_data = ((uint8_t) 1) << 7 | ((uint8_t) 1) << 6 | ((uint8_t) 1) <<5 | ((uint8_t) 0) << 4 | ((uint8_t) 1) << 3 | ((uint8_t) 0) << 2 | ((uint8_t) 1) <<1 | ((uint8_t) 0) << 0; 

             
            /*
            * Each element in spi array is 1 byte.  Therefore 4 bytes per packet.  The array shows up on Simulink end as one message packet.  
            * structure if spi arrays:
            * spi_array[0] -> register address of that data
            * spi_array[1] -> low byte of data (only relevant for READS)
            * spi_array[2] -> high byt of data (only relevant for READS)
            * spi_array[3] -> status of teensy
            */

            //default output to spi (NOT BEING USED), maybe use for when a register is called that doens't map to any known register.
            default_data_read[0] = 255;
            default_data_read[1] = 255; 
            default_data_read[2] = 255;
            default_data_read[3] = status_data;

            //read data          
            euler_x = euler.x(); //i2C call to IMU BNO to return euler_x
            euler_x = make_unsigned_output(euler_x);
            //euler_x = saturate(euler_x,0,65535);                      
            euler_yaw_read_array[0] = (uint8_t) EULER_YAW_READ;
            euler_yaw_read_array[1] = (uint8_t) (((uint16_t) ((int)euler_x)) >> 8);
            euler_yaw_read_array[2] = (uint8_t) (((uint16_t) ((int)euler_x)) & 0xFF); //Set to 
            euler_yaw_read_array[3] = (uint8_t) status_data;
            sensor_array[EULER_YAW_READ] = euler_yaw_read_array;
            
            accl_x = accl.x();
            accl_x = make_unsigned_output(accl_x);    
            accl_x = saturate(accl_x,0,65535);                             
            accl_x_read_array[0] = (uint8_t) ACCL_X_READ;   // reg addr for confirmation 
            accl_x_read_array[1] = (uint8_t) (((uint16_t) ((int)accl_x)) >> 8); // set to acc data MSB
            accl_x_read_array[2] = (uint8_t) (((uint16_t) ((int)accl_x)) & 0xFF); //Set to accelerometer data LSB        
            accl_x_read_array[3] = (uint8_t) status_data;  // teensy status byte      
            sensor_array[ACCL_X_READ] = accl_x_read_array;

            accl_y = accl.y();
            accl_y = make_unsigned_output(accl_y);
            accl_y = saturate(accl_y,0,65535);
            accl_y_read_array[0] = (uint8_t) ACCL_Y_READ;             
            accl_y_read_array[1] = (uint8_t) (((uint16_t) ((int)accl_y)) >> 8); // set to acc data MSB
            accl_y_read_array[2] = (uint8_t) (((uint16_t) ((int)accl_y)) & 0xFF); //Set to accelerometer data LSB
            accl_y_read_array[3] = (uint8_t) status_data;  // teensy status byte      
            sensor_array[ACCL_Y_READ] = accl_y_read_array;           

            accl_z = accl.z();
            accl_z = make_unsigned_output(accl_z);
            accl_z = saturate(accl_z,0,65535);
            accl_z_read_array[0] = (uint8_t) ACCL_Z_READ;
            accl_z_read_array[1] = (uint8_t) (((uint16_t) ((int)accl_z)) >> 8);
            accl_z_read_array[2] = (uint8_t) (((uint16_t) ((int)accl_z)) & 0xFF); //Set to accelerometer data
            accl_z_read_array[3] = (uint8_t) status_data;
            sensor_array[ACCL_Z_READ] = accl_z_read_array;
            
            gyro_x = gyro.x();
            gyro_x = make_unsigned_output(gyro_x);
            gyro_x = saturate(gyro_x,0,65535);
            gyro_x_read_array[0] = (uint8_t) GYRO_X_READ;
            gyro_x_read_array[1] = (uint8_t) (((uint16_t) ((int)gyro_x)) >> 8);
            gyro_x_read_array[2] = (uint8_t) (((uint16_t) ((int)gyro_x)) & 0xFF); //Set to accelerometer data
            gyro_x_read_array[3] = (uint8_t) status_data;
            sensor_array[GYRO_X_READ] = gyro_x_read_array;
            
            gyro_y = gyro.y();
            gyro_y = make_unsigned_output(gyro_y);
            gyro_y = saturate(gyro_y,0,65535);
            gyro_y_read_array[0] = (uint8_t) GYRO_Y_READ;
            gyro_y_read_array[1] = (uint8_t) (((uint16_t) ((int)gyro_y)) >> 8);
            gyro_y_read_array[2] = (uint8_t) (((uint16_t) ((int)gyro_y)) & 0xFF); //Set to accelerometer data
            gyro_y_read_array[3] = (uint8_t) status_data;
            sensor_array[GYRO_Y_READ] = gyro_y_read_array;

            gyro_z = gyro.z();
            gyro_z = make_unsigned_output(gyro_z);
            gyro_z = saturate(gyro_z,0,65535);
            gyro_z_read_array[0] = (uint8_t) GYRO_Z_READ;
            gyro_z_read_array[1] = (uint8_t) (((uint16_t) ((int)gyro_z)) >> 8);
            gyro_z_read_array[2] = (uint8_t) (((uint16_t) ((int)gyro_z)) & 0xFF); //Set to accelerometer data
            gyro_z_read_array[3] = (uint8_t) status_data;
            sensor_array[GYRO_Z_READ] = gyro_z_read_array;                                    

            range = range_finder_sensor.readRangeContinuousMillimeters();
          if (range_finder_sensor.timeoutOccurred()) { Serial.print(" TIMEOUT"); }
          //Serial.println();
          //Serial.print("distance b4: ");
          //Serial.println(range);
            range = range+500;//make_unsigned_output(range);
            range = saturate(range,0,65535);
          //Serial.print("distance after: ");
          //Serial.println(range);            
          //Serial.println();  
            range_finder_read_array[0] = (uint8_t) RANGE_FINDER_READ;
            range_finder_read_array[1] = (uint8_t) (((uint16_t) ((int)range)) >> 8);
            range_finder_read_array[2] = (uint8_t) (((uint16_t) ((int)range)) & 0xFF); 
            range_finder_read_array[3] = (uint8_t) status_data;
            sensor_array[RANGE_FINDER_READ] = range_finder_read_array;  
           

            //write
            steering_write_array[0] = (uint8_t) STEERING_WRITE;
            steering_write_array[1] = (uint8_t) 255;
            steering_write_array[2] = (uint8_t) 255;
            steering_write_array[3] = (uint8_t) status_data;
            sensor_array[STEERING_WRITE] = steering_write_array;
            
            throttle_right_front_array[0] = (uint8_t) THROTTLE_RIGHT_FRONT_WRITE;
            throttle_right_front_array[1] = (uint8_t) 255;
            throttle_right_front_array[2] = (uint8_t) 255;
            throttle_right_front_array[3] = (uint8_t) status_data;
            sensor_array[THROTTLE_RIGHT_FRONT_WRITE] = throttle_right_front_array;            
            
            throttle_left_front_array[0] = (uint8_t) THROTTLE_LEFT_FRONT_WRITE;
            throttle_left_front_array[1] = (uint8_t) 255;
            throttle_left_front_array[2] = (uint8_t) 255;
            throttle_left_front_array[3] = (uint8_t) status_data;
            sensor_array[THROTTLE_LEFT_FRONT_WRITE] = throttle_left_front_array;
            
            throttle_right_rear_array[0] = (uint8_t) THROTTLE_RIGHT_REAR_WRITE;
            throttle_right_rear_array[1] = (uint8_t) 255;
            throttle_right_rear_array[2] = (uint8_t) 255;
            throttle_right_rear_array[3] = (uint8_t) status_data;
            sensor_array[THROTTLE_RIGHT_REAR_WRITE] = throttle_right_rear_array;
            
            throttle_left_rear_array[0] = (uint8_t) THROTTLE_LEFT_REAR_WRITE;
            throttle_left_rear_array[1] = (uint8_t) 255;
            throttle_left_rear_array[2] = (uint8_t) 255;
            throttle_left_rear_array[3] = (uint8_t) status_data;
            sensor_array[THROTTLE_LEFT_REAR_WRITE] = throttle_left_rear_array;

            throttle_all_array[0] = (uint8_t) THROTTLE_ALL_WRITE;
            throttle_all_array[1] = (uint8_t) 255;
            throttle_all_array[2] = (uint8_t) 255;
            throttle_all_array[3] = (uint8_t) status_data;
            sensor_array[THROTTLE_ALL_WRITE] = throttle_all_array;
          

          
            
           
          }
          /*End of while loop*/
          

        /*CODE DOES NOT REACH PAST THIS POINT BECAUSE OF WHILE(1) LOOP*/
        
          //check voltage level (1Hz)
          current_time_voltage = millis();
          if ((current_time_voltage - start_time_voltage) >= 1000)
          {
            voltage = query_voltage_level(NODE_1);
            start_time_voltage = millis();
            
             if (voltage < MC_VOLTAGE_THRESHOLD)
             {
                Serial.println("Voltage to motors is below our threshold. System is shutting down. Charge your battery!");
                //shutdown drivers 
                shutdown_MC(NODE_1);
                shutdown_MC(NODE_2);
                shutdown_MC(NODE_3);
                shutdown_MC(NODE_4);
                
                //make LED purple
                indicatorSet(rgbPURPLE);
             }
             indicatorSet(rgbCYAN);
          }
        
          // Push Actuator Data---------------------------------------
          // Set steering angle (100Hz)
          current_time_servo = micros();
          if ((current_time_servo - start_time_servo) >= 10000)
          {
            start_time_servo = micros();
            writeServo(servo_out);
          }
          
         break;
      case(INDICATE_AND_LOG_ERROR):
         if (PRINT)
         {
           Serial.println("Indicating and logging error.");
         }
         
         next_state = WAIT_FOR_CLEAR;
         break;
      case(WAIT_FOR_CLEAR):  
         delay(1000);
         next_state = WAIT_FOR_ARM;
         break;
      default:
         if (PRINT)
         {
          //Serial.println("In default case. Should not be here. Ever.");
          //Serial.print("Current state is: ");
          //Serial.println(next_state);
         }
         
         exit(0);
         break;  
   }

}

//Interrupt Service Routine to handle incoming SPI Data
void spi0_isr(void) { //
  print_flag=1;
  current_register = data[1];
  SPI_SLAVE.rxtx8(data, sensor_array[current_register], dataLength);
}


//If REMOTE_ASSIST constant is set to 1, the remote value is added to simulink value
int steer_remote_assistance(int steer_value) {
  int value;
  value = (REMOTE_ASSIST*ST_in) +steer_value;
  if (value > 500) {
    value = 500;
  }
  else if (value< -500) {
    value = -500;
  }
  return value;
}

//If REMOTE_ASSIST constant is set to 1, the remote value is added to simulink value
int throttle_remote_assistance(int throttle_value) {
  int value;
  value = (REMOTE_ASSIST*THR_in)+throttle_value;
  if (value >500) {
    value =500;
  }
  else if (value<-500) {
    value = -500;
  }
  return value;
}

/*this function makes the data value have double precision and makes it unsigned.  This operation is undone in the simulink model FOR SIMULINK DATA TYPE COMPATIBILITY*/
double make_unsigned_output(double data) {
  return 100*(data+500);
}

/*this function will saturate the input between the two rails max_value and min_value*/
int saturate(double value,int min_value, int max_value) {
  if (value>max_value) { 
    return max_value;    
  }
  else if (value<min_value) {
    return min_value;
  }
  
  return value;
 
}

/*This function calls the write motor function so that the latest throttle values are written to the motors*/
int update_motor_velocity() {

   write_velocity_and_enable_MC(NODE_1, -throttle_out_RF * SCALE_FACTOR);
   write_velocity_and_enable_MC(NODE_2, throttle_out_LF * SCALE_FACTOR);
   write_velocity_and_enable_MC(NODE_3, -throttle_out_LR * SCALE_FACTOR);
   write_velocity_and_enable_MC(NODE_4, throttle_out_RR * SCALE_FACTOR);

  return 0;  
}

