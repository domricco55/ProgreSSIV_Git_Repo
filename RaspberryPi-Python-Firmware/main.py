#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Apr 27 22:51:05 2018

@author: pi
"""

import wiringpi
import struct

wiringpi.wiringPiSetupGpio()
SPIChannel = 0
SPIFrequency = 122000
wiringpi.wiringPiSPISetup(SPIChannel,SPIFrequency)

read_bit = 0b10000000 #read bit
write_bit = 0b0000000 #write bit
address = 0
data = 0
#buf = bytes(127)
buf = struct.pack('B', address | read_bit, data)
#buf ='\x00'

print(buf.decode('utf8'))

retlen, retdata = wiringpi.wiringPiSPIDataRW(SPIChannel,buf)
print(buf)

print ('retlen ', retlen)
print ('retdata ',retdata)
