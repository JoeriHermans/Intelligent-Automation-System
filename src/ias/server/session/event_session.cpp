/**
 * A class which describes the properties and actions of an event session.
 * This session will be responsible for notifying the client of events.
 *
 * @date                    14 January, 2015
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
#include <ias/server/session/event_session.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventSession::initialize( void ) {
    mDbConnection = nullptr;
}

void EventSession::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr && dbConnection->isConnected() );

    mDbConnection = dbConnection;
}

EventSession::EventSession( Socket * socket,
                            DatabaseConnection * dbConnection ) :
    Session(socket) {
    initialize();
    setDatabaseConnection(dbConnection);
}

EventSession::~EventSession( void ) {
    // Nothing to do here.
}

void EventSession::run( void ) {
    // TODO Implement.
}

void EventSession::stop( void ) {
    // TODO Implement.
}
