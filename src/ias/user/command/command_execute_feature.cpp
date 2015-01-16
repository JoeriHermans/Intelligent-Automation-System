/**
 * A command which is responsible for executing a feature on a certain device.
 *
 * @date                    Jul 19, 2014
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
#include <sstream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/device/action/action.h>
#include <ias/user/command/command_execute_feature.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandExecuteFeature::kIdentifier[] = "execf";

// ENC Constants. ////////////////////////////////////////////////////

void CommandExecuteFeature::setDeviceContainer( Container<Device *> * d ) {
    // Checking the precondition.
    assert( d != nullptr );

    mDevices = d;
}

CommandExecuteFeature::CommandExecuteFeature( Container<Device *> * d ) :
    Command(kIdentifier) {
    setDeviceContainer(d);
}

CommandExecuteFeature::~CommandExecuteFeature( void ) {
    // Nothing to do here.
}

std::string CommandExecuteFeature::execute( const std::string & parameters ) {
    std::string output;
    std::stringstream ss;
    std::string deviceIdentifier;
    std::string featureIdentifier;
    std::string parameter;
    Device * device;

    if( parameters.length() > 0 ) {
        ss << parameters;
        ss >> deviceIdentifier;
        ss >> featureIdentifier;
        if( !deviceIdentifier.empty() && !featureIdentifier.empty() ) {
            parameter = ss.str().substr(deviceIdentifier.length() +
                                        featureIdentifier.length() + 1);
            trim(deviceIdentifier);
            trim(featureIdentifier);
            trim(parameter);
            device = mDevices->get(deviceIdentifier);
            if( device != nullptr ) {
                Action action(featureIdentifier,parameter);

                device->execute(action);
                output = kProtocolAck;
            }
        }
    }
    if( output.length() == 0 )
        output = kProtocolNack;

    return ( output );
}
