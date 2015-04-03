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

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_remove_controller.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandRemoveController::kIdentifier[] = "removec";

// END Constants. ////////////////////////////////////////////////////

CommandRemoveController::CommandRemoveController( void ) :
    Command(kIdentifier) {
    // TODO Implement.
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
            // TODO Implement.
        }
    }
    if( response.empty() )
        response = kProtocolNack;

    return ( response );
}
