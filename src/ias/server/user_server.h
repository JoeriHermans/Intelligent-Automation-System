/**
 * A class which describes the properties and actions of a user server. A
 * user servers allows for users to connect and execute commands remotely.
 *
 * @date                    Jul 18, 2014
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

#ifndef USER_SERVER_H_
#define USER_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <thread>
#include <utility>
#include <map>
#include <mutex>

// Application dependencies.
#include <ias/server/server.h>
#include <ias/server/session/session.h>
#include <ias/user/user.h>
#include <ias/user/command/command_dispatcher.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class UserServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A containers which holds the set of all users available in
     * IAS.
     */
    Container<User *> * mUsers;

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
     * A class which is responsible for dispatching user commands.
     */
    CommandDispatcher * mDispatcher;
    
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
    
    void setUserContainer( Container<User *> * users );
    
    void setDispatcher( CommandDispatcher * dispatcher );
    
    void cleanupFinishingThreads( void );
    
    void signalSessions( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    UserServer( ServerSocket * serverSocket,
                Container<User *> * users,
                CommandDispatcher * dispatcher );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~UserServer( void );
    
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

#endif /* USER_SERVER_H_ */
