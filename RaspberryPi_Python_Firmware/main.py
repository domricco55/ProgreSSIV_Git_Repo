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


for n in range(10):
    buf = struct.pack('BBBBB', address | read_bit, data,1,1,1)

    retlen, retdata = wiringpi.wiringPiSPIDataRW(SPIChannel,buf)
    #print(buf)
    
    print (struct.unpack('BBBBB',retdata))
    #print ('retlen ', retlen)
    #print ('retdata ',retdata)
    time.sleep(1)
