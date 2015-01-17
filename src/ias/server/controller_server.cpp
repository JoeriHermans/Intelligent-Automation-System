/**
 * A class which will handle incoming connections from controllers and dispatch
 * them accordingly.
 *
 * @date                    July 6, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
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
#include <ias/server/controller_server.h>
#include <ias/server/session/controller_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void ControllerServer::initialize( void ) {
    mControllers = nullptr;
}

void ControllerServer::setControllerContainer( Container<Controller *> * c ) {
    // Checking the precondition.
    assert( c != nullptr );

    mControllers = c;
}

Session * ControllerServer::getSession( Socket * socket ) const {
    // Checking the precondition.
    assert( socket != nullptr );

    return ( new ControllerSession(socket,mControllers) );
}

ControllerServer::ControllerServer( ServerSocket * socket,
                                    Container<Controller *> * controllers ) :
    SessionServer(socket) {
    initialize();
    setControllerContainer(controllers);
}

ControllerServer::~ControllerServer( void ) {
    join();
}

void ControllerServer::join( void ) {
    // Nothing to do here.
}
