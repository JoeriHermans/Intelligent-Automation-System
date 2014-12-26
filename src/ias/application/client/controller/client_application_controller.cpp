/**
 * A class which describes the properties and actions of a client application
 * controller. This controller will be responsible for handling/relaying view
 * triggers from the view.
 *
 * @date                    December 15, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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
#include <ias/application/client/controller/client_application_controller.h>

// END Includes. /////////////////////////////////////////////////////

inline void ClientApplicationController::initialize( void ) {
    mModel = nullptr;
}

void ClientApplicationController::setModel( ClientApplicationModel * model ) {
    // Checking the precondition.
    assert( model != nullptr );

    mModel = model;
}

ClientApplicationController::ClientApplicationController(
        ClientApplicationModel * model ) {
    initialize();
    setModel(model);
}

void ClientApplicationController::login( const std::string & username,
                                         const std::string & password ) {
    mModel->authorize(username,password);
}

void ClientApplicationController::createConnection( const std::string & address,
                                                    const std::size_t port ) {
    mModel->createConnection(address,port);
}

void ClientApplicationController::execute( const std::string & command ) {
    mModel->execute(command);
}

void ClientApplicationController::closeConnection( void ) {
    mModel->closeConnection();
}
