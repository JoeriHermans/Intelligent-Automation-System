/**
 * A command which is responsible for listing all rules.
 *
 * @date                    Aug 3, 2014
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
#include <string>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_list_rules.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandListRules::kIdentifier[] = "lsr";

// END Constants. ////////////////////////////////////////////////////

void CommandListRules::setRuleContainer( const Container<Rule *> * rules ) {
    // Checking the precondition.
    assert( rules != nullptr );

    mRules = rules;
}

CommandListRules::CommandListRules( const Container<Rule *> * rules ) :
    Command(kIdentifier) {
    setRuleContainer(rules);
}

CommandListRules::~CommandListRules( void ) {
    // Nothing to do here.
}

std::string CommandListRules::execute( const std::string & parameters ) {
    std::string response;
    std::vector<Rule *> rules;
    std::size_t n;

    rules = mRules->getAll();
    n = rules.size();
    if( n > 0 ) {
        response = "{\"rules\":[\n";
        for( std::size_t i = 0 ; i < n ; ++i ) {
            response += "{\"id\":" + std::to_string(rules.at(i)->getId()) + "}";
            if( i < (n - 1) )
                response += ',';
            response += "\n";
        }
        response += "]}";
    } else {
        response = kProtocolAck;
    }

    return ( response );
}
