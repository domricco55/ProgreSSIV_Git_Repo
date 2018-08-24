/* SPI slave interface for communication with Raspberry Pi running embedded Simulink files. Designed by Dominic Riccoboni 
of the ProgreSSIV senior project team - Cal Poly San Luis Obispo  */

/*********************************/

#include "ProgreSSIV_SPI_task.h"

/*General Debugging*/
template<class T> inline Print &operator <<(Print &obj, T arg) {  //"Adding streaming (insertion-style) Output" from playground.arduino.cc
  //Allows Serial << "This is an insertion-style message" type operation
  obj.print(arg);
  return obj;
}


SPI_task::SPI_task( SPI_actuations_t *SPI_actuations, SPI_commands_t *SPI_commands, SPI_sensor_data_t *SPI_sensor_data, node_info_t *node_info, radio_struct_t *radio_struct, flags_struct_t *flags_struct):

    SPI_actuations (SPI_actuations),
    SPI_commands (SPI_commands),
    SPI_sensor_data(SPI_sensor_data),
    node_info(node_info),
    radio_struct(radio_struct),
    flags_struct(flags_struct) //Initializer list 
  {

  /* Initialize other member attributes */;
  registers = new reg_union_t(); //initialize the SPI registers on the heap
  reg_write_buf = new reg_union_t(); //initialize the SPI write register buffer on the heap  

//  registers -> reg_map.init_motor_controllers = 1;
//  registers -> reg_map.dead_switch = 1;
  
  start_time_SPI_task = micros();

  //Configure the SPI memory map and pins
  spi_slave_init();
  
  if (SPI_GENERAL_PRINT) {
    //Print the registers at initialization
    spi_registers_print();
  }
}

