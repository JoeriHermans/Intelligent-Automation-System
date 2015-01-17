/**
 * A class which describes the actions and properties of an event session. This
 * session will notify the connected endpoint of server events (like device
 * updates, e.d.). This way, we can prevent polling.
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/server/session/event_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventSession::initialize( void ) {
    mDbConnection = nullptr;
    mEventDispatcher = nullptr;
    mChannel = nullptr;
    mFlagRunning = true;
}

void EventSession::setDatabaseConnection( DatabaseConnection * connection ) {
    // Checking the precondition.
    assert( connection != nullptr );

    mDbConnection = connection;
}

void EventSession::setEventDispatcher( EventDispatcher * eventDispatcher ) {
    // Checking the precondition.
    assert( eventDispatcher != nullptr );

    mEventDispatcher = eventDispatcher;
}

EventSession::EventSession( Socket * socket, DatabaseConnection * connection,
                            EventDispatcher * eventDispatcher ) :
    Session(socket) {
    initialize();
    setDatabaseConnection(connection);
    setEventDispatcher(eventDispatcher);
}

EventSession::~EventSession( void ) {
    if( mChannel != nullptr )
        mEventDispatcher->removeChannel(mChannel);
}

void EventSession::run( void ) {
    // TODO Implement.
}

void EventSession::stop( void ) {
    if( mFlagRunning ) {
        logi("Closing user session.");
        mFlagRunning = false;
    }
}
