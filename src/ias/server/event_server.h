/**
 * A class which describes the properties and actions of the event server. This
 * server will be responsible for reporting events to the client. This service
 * can be used to enable Server Sent Events, which removes the need for polling.
 *
 * @date                    14 January, 2014
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

#ifndef EVENT_SERVER_H_
#define EVENT_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <map>
#include <thread>
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/network/server_socket.h>
#include <ias/server/server.h>
#include <ias/server/session/session.h>

// END Includes. /////////////////////////////////////////////////////

class EventServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the database connection which will be used to check the
     * user credentials of incoming connections.
     *
     * @note        By default, this member will be equal to the null reference.
     */
    DatabaseConnection * mDbConnection;

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
     * Contains the main thread of the server.
     */
    std::thread * mMainThread;

    /**
     * A flag which indicates if the server needs to stop.
     */
    bool mFlagRunning;

    /**
     * A mutes which sync's the access to the sessions map.
     */
    std::mutex mMutexSessions;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setDatabaseConnection( DatabaseConnection * dbConnection );

    void cleanupFinishingThreads( void );

    void signalSessions( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    EventServer( ServerSocket * socket,
                 DatabaseConnection * dbConnection );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~EventServer( void );

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

#endif /* EVENT_SERVER_H_ */
