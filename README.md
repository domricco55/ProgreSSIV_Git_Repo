This repository follows developement of the Cal Poly Small Scale Intelligent Vehicle (SSIV) by the ProgreSSIV senior project team.

The main elements of the repository are:

1. The ProgreSSIV_Teensy_Firmware arduino sketch 

* Code that gets embedded on the teensy 3.6. 

* The code follows a cooperative multitasking scheme for soft real time behavior. There are four main tasks that run sequentially in the ProgreSSIV_Teensy_Firmeare.ino arduino file. Each takes up only a portion of the processing time in each iteration of the loop. The four tasks are SPI, CAN Motor Controller state machine, Inertial Measurement Unit, and CAN filter. There is also code to handle the Radio Receiver data and servo pwm but these are done purely with interrupts and utilize global variables to share data with the other tasks. All other data is exchanged between tasks using structs defined in shares.h. Each task can alter shared data to affect the behavior of another task but the state of one task SHOULD NOT be able to be directly affected by another task. 

* This code facilitates the SPI communication between Simulink running on the Raspberry Pi and the sensors, servo, and motor controllers (the SPI slave interface) in the ProgreSSIV_SPI_task file. The code gathers data from the Adafruit BNO055 Inertial Measurement Unit sensor via I2C in the ProgreSSIV_IMU_task file. The Maxon Motor controllers are being communicated via the CAN bus (CAN high and CAN low wires) and CAN interface code in the ProgreSSIV_CAN_write_driver, ProgreSSIV_CAN_filter_task, and ProgreSSIV_MC_state_machine cpp files. Radio receiver code and servo pwm actuation is taken care of in the input_handler and output_handler files respectively. 

 Col 1 | Col 2
-------|------
blah   | blah 



1. The RaspberryPi_Python_Firmware file

1. The Simulink_Files file

1. The EPOS_Studio file

1. The CAN_Test_Code file

1. The Documentation file. 
