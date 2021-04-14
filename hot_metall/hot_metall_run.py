#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Apr 14 18:14:12 2021

@author: honepa
"""
from time import sleep
import sys
from serial import Serial, SerialException

PORTS = ['/dev/ttyUSB0', '/dev/ttyUSB1', '/dev/ttyUSB2', '/dev/ttyUSB3', '/dev/ttyUSB4']


class Arduino():
    
    def __init__(self, x):
        self.port = None
        for port in PORTS:
            try:
                #print(port)
                self.port = Serial(port = port, baudrate = 9600, timeout = 2)
                #print(self.port.readlines())
                b = self.port.read()
                
                
                if b == x:
                    break               
               
                
            except SerialException as e:
                print(port, 'failed')
            
        if self.port == None:
            raise SerialException('Port is not found')
    
    def __del__(self):
        try:
            self.port.close()
        except AttributeError:
            print('nicht close', file = sys.stderr)

    def __str__(self):
        return str(self.port)
    
if __name__ == '__main__':
    
    mega = Arduino(1)
    print(mega)
    sleep(4)
    mega.port.write(str(40).encode())
    sleep(4)
    mega.port.write(str(43).encode())
    print(mega.port.readline().decode())
    sleep(0.5)
    mega.port.write(str(45).encode())
    #print(mega.port.readline().decode())
    #mega.port.write(str(50).encode())
    del mega
