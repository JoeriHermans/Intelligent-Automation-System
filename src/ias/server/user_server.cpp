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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/server/user_server.h>
#include <ias/server/session/user_session.h>
#include <ias/user/command/command_stop.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

void UserServer::setUserContainer( Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );

    mUsers = users;
}

void UserServer::setDispatcher( CommandDispatcher * dispatcher ) {
    // Checking the precondition.
    assert( dispatcher != nullptr );

    mDispatcher = dispatcher;
}

void UserServer::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr );

    mDbConnection = dbConnection;
}

Session * UserServer::getSession( Socket * socket ) const {
    // Checking the precondition.
    assert( socket != nullptr );

    return ( new UserSession(socket,mUsers,mDispatcher,mDbConnection) );
}

UserServer::UserServer( ServerSocket * serverSocket,
                        Container<User *> * users,
                        CommandDispatcher * dispatcher,
                        DatabaseConnection * dbConnection ) :
    SessionServer(serverSocket) {
    setUserContainer(users);
    setDispatcher(dispatcher);
    setDatabaseConnection(dbConnection);
}

UserServer::~UserServer( void ) {
    join();
}

void UserServer::join( void ) {
    SessionServer::join();
}
