/**
 * A class which describes the properties and actions of a device session.
 *
 * @date					July 7, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

#ifndef DEVICE_SESSION_H_
#define DEVICE_SESSION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <utility>

// Application dependencies.
#include <ias/server/session/session.h>
#include <ias/dispatcher/dispatcher.h>

// END Includes. /////////////////////////////////////////////////////

class DeviceSession : public Session {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the dispatcher which will dispatch server commands to the
     * correct device. The session will add devices to this dispatcher.
     */
    Dispatcher<const std::string &> * mDispatcher;
    
    /**
     * Contains a set of all device identifiers.
     */
    const std::vector<std::string> * mDevices;
    
    /**
     * Contains the identifier of the authenticated device.
     */
    std::string mDevice;
    
    /**
     * Contains the socket which is connected with the server.
     */
    Socket * mServerSocket;
    
    /**
     * A flag tells the session to keep running.
     */
    bool mFlagRunning;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setDispatcher( Dispatcher<const std::string &> * d );
    
    void authorize( void );
    
    void setServerSocket( Socket * serverSocket );
    
    void setDevices( const std::vector<std::string> * devices );
    
    bool containsDevice( const std::string & identifier ) const;
    
    void updateDeviceState( void );
    
    void sendDeviceState( const std::string & stateIdentifier,
                          const std::string & value );
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
        
    DeviceSession( Socket * socket,
                   Socket * serverSocket,
                   Dispatcher<const std::string &> * dispatcher,
                   const std::vector<std::string> * devices );
        
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
        
    virtual ~DeviceSession( void );
        
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void );
    
    virtual void stop( void );
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_SESSION_H_ */
