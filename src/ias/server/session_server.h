/**
 * An abstract server which is based on session-based connections.
 *
 * @date                    17 January, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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

#ifndef SESSION_SERVER_H_
#define SESSION_SERVER_H_

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
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

class SessionServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

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

    void cleanupFinishingThreads( void );

    void signalSessions( void );

    void joinMainthread( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    virtual Session * getSession( Socket * socket ) const = 0;

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    SessionServer( ServerSocket * socket );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~SessionServer( void );

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

#endif /* SESSION_SERVER_H_ */
