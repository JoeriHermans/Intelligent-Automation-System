/**
 * A class which will handle incoming connections from controllers and dispatch
 * them accordingly.
 *
 * @date                    July 6, 2014
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

#ifndef CONTROLLER_SERVER_H_
#define CONTROLLER_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <thread>
#include <utility>
#include <map>
#include <mutex>

// Application dependencies.
#include <ias/controller/controller.h>
#include <ias/server/server.h>
#include <ias/server/session/session.h>
#include <ias/server/session/controller_session.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class ControllerServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * A containers which holds the set of all controllers available in
     * IAS.
     */
    Container<Controller *> * mControllers;
    
    /**
     * A map which holds all running controller sessions and the
     * corresponding sessions.
     */
    std::map<Session *,std::thread *> mSessions;
    
    /**
     * A set of threads which are meant for cleanup.
     */
    std::vector<std::thread *> mInactiveThreads;
    
    /**
     * Contains a pointer to the main server thread.
     */
    std::thread * mMainThread;
    
    /**
     * A flag which indicates if the server needs to stop.
     */
    bool mFlagRunning;
    
    /**
     * A mutex which sync's the access to the sessions map.
     */
    std::mutex mMutexSessions;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setControllerContainer( Container<Controller *> * controllers );
    
    void cleanupFinishingThreads( void );
    
    void signalSessions( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    ControllerServer( ServerSocket * socket,
                      Container<Controller *> * controllers );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ControllerServer( void );
    
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

#endif /* CONTROLLER_SERVER_H_ */
