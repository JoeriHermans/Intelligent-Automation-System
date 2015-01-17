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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/server/event_server.h>
#include <ias/server/session/event_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

void EventServer::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr && dbConnection->isConnected() );

    mDbConnection = dbConnection;
}

void EventServer::setEventDispatcher( EventDispatcher * eventDispatcher ) {
    // Checking the precondition.
    assert( eventDispatcher != nullptr );

    mEventDispatcher = eventDispatcher;
}

Session * EventServer::getSession( Socket * socket ) const {
    // Checking the precondition.
    assert( socket != nullptr );

    return ( new EventSession(socket,mDbConnection,mEventDispatcher) );
}

EventServer::EventServer( ServerSocket * serverSocket,
                          DatabaseConnection * dbConnection,
                          EventDispatcher * eventDispatcher ) :
    SessionServer(serverSocket) {
    setDatabaseConnection(dbConnection);
    setEventDispatcher(eventDispatcher);
}

EventServer::~EventServer( void ) {
    join();
}

void EventServer::join( void ) {
    SessionServer::join();
}