void SPI_task::handle_registers(){

  unsigned long current_time_SPI_task = micros();
  if ((current_time_SPI_task - start_time_SPI_task) >= 2000)  //2000 microseconds => 500Hz. This task will run at this frequency
  {   
    /*Disable interrupts while SPI task is interacting with the registers -> prevents spi0_isr from reading or writing corrupt data*/
    noInterrupts();
    
    /* Load the sensor data struct values into the SPI read registers*/
    
    //Euler angles
    registers -> reg_map.euler_heading = SPI_sensor_data -> euler_heading;
    registers -> reg_map.euler_roll = SPI_sensor_data -> euler_roll;
    registers -> reg_map.euler_pitch = SPI_sensor_data -> euler_pitch;
    
    //Accelerations
    registers -> reg_map.accl_x = SPI_sensor_data -> accl_x;
    registers -> reg_map.accl_y = SPI_sensor_data -> accl_y;
    registers -> reg_map.accl_z = SPI_sensor_data -> accl_z;
  
    //Gyroscope data
    registers -> reg_map.gyro_x = SPI_sensor_data -> gyro_x;
    registers -> reg_map.gyro_y = SPI_sensor_data -> gyro_y;
    registers -> reg_map.gyro_z = SPI_sensor_data -> gyro_z;
  
    //Steering and throttle inputs from radio
    registers -> reg_map.radio_steering = radio_struct -> ST_in; 
    registers -> reg_map.radio_throttle = radio_struct -> THR_in;
  
    //Node motor velocities in rpm
    registers -> reg_map.node_rpms[0] = SPI_sensor_data -> node_rpms[0];
    registers -> reg_map.node_rpms[1] = SPI_sensor_data -> node_rpms[1];
    registers -> reg_map.node_rpms[2] = SPI_sensor_data -> node_rpms[2];
    registers -> reg_map.node_rpms[3] = SPI_sensor_data -> node_rpms[3];

    //Low byte of each nodes statusword
    registers -> reg_map.node_statuswords[0] = (uint8_t)((node_info -> node_statuswords[0] & 0x00FF));
    registers -> reg_map.node_statuswords[1] = (uint8_t)((node_info -> node_statuswords[1] & 0x00FF));
    registers -> reg_map.node_statuswords[2] = (uint8_t)((node_info -> node_statuswords[2] & 0x00FF));
    registers -> reg_map.node_statuswords[3] = (uint8_t)((node_info -> node_statuswords[3] & 0x00FF));
    
    /* Offload the SPI write registers into the actuation and command structs*/

    //Command registers     
    SPI_commands -> init_motor_controllers = registers -> reg_map.init_motor_controllers;

    SPI_commands -> dead_switch = registers -> reg_map.dead_switch;

    
    if (registers -> reg_map.reset_imu && flags_struct -> reset_imu_flag){ //If the IMU task has already reset the BNO, it will signal SPI task to clear the reset_imu regiser -> prevents IMU from being continuously reset

      registers -> reg_map.reset_imu = 0;
      flags_struct -> reset_imu_flag = false;
      
    }

    else{
      
      SPI_commands -> reset_imu = registers -> reg_map.reset_imu;
      
    }
        
    //Torques to the Maxon Motor Controller nodes (in units of max continuous torque/1000)
    SPI_actuations -> node_torques[0] = registers -> reg_map.node_torques[0];
    SPI_actuations -> node_torques[1] = registers -> reg_map.node_torques[1];
    SPI_actuations -> node_torques[2] = registers -> reg_map.node_torques[2];
    SPI_actuations -> node_torques[3] = registers -> reg_map.node_torques[3];
  
    //Servo actuation value
    SPI_actuations -> servo_out = registers -> reg_map.servo_out;
    
    interrupts();
    start_time_SPI_task = current_time_SPI_task;

  }
  return;
}

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*SERIAL PERIPHERAL INTERFACE (SPI) INTERRUPT SERVICE ROUTINES*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*
  Teensy SPI Communication Protocol Description:

    spi0_isr handles the incoming bytes - or each frame - of an SPI message while spi_transfer_complete_isr prepares the code for recieving a new spi message
    once the current one is complete.

    An SPI message in this code consists of several one byte frames. The Master can send as many frames per message as it wants and there are two types of messages it can
    initiate with the Slave, a read message and a write message. These are mutually exclusive and which one is occurring is determined by the value of the MSB of the first
    byte recieved in a message, the Read/Write bit. The master sets this bit to 1 for reads and 0 for writes. This byte also contains in the remaining 7 bits the register
    address (a value between 0 an 127). This value indexes a register in the registers union that is to be read from or written to with SPI data. For example:

         0b10000001 -  This as the first frame of a message indicates that a read message is to follow and it should start at index 1 of the registers, i.e. registers -> bytes[1].
                       This index currently points to the memory location of the "begin data collection" command flag, i.e. registers -> reg_map.init_motor_controllers.

    The next frame the master sends will fill this memory location with data. Any subsequent frames will fill further registers with data, i.e. registers -> bytes[2], registers -> bytes[3]
    and so on. These may correspond to different commands, sensor readings, or actuation signals. In this iteration of the code, there is no protection agains writing to a read register
    but this is a recommended feature. Making some of the registers read only can prevent errors.

    Below is an outline of both a read message and a write message.
