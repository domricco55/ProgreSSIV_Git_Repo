#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr 27 22:51:05 2018

@author: pi
"""

import wiringpi
import struct
import time

wiringpi.wiringPiSetupGpio()
SPIChannel = 0
SPIFrequency = 122000/2
wiringpi.wiringPiSPISetup(SPIChannel,SPIFrequency)

read_bit = 0b10000000 #read bit
write_bit = 0b0000000 #write bit
address = 0 #send an address in the first byte
data = 0

def send_packets_read(num_packets=1):

    for n in range(num_packets):
        buf = struct.pack('BBBBBBBBBB', address | read_bit, 1,1,1,1,1,1,1,1,1)
    
        retlen, retdata = wiringpi.wiringPiSPIDataRW(SPIChannel,buf)

        return_tuple = struct.unpack('BBBBBBBBBB',retdata)
        print (return_tuple)

        #time.sleep(1)
        
def send_packets_write(num_packets=1):

    for n in range(num_packets):
        buf = struct.pack('BBBBBBBBB', address | write_bit, 1,2,3,4,5,6,7,8)
    
        retlen, retdata = wiringpi.wiringPiSPIDataRW(SPIChannel,buf)

        return_tuple = struct.unpack('BBBBBBBBB',retdata)
        print (return_tuple)

        #time.sleep(1)
        
def send_1_byte():
    buf = struct.pack('B', address | read_bit)

    retlen, retdata = wiringpi.wiringPiSPIDataRW(SPIChannel,buf)
    #print(buf)
    
    print (struct.unpack('B',retdata))