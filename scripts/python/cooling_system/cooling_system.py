#
# An implementation of a technology which allows us to control an industrial
# cooling system in an efficient way.
#
# Author: Joeri Hermans
#

import sys
import socket
import struct
import time
from threading import Thread
from numpy import *

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True

# Global state members.
gUpdateInterval = int(sys.argv[4])
gTemperatureResolution = 0.1 # In meters
gCoolingSystemWidth = 2 # In meters
gCoolingSystemDepth =  1 # In meters
gCoolingSystemHeight = 1.9 # In meters
gTemperatureMap = None

## COOLING SYSTEM FUNCTIONS ####################################################

def initializeTemperatureMap():
    global gTemperatureResolution
    global gCoolingSystemWidth
    global gCoolingSystemDepth
    global gCoolingSystemHeight

def updateTemperatureMap():
    print("TODO Implement.")

## CORE FUNCTIONS ##############################################################

def updateState( stateIdentifier , newValue ):
    global gSocket
    stateIdentifierLength = len(stateIdentifier)
    newValueLength = len(newValue)
    data = struct.pack("!BBB",0x01,stateIdentifierLength,newValueLength);
    data += str.encode(stateIdentifier)
    data += str.encode(newValue)
    gSocket.sendall(data)

def authenticate():
    global gDeviceIdentifier
    global gSocket;
    identifierLength = len(gDeviceIdentifier)
    message = struct.pack("!BB",0x00,identifierLength) + bytes(gDeviceIdentifier.encode("ascii"));
    gSocket.sendall(message);

def processFeature(featureIdentifier,parameter):
    # TODO Implement
    print("Executing " + featureIdentifier + " with " + parameter)

def processCommand():
    global gSocket
    global gRunning
    data = gSocket.recv(3);
    data = struct.unpack("!BBB",data)
    if( data[0] != 0x01 ):
        gRunning = False
        return
    featureIdentifierLength = data[1]
    parameterLength = data[2]
    featureIdentifier = gSocket.recv(featureIdentifierLength)
    featureIdentifier = featureIdentifier.decode("ascii")
    if( parameterLength > 0 ):
        parameter = gSocket.recv(parameterLength)
        parameter = parameter.decode("ascii")
    else:
        parameter = ""
    processFeature(featureIdentifier,parameter)

def processCommands():
    global gRunning
    while( gRunning ):
        try:
            processCommand()
        except:
            gRunning = False

def monitor():
    global gRunning
    global gUpdateInterval
    while( gRunning ):
        updateTemperatureMap()
        time.sleep(gUpdateInterval)

def main():
    authenticate()
    thread = Thread(target = monitor)
    initializeTemperatureMap()
    thread.start()
    processCommands()
    thread.join()

if( __name__ == "__main__" ):
    main()