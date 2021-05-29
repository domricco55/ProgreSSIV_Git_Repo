This repository follows developement of the Cal Poly Small Scale Intelligent Vehicle (SSIV) by the ProgreSSIV senior project team.

https://issuu.com/calpolyceng/docs/me_newsletter-summer

The main elements of the repository are:

1. The ProgreSSIV_Teensy_Firmware arduino sketch 

   * Code that gets embedded on the Teensy 3.6. 

   * The code follows a cooperative multitasking scheme for soft real time behavior. There are four main tasks that run sequentially in the ProgreSSIV_Teensy_Firmeare.ino arduino file. Each takes up only a portion of the processing time in each iteration of the loop. The four tasks are SPI, CAN Motor Controller state machine, Inertial Measurement Unit, and CAN filter. There is also code to handle the Radio Receiver data and servo pwm but these are done purely with interrupts and utilize global variables to share data with the other tasks. All other data is exchanged between tasks using structs defined in shares.h. Each task can alter shared data to affect the behavior of another task but the state of one task should not be able to be directly affected by another task. 

   * This code facilitates the SPI communication between Simulink running on the Raspberry Pi and the sensors, servo, and motor controllers (the SPI slave interface) in the ProgreSSIV_SPI_task file. The code gathers data from the Adafruit BNO055 Inertial Measurement Unit sensor via I2C in the ProgreSSIV_IMU_task file. The Maxon Motor controllers are being communicated to via the CAN bus and CAN interface code in the ProgreSSIV_CAN_write_driver, ProgreSSIV_CAN_filter_task, and ProgreSSIV_MC_state_machine cpp files. Radio receiver code and servo pwm actuation is taken care of in the input_handler and output_handler files respectively. 


2. The RaspberryPi_Python_Firmware file

	*Test scripts utilized in early developement of the SPI interface between the Raspberry Pi and the Teensy. Was helpful in developing the SPI slave interface on the Teensy earlier in the project timeline. This is not utilized by the system in it's current state - the SPI Master interface running on the RPi is facilitated by the Simulink developement environment. 


3. The Simulink_Files file

| Folder        | Description   |
| ------------- | ------------- |
| Adaptive Cruise Control Dominic Riccoboni  |  Files pertaining to the simulation and implementation of an adaptive cruise controller for the SSIV.  |
| Testing  | Under "Blank Control System Developement Files" are the "black box" simulink models - these allow the user to route real signals from sensors and actuators to construct their control system. Under "Particular Test Cases" are some implementations of the developement environment produced by the ProgreSSIV senior project team. |

4. The EPOS_Studio file

	* Configuration files for the MAXON EPOS Studio software. During developement of the CAN interface to the SSIV's motor controllers, intermediate steps required configuration via EPOS Studio. Later on in the project, however, all configuration is done via the teensy 3.6 firmware. 

5. The CAN_Test_Code file

	*Code utilized in developement of the CAN interface on the Teensy. Used to configure the Maxon motor controllers, interface with their onboard state machines, configure messages correctly, and determine which types of messages (Network Management, Service Data Objects, Process Data Objects, etc) need to be sent and when.

6. The Documentation file. 

	* Contains various relevent documents that were utilized in the design and developement of the SSIV. Contains the ProgreSSIV finalized senior project document, helpfull CAN documentation, and relevant hardware/software manuals. 