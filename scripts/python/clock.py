#
# Clock technology.
#
# Author: Joeri Hermans
#

import sys
import socket
import struct
import datetime
from datetime import date
import time
import re
from threading import Thread

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True
gUpdateInterval = int(sys.argv[4])

# State members
gTimestampUnix = str(int(time.time()))
gYear = "0"
gMonth = "0"
gDay = "0"
gHour = "0"
gMin = "0"
gDayOfTheWeek = "0"

def updateTimestamp():
    global gTimestampUnix
    global gUpdateInterval
    
    intGlobalTimestamp = int(gTimestampUnix)
    timestamp = int(time.time())
    dt = timestamp - intGlobalTimestamp
    if( dt >= gUpdateInterval ):
        while( dt > 0 ):
            dt -= gUpdateInterval
            intGlobalTimestamp += gUpdateInterval
            gTimestampUnix = str(intGlobalTimestamp)
            updateState("timestamp_unix",gTimestampUnix)

def updateYear():
    global gYear
    year = str(date.today().year)
    if( gYear != year ):
        gYear = year
        updateState("year",gYear)

def updateMonth():
    global gMonth
    month = str(date.today().month)
    if( gMonth != month ):
        gMonth = month
        updateState("month",gMonth)

def updateDay():
    global gDay
    day = str(date.today().day)
    if( gDay != day ):
        gDay = day
        updateState("day",gDay)

def updateHour():
    global gHour
    hour = str(datetime.datetime.now().strftime("%H"))
    if( gHour != hour ):
        gHour = hour
        updateState("hour",gHour)

def updateMinute():
    global gMin
    minute = str(datetime.datetime.now().strftime("%M"))
    if( gMin != minute ):
        gMin = minute
        updateState("min",gMin)

def updateDayOfTheWeek():
    global gDayOfTheWeek
    
    dayOfTheWeek = str(datetime.datetime.now().weekday())
    if( gDayOfTheWeek != dayOfTheWeek ):
        gDayOfTheWeek = dayOfTheWeek
        updateState("dayoftheweek",gDayOfTheWeek)

def updateAll():
    updateTimestamp()
    updateYear()
    updateMonth()
    updateDay()
    updateHour()
    updateMinute()
    updateDayOfTheWeek()

def setInterval( dt ):
    global gUpdateInterval
    
    gUpdateInterval = dt
    print("Updating interval: " + dt)

def update():
    global gRunning
    global gUpdateInterval
    updateAll()
    lastUpdate = time.time()
    while gRunning:
        currentTimestamp = time.time()
        dt = currentTimestamp - lastUpdate
        if( dt >= gUpdateInterval ):
            updateAll()
            lastUpdate = time.time()
        time.sleep(0.1)

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
    if( featureIdentifier == "setinterval" and 
        len(parameter) > 0 and parameter.isdigit() ):
        parameter = int(parameter)
        setInterval(parameter)

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
    thread = Thread(target = update)
    thread.start()
    processCommands()
    thread.join()

if( __name__ == "__main__" ):
    main()