*/
/*
  If the read bit is high, the structure of the incoming message will behave like this:

    first incoming frame -> Teensy recieves register address of data_0 (Just prior to Interrupt 1)
    second incoming frame -> Teensy recieves junk (Just prior to Interrupt 2)
    third incoming frame -> Teensy recieves junk (Just prior to Interrupt 3)
    fourth incoming frame -> Teensy recieves junk (Just prior to Interrupt 4)
    fifth incoming frame -> Teensy recieves junk (Just prior to Interrupt 5) --> After the last spi0_isr interrupt (5), and immediately after the CS0 pin is brought high by MASTER, the Teensy
                                                                                   will enter the spi_transfer_complete_isr interrupt. There it will load the SPI0_PUSHR_SLAVE push register with the Teensy
                                                                                   status byte to be sent out in the next message (status byte handler code not yet implemented)
*/
/*
  If the read bit is set high, the structure of the outgoing message will look like this (there is a wasted byte due to the double buffering of the spi hardware registers):

    from registers -> bytes[address] -> Teensy sends junk (Just prior to Interrupt 1)
    from registers -> bytes[address+1] -> Teensy sends the Teensy_Status byte (Just prior to Interrupt 2)
    from registers -> bytes[address+2] -> Teensy sends requested data 0 (Just prior to Interrupt 3)
    from registers -> bytes[address+3] -> Teensy sends requested data 1 (Just prior to Interrupt 4)
    from registers -> bytes[address+4] -> Teensy sends requested data 2 (Just prior to Interrupt 5)

  For more details on this process, including a graphical representation of this communnication protocol, please refer to the ProgreSSIV firmware documentation.

*/

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Interrupt Service Routine to run the slave data transfer function call. Responds to the Master's request for a message*/
void SPI_task::spi0_callback(void) {
  volatile uint8_t SPI0_POPR_buf = SPI0_POPR; //Use SPI0_POPR to read the R1 FIFO buffer value. This is the value that was just recieved in the spi shift register from Master.

  //If this is a new message, also decode the R/W bit and grab the address of the register to be accesses. These are both done with bit masks on the first byte of a message.
  if (first_interrupt_flag) {
    
    first_interrupt_flag = false;
    isrStartTime = micros();
    messageStartTime = micros();
    
    if (SPI_DEBUG_PRINT) {
      Serial.println();
      Serial.print("--------");
      Serial.print(message_cnt);
      Serial.println("---------");
    }

    spi_address_buf = SPI0_POPR_buf & ADDRESS_MASK; //ANDs the shift register buffer value and the address mask (extract the 7 bit address from the first byte of the message)

    spi_rw_bit = SPI0_POPR_buf & RW_MASK; //ANDs the shift register buffer value and the read/write bit mask (extract the MSB that tells whether this is a read or write message)

    if (SPI_DEBUG_PRINT) {
      Serial.println("State 1:");
      Serial.print("\tAddr: ");
      Serial.println(spi_address_buf);
      Serial.print("\tReg: ");
      Serial.println(registers -> bytes[spi_address_buf]);
      spi_debug();
    }

    if (spi_rw_bit) { //if the read/write bit is 1, it is a read message and spi_rw_buf will be true
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 2:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers -> bytes[spi_address_buf]);
      }

      SPI0_PUSHR_SLAVE = registers -> bytes[spi_address_buf];//Place the read message byte into the push register to be immediately placed in the T1 FIFO register. By the next 
                                                              //interrupt this value will have been placed in the shift register and by the one after that, it will have been shifted
                                                              //out to the Master device. The message from slave to master lags by two frames.

      spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register

    }

    else{ //The message is a write message, load the register values into the register write buffer

      reg_write_buf = registers;
      
    }
  }

  //NOW NOT ON THE FIRST INTERRUPT ANYMORE. This is the code that will run for all subsequent interrupts of a single spi message.
  else {

    if (spi_rw_bit) { //Message is a READ message
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 3:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(registers -> bytes[spi_address_buf]);
        spi_debug();
      }

      SPI0_PUSHR_SLAVE = registers -> bytes[spi_address_buf]; //Place the read message byte into the push register to be immediately placed in the T1 FIFO register. By the next 
                                                               //interrupt this value will have been placed in the shift register and by the one after that, it will have been shifted
                                                               //out to the Master device. The message from slave to master lags by two frames.

    }
    else {//Message is a WRITE message

      reg_write_buf -> bytes[spi_address_buf] = SPI0_POPR_buf;
      
      if (SPI_DEBUG_PRINT) {
        Serial.println("State 4:");
        Serial.print("\tAddr: ");
        Serial.println(spi_address_buf);
        Serial.print("\tReg: ");
        Serial.println(reg_write_buf -> bytes[spi_address_buf]);
        spi_debug();
      }
    }
    
    spi_address_buf++; //Increment the address so the next byte sent will be the next byte in the spi register
    
  }
  
  isrEndTime = micros();
  if (SPI_DEBUG_PRINT) {
    Serial << "\tInterrupt Time: " << (isrEndTime - isrStartTime) << " Microseconds";
    Serial.println();
    Serial.println();
  }


  SPI0_SR |= SPI_SR_RFDF; //Setting the RFDF or "Recieve FIFO Drain Flag" bit in the SPI0_SR register low (this is cleared by writing a 1 to it) to let the SPI0 module know that all entries have
                          //been removed from the RXFIFO register. Not sure exactly why this needs to be done or if it is absolutely necessary. 

}

