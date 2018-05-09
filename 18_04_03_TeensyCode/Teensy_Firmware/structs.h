#ifndef structs_h
#define structs_h

#include "Adafruit_Sensor.h"
#include "Adafruit_BNO055.h"
#include "imumaths.h"

 struct IMUstructp{
  bool err;          // Indicates a communication error
  imu::Vector<3> accel;  // Stores the 16-bit signed accelerometer sensor output
  imu::Vector<3> gyro;   // Stores the 16-bit signed gyro sensor output
  imu::Vector<3> mag;    // Stores the 16-bit signed magnetometer sensor output
  imu::Quaternion quat;   // Stores the 16-bit signed quaternion output
  imu::Vector<3> eul;    // Stores the 16-bit signed Euler angle output
  imu::Vector<3> lia;    // Stores the 16-bit signed linear acceleration output
  imu::Vector<3> grv;    // Stores the 16-bit signed gravity vector output
};

typedef struct IMUstructp IMUstruct;

#endif /* structs_h */
