/**
 * A command which describes the properties of a "state" command. The state
 * command will list the state of the specified device.
 *
 * @date                    Jul 19, 2014
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
#include <ias/application/constants.h>
#include <ias/user/command/command_state.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandState::kIdentifier[] = "state";

// END Constant.s ////////////////////////////////////////////////////

void CommandState::setDeviceContainer( Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

CommandState::CommandState( Container<Device *> * devices ) :
    Command(kIdentifier) {
    setDeviceContainer(devices);
}

CommandState::~CommandState( void ) {
    // Nothing to do here.
}

std::string CommandState::execute( User * user,
                                   const std::string & parameters ) {
    std::string response;
    Device * device;
    Member * member;
    std::size_t n;

    // Checking the precondition.
    assert( user != nullptr );

    if( parameters.length() > 0 ) {
        device = mDevices->get(parameters);
        if( device != nullptr ) {
            const Technology * t = device->getTechnology();
            const std::vector<Member *> & members = t->getMembers();
            n = members.size();
            if( n > 0 ) {
                response = "{\"state\":[\n";
                for( std::size_t i = 0 ; i < n ; ++i ) {
                    member = members.at(i);
                    response += "  {\"" + member->getIdentifier() + "\":\"" +
                                        device->get(member->getIdentifier()) +
                                        "\"}";
                    if( n > 1 && i < ( n - 1 ) )
                        response += ',';
                    response += "\n";
                }
                response += "]}";
            }
        }
    }
    if( response.length() == 0 )
        response = kProtocolNack;

    return ( response );
}
