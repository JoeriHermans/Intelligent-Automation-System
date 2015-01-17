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
#include <ias/event/event_dispatcher.h>
#include <ias/database/interface/database_connection.h>
#include <ias/network/server_socket.h>
#include <ias/server/server.h>
#include <ias/server/session/session.h>
#include <ias/server/session_server.h>

// END Includes. /////////////////////////////////////////////////////

class EventServer : public SessionServer {

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
     * The dispatcher which will be responsible for dispatching the server
     * events to the connected sessions.
     *
     * @note        By default, this member will be equal to the null reference.
     */
    EventDispatcher * mEventDispatcher;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setDatabaseConnection( DatabaseConnection * dbConnection );

    void setEventDispatcher( EventDispatcher * eventDispatcher );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    Session * getSession( Socket * socket ) const;

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    EventServer( ServerSocket * socket,
                 DatabaseConnection * dbConnection,
                 EventDispatcher * eventDispatcher );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~EventServer( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void join( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* EVENT_SERVER_H_ */
