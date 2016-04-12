/**
 * A class which represents the properties and actions of a command which is
 * responsible for removing a controller (and the associated devices, rules)
 * from the system.
 *
 * @date                    3 April, 2015
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
#include <vector>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_remove_controller.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandRemoveController::kIdentifier[] = "removec";

// END Constants. ////////////////////////////////////////////////////

void CommandRemoveController::removeDevices( const Controller * controller ) {
    // Checking the precondition.
    assert( controller != nullptr );

    // Fetch all devices from the controller.
    const std::vector<const Device *> devices = controller->getDevices();
    // Remove every associated device from the container.
}

void CommandRemoveController::removeController( Controller * controller ) {
    Socket * socket;

    // Checking the precondition.
    assert( controller != nullptr );

    // Remove the controller from the container.
    mControllers->remove(controller);
    // Check if a remote connection with the controller has been established.
    if( controller->isConnected() ) {
        socket = controller->getSocket();
        socket->closeConnection();
    }
}

inline void CommandRemoveController::setControllers(
        Container<Controller *> * controllers ) {
    // Checking the precondition.
    assert( controllers != nullptr );

    mControllers = controllers;
}

inline void CommandRemoveController::setDevices(
        Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

inline void CommandRemoveController::setRules( Container<Rule *> * rules ) {
    // Checking the precondition.
    assert( rules != nullptr );

    mRules = rules;
}

CommandRemoveController::CommandRemoveController(
        Container<Controller *> * controllers,
        Container<Device *> * devices,
        Container<Rule *> * rules ) :
    Command(kIdentifier) {
    setControllers(controllers);
    setDevices(devices);
    setRules(rules);
}

std::string CommandRemoveController::execute( User * user,
                                              const std::string & parameters ) {
    Controller * controller;
    std::string response;

    // Checking the precondition.
    assert( user != nullptr );

    if( !parameters.empty() ) {
        controller = mControllers->get(parameters);
        if( controller != nullptr ) {
            removeDevices(controller);
            response = kProtocolAck;
        }
    }
    if( response.empty() )
        response = kProtocolNack;

    return ( response );
}
