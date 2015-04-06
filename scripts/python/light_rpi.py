#
# IAS Basic device framework.
#
# Author: Joeri Hermans
#

import sys
import socket
import struct
import os
import RPIO

from time import sleep

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gPin = int(sys.argv[4])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True
# Light state members.
gState = False
gTriggerDelay = 0.1

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

def toggle():
    global gState
    if( gState == True ):
        off()
    else:
        on()

def on():
    global gCommandOn
    global gState
    global gPin
    global gTriggerDelay
    if not gState:
        gState = True
        RPIO.setup(gPin, RPIO.OUT)
        updateState("state","1")
        sleep(gTriggerDelay)
        RPIO.setup(gPin, RPIO.IN)

def off():
    global gCommandOff
    global gState
    global gPin
    global gTriggerDelay
    if gState:
        gState = False
        RPIO.setup(gPin, RPIO.OUT)
        updateState("state","0")
        sleep(gTriggerDelay)
        RPIO.setup(gPin, RPIO.IN)

def processFeature(featureIdentifier,parameter):
    if( featureIdentifier == "toggle" ):
        toggle()
    elif( featureIdentifier == "on" ):
        on()
    elif( featureIdentifier == "off" ):
        off()

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
        except Exception as e:
            print(e)
            gRunning = False

def main():
    global gPin
    authenticate()
    RPIO.setup(gPin, RPIO.IN)
    processCommands()
    RPIO.cleanup()

if( __name__ == "__main__" ):
    main()