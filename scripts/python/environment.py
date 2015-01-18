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
import time
from threading import Thread

# Global members, which are required for the communication
# with the remote IAS controller.
gDeviceIdentifier = sys.argv[1]
gControllerAddress = sys.argv[2]
gControllerPort = int(sys.argv[3])
gSocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
gSocket.connect((gControllerAddress,gControllerPort))
gRunning = True

# Begin state members.
gSunsetTimestamp = str(0)
gSunriseTimestamp = str(0)
gHumidity = str(0)
gPressure = str(0)
gTemperature = str(0)
gTemperatureMin = str(0)
gTemperatureMax = str(0)
gWindSpeed = str(0)
gWindDirection = str(0)
gLocation = sys.argv[4]
gClouds = str(0)
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

def setSunsetTimestamp( timestamp ):
    global gSunsetTimestamp
    if( gSunsetTimestamp != timestamp ):
        gSunsetTimestamp = timestamp
        updateState("sunset_timestamp",timestamp)

def setSunriseTimestamp( timestamp ):
    global gSunriseTimestamp
    if( gSunriseTimestamp != timestamp ):
        gSunriseTimestamp = timestamp
        updateState("sunrise_timestamp",timestamp)

def setHumidity( humidity ):
    global gHumidity
    if( gHumidity != humidity ):
        gHumidity = humidity
        updateState("humidity",humidity)

def setPressure( pressure ):
    global gPressure
    if( gPressure != pressure ):
        gPressure = pressure
        updateState("pressure",pressure)

def setTemperature( temperature ):
    global gTemperature
    if( gTemperature != temperature ):
        gTemperature = temperature
        updateState("temperature",temperature)

def setTemperatureMin( temperature ):
    global gTemperatureMin
    if( gTemperatureMin != temperature ):
        gTemperatureMin = temperature
        updateState("temperature_min",temperature)

def setTemperatureMax( temperature ):
    global gTemperatureMax
    if( gTemperatureMax != temperature ):
        gTemperatureMax = temperature
        updateState("temperature_max",temperature)

def setWindSpeed( speed ):
    global gWindSpeed
    if( gWindSpeed != speed ):
        gWindSpeed = speed
        updateState("windspeed",speed)

def setWindDirection( direction ):
    global gWindDirection
    if( gWindDirection != direction ):
        gWindDirection = direction
        updateState("winddirection",direction)

def setClouds( clouds ):
    global gClouds
    if( gClouds != clouds ):
        gClouds = clouds
        updateState("clouds",clouds)

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

def parseAndProcessData( json ):
    try:
        message = json["cod"];
        if( message == "404" ):
            setTemperature("0");
            setTemperatureMin("0")
            setTemperatureMax("0")
            setPressure("0")
            setHumidity("0")
            setWindSpeed("0")
            setWindDirection("0")
            setClouds("0")
            setSunriseTimestamp("0")
            setSunsetTimestamp("0")
        else:
            # Fetch data from the JSON structure.
            temperature = json["main"]["temp"]
            temperature_min = json["main"]["temp_min"]
            temperature_max = json["main"]["temp_max"]
            pressure = json["main"]["pressure"]
            humidity = json["main"]["humidity"]
            wind_speed = json["wind"]["speed"]
            wind_direction = json["wind"]["deg"]
            clouds = json["clouds"]["all"]
            sunset = json["sys"]["sunset"]
            sunrise = json["sys"]["sunrise"]
            # Update the retrieved date.
            setTemperature(str(temperature))
            setTemperatureMin(str(temperature_min))
            setTemperatureMax(str(temperature_max))
            setPressure(str(pressure))
            setHumidity(str(humidity))
            setWindSpeed(str(wind_speed))
            setWindDirection(str(wind_direction))
            setClouds(str(clouds))
            setSunriseTimestamp(str(sunrise))
            setSunsetTimestamp(str(sunset))
    except Exception as e:
        print(str(e))

def update():
    global gApiUrl
    try:
        response = requests.get(gApiUrl)
        if( response.status_code == requests.codes.ok ):
            data = response.json()
            parseAndProcessData(data)
    except:
        print("Request error occurred.")

def setLocation( location ):
    global gLocation
    gLocation = location
    updateState("location",gLocation)
    setApiUrl()
    update()

def processFeature(featureIdentifier,parameter):
    global gRunning
    if( featureIdentifier == "setinterval" and 
        len(parameter) > 0 and
        parameter.isdigit() ):
        parameter = int(parameter)
        setInterval(parameter)
    elif( featureIdentifier == "setlocation" and len(parameter) > 0 ):
        setLocation(parameter)
    elif( featureIdentifier == "update" ):
        update()

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

def environmentMonitor():
    global gRunning
    global gUpdateInterval
    update()
    sendFullState()
    lastUpdateTimestamp = int(time.time())
    while( gRunning ):
        currentTimestamp = int(time.time())
        dt = currentTimestamp - lastUpdateTimestamp
        if( dt > int(gUpdateInterval) ):
            update()
            lastUpdateTimestamp = int(time.time())
        time.sleep(1)

def main():
    authenticate()
    setApiUrl()
    thread = Thread(target = environmentMonitor)
    thread.start()
    processCommands()
    thread.join()

if( __name__ == "__main__" ):
    main()