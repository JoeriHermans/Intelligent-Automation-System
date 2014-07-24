/**
 * A server which is responsible for interacting with devices.
 *
 * @date                    July 7, 2014
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

#ifndef DEVICE_SERVER_H_
#define DEVICE_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <map>
#include <mutex>
#include <thread>

// Application dependencies.
#include <ias/dispatcher/dispatcher.h>
#include <ias/server/server.h>
#include <ias/server/session/session.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class DeviceServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * A map which holds all active sessions and their threads.
     */
    std::map<Session *, std::thread *> mSessions;
    
    /**
     * A mutex which will synchronize the sessions map.
     */
    std::mutex mMutexSessions;
    
    /**
     * A vector which holds all inactive session threads.
     */
    std::vector<std::thread *> mInactiveThreads;
    
    /**
     * A thread which listens for incoming device connections.
     */
    std::thread * mListenThread;
    
    /**
     * A thread which dispatches commands from the server.
     */
    std::thread * mDispatchThread;
        
    /**
     * A dispatcher which holds all channels to all connected devices.
     */
    Dispatcher<const std::string &> mConnectedDevices;
    
    /**
     * Contains all device identifiers available to the controller.
     */
    std::vector<std::string> mDeviceIdentifiers;
    
    /**
     * A socket which is connected to the IAS server.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    Socket * mSocket;
    
    /**
     * A flag which indicates that the server is allowed to run.
     */
    bool mFlagRunning;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setSocket( Socket * socket );
    
    void setDeviceIdentifiers( const std::vector<std::string> & identifiers );
    
    void startListenThread( void );
    
    void startDispatchThread( void );
    
    void signalSessions( void );
    
    void cleanupFinishingThreads( void );
    
    void dispatchCommand( void );
    
    bool readBytes( char * buffer , const unsigned int n );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    DeviceServer( ServerSocket * serverSocket,
                  Socket * socket,
                  const std::vector<std::string> & devices );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
        
    virtual ~DeviceServer( void );
        
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void start( void );

    virtual void stop( void );

    virtual void join( void );
    
    virtual void update( void );
    
    virtual void update( void * argument );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_SERVER_H_ */
