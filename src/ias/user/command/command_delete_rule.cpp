/**
 * A command which is responsible for unregistering rules from IAS>
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
#include <vector>
#include <iostream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_delete_rule.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandDeleteRule::kIdentifier[] = "drule";

// END Constants. ////////////////////////////////////////////////////

void CommandDeleteRule::setDeviceContainer( const Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

void CommandDeleteRule::setRuleContainer( Container<Rule *> * rules ) {
    // Checking the precondition.
    assert( rules != nullptr );

    mRules = rules;
}

CommandDeleteRule::CommandDeleteRule( Container<Device *> * devices,
                                      Container<Rule *> * rules ) :
    Command(kIdentifier) {
    setDeviceContainer(devices);
    setRuleContainer(rules);
}

CommandDeleteRule::~CommandDeleteRule( void ) {
    // Nothing to do here.
}

std::string CommandDeleteRule::execute( const std::string & parameters ) {
    std::string response;
    std::vector<Device *> devices;
    bool success;
    Rule * rule;

    success = false;
    if( parameters.length() > 0 ) {
        std::size_t id = static_cast<std::size_t>(atol(parameters.c_str()));
        rule = mRules->get(id);
        if( rule != nullptr ) {
            mRules->remove(rule);
            devices = mDevices->getAll();
            for( Device * device : devices ) {
                device->removeObserver(rule);
            }
            success = true;
            response = kProtocolAck;
        }
    }
    if( !success )
        response = kProtocolNack;

    return ( response );
}
