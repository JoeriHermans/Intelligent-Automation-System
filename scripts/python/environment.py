#
# An implementation of the environment technology. This technology
# is responsible for reporting sensor data on the weather, sun, and
# other environmental conditions.
#
# Author: Joeri Hermans
#

import sys
import socket
import struct
import requests

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True

# Begin state members.
gSunsetTimestamp = 0
gSunriseTimestamp = 0
gHumidity = 0
gPressure = 0
gTemperature = 0
gTemperatureMin = 0
gTemperatureMax = 0
gWindSpeed = 0
gWindDirection = 0
gLocation = sys.argv[4]
gCoulds = 0
gUpdateInterval = sys.argv[5] # In seconds
gMetrics = int(sys.argv[6]) # If != 0, reported values are in the metric system.
gApiUrl = ""

def setApiUrl():
    global gApiUrl
    global gLocation
    gApiUrl = "http://api.openweathermap.org/data/2.5/weather?q=" + gLocation
    if( gMetrics != 0 ):
        gApiUrl +=  "&units=metric"

def updateState( stateIdentifier , newValue ):
    global gSocket
    stateIdentifierLength = len(stateIdentifier)
    newValueLength = len(newValue)
    data = struct.pack("!BBB",0x01,stateIdentifierLength,newValueLength);
    data += str.encode(stateIdentifier)
    data += str.encode(newValue)
    gSocket.sendall(data)

def sendFullState():
    global gLocation
    global gUpdateInterval
    updateState("location",str(gLocation))
    updateState("updateinterval",str(gUpdateInterval))

def authenticate():
    global gDeviceIdentifier
    global gSocket;
    identifierLength = len(gDeviceIdentifier)
    message = struct.pack("!BB",0x00,identifierLength) + bytes(gDeviceIdentifier.encode("ascii"));
    gSocket.sendall(message);

def setInterval( seconds ):
    global gUpdateInterval
    gUpdateInterval = seconds
    updateState("updateinterval",str(seconds))

def update():
    global gApiUrl
    response = requests.get(gApiUrl)
    data = response.json()
    # TODO Parse JSON.

def setLocation( location ):
    global gLocation
    gLocation = location
    updateState("location",gLocation)
    setApiUrl()
    update()
    sendFullState()

def processFeature(featureIdentifier,parameter):
    global gRunning
    if( featureIdentifier == "setinterval" and 
        len(parameter) > 0 and
        parameter.isdigit() ):
        parameter = int(parameter)
        setInterval(parameter)
    elif( featureIdentifier == "setlocation" and len(parameter) > 0 ):
        setLocation(parameter)
    else:
        gRunning = False

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
    else:
        parameter = ""
    parameter = parameter.decode("ascii")
    processFeature(featureIdentifier,parameter)
    

def processCommands():
    global gRunning
    while( gRunning ):
        try:
            processCommand()
        except:
            gRunning = False

def main():
    authenticate()
    setApiUrl()
    update()
    sendFullState()
    processCommands()

if( __name__ == "__main__" ):
    main()