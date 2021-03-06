#
# IAS Basic device framework.
#
# Author: Joeri Hermans
#

import sys
import socket
import struct
import os

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True
# Light state members.
gState = False
gCommandOn = "echo '255' > /sys/class/leds/tpacpi\:\:thinklight/brightness"
gCommandOff = "echo '0' > /sys/class/leds/tpacpi\:\:thinklight/brightness"

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
    gState = True
    os.system(gCommandOn)
    updateState("state","1")

def off():
    global gCommandOff
    global gState
    gState = False
    os.system(gCommandOff)
    updateState("state","0")

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
    authenticate()
    processCommands()

if( __name__ == "__main__" ):
    main()