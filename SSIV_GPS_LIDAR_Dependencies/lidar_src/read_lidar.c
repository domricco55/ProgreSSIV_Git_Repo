#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "read_lidar.h" 

//#define DATA_SIZE 10

        
// void read_lidar_setup()//uint8_T pin, boolean_T mode)
// { 
//    // Perform one-time wiringPi initialization
//    //if (!initialized) { 
//    //   wiringPiSetupGpio(); 
//    //   initialized = 1;
//    //} 
// 
// 
//    // mode = 0: Input 
//    // mode = 1: Output
//    //if (mode) { 
//    //   pinMode(pin, OUTPUT); 
//    //} 
//    //else 
//    //{ 
//    //   pinMode(pin, INPUT); 
//    //}   
//  
// } 

// Write a logic value to pin 
//void writeDigitalPin(uint8_T pin, boolean_T val) 
//{ 
//   digitalWrite(pin, val); 
//}

// Read a logic value from pin 
void read_lidar_data(double data[DATA_SIZE]) {
   FILE *fp;
   int chars_per_line = 60;  // should exceed expected num of chars per line
   char str[60]; //[chars_per_line]; 
   char *ptr;
   int count = 0;

   fp = fopen("/home/pi/sensors/lidar/lidar_data","r");

   if (fp == NULL) { 
      //for (count = 0; count < DATA_SIZE; count++) {
      for (count = 0; count < DATA_SIZE; count++) {
         data[count] = -1; 
      }
   }
   else {
       //while (count < DATA_SIZE && fgets(str,chars_per_line,fp) != NULL) {
       while (count < DATA_SIZE && fgets(str,chars_per_line,fp) != NULL) {
          data[count] = (double) strtol(str,&ptr,10);
          count++;  
       }
       fclose(fp); 
   }
  
}

// boolean_T readDigitalPin(uint8_T pin) 
// { 
//     
//    return ((boolean_T)digitalRead(pin)); 
// }