/* End spi0_isr */

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/* Used to print some memory map information for debugging purposes. This was used to debug the behavior of the TX FIFO buffer and better understand how it is working. */
void SPI_task::spi_debug(void) {
  Serial.print("\tCTR: ");
  Serial.println((SPI0_SR & (0b1111 << 12)) >> 12); // CTR tells the number of entries in the TX FIFO register
  Serial.print("\tPTR: ");
  Serial.println((SPI0_SR & (0b1111 << 8)) >> 8); //Grab the TX FIFO pointer value that tells which TX FIFO entry is to be transmitted during the next transfer
  Serial.print("\tTX0: ");
  //These are glimpses into data that is to be shifted out. What is in the double buffer to be sent into the shift registers
  Serial.println(SPI0_TXFR0);
  Serial.print("\tTX1: ");
  Serial.println(SPI0_TXFR1);
  Serial.print("\tTX2: ");
  Serial.println(SPI0_TXFR2);
  Serial.print("\tTX3: ");
  Serial.println(SPI0_TXFR3);
}


/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

/*Interrupt service routine for the rising edge of the chip enable pin. This will occur at the end of every spi message. It resets flags, clears the microcontoller TX FIFO counter
  (by setting a bit in the SPI0_MCR register high) and loads the push register buffer with the Teensy status byte.   */
void SPI_task::spi_transfer_complete_isr(void) {

  first_interrupt_flag = true;//Raises the new message flag so spi0_isr knows to take the initial interrupt service routine actions of copying the register buffer, extracting the address 
                              //and extracting the R/W bits

  if (SPI_DEBUG_PRINT) {
    Serial.println("State 4a:");
    Serial.print("\tAddr: ");
    Serial.println(spi_address_buf);
    Serial.print("\tReg: ");
    Serial.println(registers -> bytes[spi_address_buf]);
    spi_debug();
  }

  SPI0_MCR |= (1 << 11);  //Clear the TX FIFO counter so that the Teensy Status Byte gets placed in the first location in the TX FIFO buffer. During the last interrupt, data was
                          //placed in TX FIFO to be placed in the shift register next. Since this data was not transfered into the shift register, the counter currently points to the 
                          //next location in TX FIFO. If we did not clear this counter, the Teensy Status Byte would be placed "in line behind" old junk data. This also helps get around 
                          //double buffering behavior of the SPI hardware by dissallowing TXFIFO from acting like a multiple frame buffer. 

  SPI0_PUSHR_SLAVE = Teensy_Status_Byte; //This loads the push register with the status byte. Currently status byte code is not implemented but perhaps it can be 8 bits that let the Master
  //know which sensors are currently on. There could be a task that sets the bits according to which peripheral-on flags are high or low.

  if(!spi_rw_bit){ //If the message was a write, offload the write values from the registers buffer. 
    registers -> reg_map.node_torques[0] = reg_write_buf -> reg_map.node_torques[0];
    registers -> reg_map.node_torques[1] = reg_write_buf -> reg_map.node_torques[1];
    registers -> reg_map.node_torques[0] = reg_write_buf -> reg_map.node_torques[2];
    registers -> reg_map.node_torques[3] = reg_write_buf -> reg_map.node_torques[3];
    registers -> reg_map.servo_out = reg_write_buf -> reg_map.servo_out;
    
  }

  message_cnt++; //For SPI Debugging Purposes. If SPI_DEBUG_PRINT is true, then the packet count will be displayed at the beginning of each spi message/packet

  /* Timing Calculations */
  message_delta_t = micros() - messageStartTime; //Calculate the time the spi message took to occur from start to finish. Can be used to help diagnose performance/frequency issues

  if (SPI_DEBUG_PRINT) {
    Serial.print("Message Time: ");
    Serial.println(message_delta_t);
  }
  return;
}

/* End spi_transfer_complete_isr */

/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*FUNCTIONS*/
/*----------------------------------------------------------------------------------------------------------------------------------------------------------------------*/

