/**
 * A class which describes the abstract properties and actions of a
 * controller.
 *
 * @date                    Jun 2, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
 *
 * Copyright 2013 Joeri HERMANS
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef CONTROLLER_APPLICATION_H_
#define CONTROLLER_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <string>
#include <spawn.h>

// Application dependencies.
#include <ias/application/application.h>
#include <ias/network/socket.h>
#include <ias/util/util.h>
#include <ias/util/properties.h>

// Forward declarations.
class DeviceServer;

// END Includes. /////////////////////////////////////////////////////

class ControllerApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the socket which is connected to the IAS server.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    Socket * mSocket;
    
    /**
     * Contains all by-default and key-value relationships which have been
     * read from the configuration file.
     */
    Properties mProperties;
    
    /**
     * A vector which contains all device identifiers and corresponding bash
     * commands.
     */
    std::vector<std::string> mDevices;
    std::vector<std::string> mDeviceCommands;
    
    /**
     * Contains a vector of all PID's which have been initiated.
     */
    std::vector<pid_t> mPids;
    
    /**
     * Contains the device server which is responsible for handling
     * device updates and commands.
     */
    DeviceServer * mDeviceServer;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
        
    inline void initialize( void );
    
    void setup( const int argc , const char ** argv );
    
    void readConfiguration( const std::string & filePath );
    
    void readDevices( void );
    
    void allocateDeviceServer( void );
    
    void connectToServer( void );
    
    void authenticateWithServer( void );
    
    void startDeviceProcesses( void );
    
    void cleanupDeviceProcesses( void );

    void initializeLogger( void );
        
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    ControllerApplication( const int argc , const char ** argv );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ControllerApplication( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void );
    
    virtual void stop( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONTROLLER_APPLICATION_H_ */
