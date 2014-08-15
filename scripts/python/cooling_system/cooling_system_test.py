from numpy import *
import numpy as np
import matplotlib.pyplot as plt
import time

# Global state members.
gTemperatureResolution = 0.05 # In meters
gCoolingSystemWidth = 2 # In meters
gCoolingSystemDepth =  1 # In meters
gCoolingSystemHeight = 1.9 # In meters
gTemperatureMap = None
gTemperatureMapRows = 0
gTemperatureMapColumns = 0
gTemperatureMapMaxRadius = 0
gSensors = [(10,0),(10,20),(15,28)]
gNumSensors = 3

## COOLING SYSTEM FUNCTIONS ####################################################

def readSensor(sensorIndex):
    return {
        0: 3.4,
        1: 4.0,
        2: 4.2,
        3: 4.4,
    }[sensorIndex]

def calculateSlope( dt , dx ):
    return ( dt / dx )

def calculateDistance( c1 , c2 ):
    dx = c1[0] - c2[0]
    dy = c1[1] - c2[1]
    d = dx**2 + dy**2
    d = math.sqrt(d)
    return (d)

def initializeTemperatureMap():
    global gTemperatureResolution
    global gCoolingSystemWidth
    global gCoolingSystemDepth
    global gTemperatureMapRows
    global gTemperatureMapColumns
    global gTemperatureMap
    global gTemperatureMapMaxRadius
    nRows = int(gCoolingSystemDepth / gTemperatureResolution)
    nColumns = int(gCoolingSystemWidth / gTemperatureResolution)
    gTemperatureMap = zeros((nRows,nColumns))
    gTemperatureMap.fill(100)
    gTemperatureMapRows = nRows
    gTemperatureMapColumns = nColumns
    if( nRows >= nColumns ):
        gTemperatureMapMaxRadius = nRows
    else:
        gTemperatureMapMaxRadius = nColumns

def plotTemperatureMap():
    global gTemperatureMap
    plt.suptitle("Estimated temperature map")
    plt.xlabel("Meters")
    plt.ylabel("Meters")
    plt.imshow(gTemperatureMap,interpolation='nearest',extent=(0.1,2,0.1,1))
    plt.colorbar()
    plt.show()

def updateTemperature( x , y , t ):
    global gTemperatureMap
    global gTemperatureMapRows
    global gTemperatureMapColumns
    
    if( t <= gTemperatureMap[x,y] ):
        gTemperatureMap[x,y] = t

def plotTemperature( c , t , tSlope ):
    global gTemperatureMap
    global gTemperatureMapMaxRadius
    global gTemperatureMaxRows
    global gTemperatureMapColumns
    
    x = c[0]
    y = c[1]
    updateTemperature(x,y,t)
    r = 1
    while( r <= gTemperatureMapMaxRadius ):
        t = t + tSlope
        for i in range(0,gTemperatureMapRows):
            for j in range(0,gTemperatureMapColumns):
                if( (i - x)**2 + (j - y)**2 <= r**2 ):
                    updateTemperature(i,j,t)
        r = r + 1

def updateTemperatureMap():
    global gNumSensors
    for i, c1 in enumerate(gSensors):
        for j, c2 in enumerate(gSensors):
            d = calculateDistance(c1,c2)
            if( d == 0 ):
                continue
            tc1 = readSensor(i)
            tc2 = readSensor(j)
            dt = math.fabs(tc1 - tc2)
            tSlope = 0.1
            plotTemperature(c1,tc1,tSlope)

## CORE FUNCTIONS ##############################################################

def main():
    initializeTemperatureMap()
    updateTemperatureMap()
    plotTemperatureMap()

if( __name__ == "__main__" ):
    main()