void SPI_task::spi_slave_init(void) {

  /*Configure SPI Memory Map*/
  SIM_SCGC6 |= SIM_SCGC6_SPI0;    // enable clock to SPI. THIS WAS MISSING PRIOR AND WOULD CAUSE CODE TO GET STUCK IN THIS FUNCTION
  delay(1000);

  SPI0_MCR |= SPI_MCR_HALT | SPI_MCR_MDIS; //While configuring memory map, halt spi functions

  SPI0_MCR = 0x00000000; //This clears the entire SPI0_MCR register. This will clear the MSTR bit (master mode is a 1 and slave mode is a 0)

  SPI0_CTAR0_SLAVE = 0; //Clears entire CTAR0 slave register

  SPI0_CTAR0 |= SPI_CTAR_FMSZ(7); //THIS SETS THE BITS FOR FRAME SIZE (The value in this register plus one is the frame size. Want a single byte frame size.
  //Master and slave in our system agree on this)

  SPI0_CTAR0 = SPI0_CTAR0 & ~(SPI_CTAR_CPOL | SPI_CTAR_CPHA) | SPI_MODE0 << 25; //This line sets the clock phase and clock polarity bits. Clock is inactive low (polarity)
  //and the data is captured on the leading edge of SCK (phase). Configures CTAR0 Slave register

  SPI0_RSER = 0x00020000; //Request Select and Enable Register. Setting the RFDF_RE FIFO DRAIN REQUEST ENABLE Pin that allows interrupts or DMA to occur. The default method of draining
  //the SPI hardware data register is interrupts. When a full 8 bits (the frame size) has been recieved an interrupt will be triggered (SPI0_ISR) and the data will be decoded.

  //Enable the SCK, MISO, MOSI, and CS0 Pins (connections to the master device)
  CORE_PIN13_CONFIG = PORT_PCR_MUX(2); //Serial Clock (SCK) pin
  CORE_PIN11_CONFIG = PORT_PCR_DSE | PORT_PCR_MUX(2); //Master Output Slave Input (MOSI) pin
  CORE_PIN12_CONFIG = PORT_PCR_MUX(2); //Master Input Slave Output (MISO) pin
  CORE_PIN10_CONFIG = PORT_PCR_MUX(2); //Chip Select 0 (CS0) or Enable  pin

  SPI0_MCR &= ~SPI_MCR_HALT & ~SPI_MCR_MDIS; //Resume spi functions

  if (SPI_GENERAL_PRINT) {
    Serial.println("Made it to end of spi_slave_init");
    delay(500);
    Serial << "SPI0_MCR: ";
    Serial.println(SPI0_MCR, BIN);
  }
}

void SPI_task::spi_registers_print(void) { //This prints the name and address of each of the items in the register map along with the data stored in each register MUST UPDATE AS REGISTERS ARE ADDED
  Serial.println();
  Serial << "Register Map of Teensy";
  Serial.println();
  Serial.println();
  
  uint32_t first_pointer;
  uint32_t next_pointer;
  first_pointer = (uint32_t)&registers -> reg_map;//Grab the address of the first register in the register map. (uint32_t) is a cast used to get the address to the correct type

  next_pointer = (uint32_t)&registers -> reg_map.init_motor_controllers - first_pointer;
  Serial << "init_motor_controllers: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.init_motor_controllers;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.reset_imu - first_pointer;
  Serial << "reset_imu: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.reset_imu;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.dead_switch - first_pointer;
  Serial << "dead_switch: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.dead_switch;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.euler_heading - first_pointer;
  Serial << "euler_heading: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.euler_heading;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.euler_roll - first_pointer;
  Serial << "euler_roll: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.euler_roll;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.euler_pitch - first_pointer;
  Serial << "euler_pitch: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.euler_pitch;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.accl_x - first_pointer;
  Serial << "accl_x: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.accl_x;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.gyro_x - first_pointer;
  Serial << "gyro_x: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.gyro_x;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.accl_y - first_pointer;
  Serial << "accl_y: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.accl_y;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.gyro_y - first_pointer;
  Serial << "gyro_y: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.gyro_y;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.accl_z - first_pointer;
  Serial << "accl_z: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.accl_z;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.gyro_z - first_pointer;
  Serial << "gyro_z: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.gyro_z;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();


  next_pointer = (uint32_t)&registers -> reg_map.radio_throttle - first_pointer;
  Serial << "radio_throttle: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.radio_throttle;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.radio_steering - first_pointer;
  Serial << "radio_steering: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.radio_steering;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_torques[0] - first_pointer;
  Serial << "torque front right/node_torques[0]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_torques[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_torques[1] - first_pointer;
  Serial << "torque front left/node_torques[1]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_torques[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_torques[2] - first_pointer;
  Serial << "torques_back_right/node_torques[2]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_torques[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_torques[3] - first_pointer;
  Serial << "torque back left/node_torques[3]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_torques[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.servo_out - first_pointer;
  Serial << "servo_out: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.servo_out;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_rpms[0] - first_pointer;
  Serial << "rpm front right/node_rpms[0]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_rpms[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_rpms[1] - first_pointer;
  Serial << "rpm front left/node_rpms[1]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_rpms[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_rpms[2]- first_pointer;
  Serial << "rpm back right/node_rpms[2]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_rpms[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_rpms[3] - first_pointer;
  Serial << "rpm back left/node_rpms[3]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_rpms[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.shutdown_MCs - first_pointer;
  Serial << "shutdown_MCs: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.shutdown_MCs;
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();
  
  next_pointer = (uint32_t)&registers -> reg_map.node_errors[0] - first_pointer;
  Serial << "node_errors[0]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_errors[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_errors[1] - first_pointer;
  Serial << "node_errors[1]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_errors[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_errors[2] - first_pointer;
  Serial << "node_errors[2]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_errors[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_errors[3] - first_pointer;
  Serial << "node_errors[3]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_errors[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_statuswords[0] - first_pointer;
  Serial << "node_statuswords[0]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_statuswords[0];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println(); 

  next_pointer = (uint32_t)&registers -> reg_map.node_statuswords[1] - first_pointer;
  Serial << "node_statuswords[1]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_statuswords[1];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println(); 

  next_pointer = (uint32_t)&registers -> reg_map.node_statuswords[2] - first_pointer;
  Serial << "node_statuswords[2]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_statuswords[2];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();

  next_pointer = (uint32_t)&registers -> reg_map.node_statuswords[3] - first_pointer;
  Serial << "node_statuswords[3]: ";
  Serial.println();
  Serial << " \t value = " << registers -> reg_map.node_statuswords[3];
  Serial.println();
  Serial << " \t index = " << next_pointer;
  Serial.println();
  Serial.println();


  //REFERENCE!! REPLACE EVERY TIME SOMETHING IS ADDED TO THE REGISTER MAP
//  uint8_t init_motor_controllers;
//  uint8_t reset_imu;//Will re-run the bno055 initialization code...the intitial conditions of the euler angle readings will change when you reset...may want to integrate this into the dead switch logic
//  uint8_t dead_switch;
//  // IMU
//  int16_t euler_heading;
//  int16_t euler_roll;
//  int16_t euler_pitch;
//  int16_t accl_x;
//  int16_t gyro_x;
//  int16_t accl_y;
//  int16_t gyro_y;
//  int16_t accl_z;
//  int16_t gyro_z;
//  //Servo and Radio
//  int16_t radio_throttle;
//  int16_t radio_steering;
//  // Output/Actuation Registers
//  int16_t node_torques[4]; //Array of node torque actuations. 0 - torque front right, 1 - torque front left, 2 - torque back right, 3 - torque back left
//  int16_t servo_out;
//  //Velocity Units are in RPM and the data comes in from the MC's as 32 bit integers. This can be truncated to 16 bits because there is no way our motors will be spinning more than 32,768 rpm
//  int16_t node_rpms[4]; //Array of node rpm readings. 0 - rpm front right, 1 - rpm front left, 2 - rpm back right, 3 - rpm back left
//  //CAN Motor Controller Commands
//  uint8_t shutdown_MCs;//Not yet implemented but will need to be at some point.
//  //CAN Error Code Registers
//  uint8_t node_errors[4];//Array of node error messages
//  //CAN Statusword Registers 
//  uint8_t node_statuswords[4];//Array of node statuswordswords

}



