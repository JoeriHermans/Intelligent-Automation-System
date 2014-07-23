/**
 * A class which describes the properties and actions of a say command.
 * IAS's NLP engine will process the string and execute a set of actions
 * based on the probability distributions which have been derrived from
 * the specified string.
 *
 * @date					Jul 20, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_say.h>
#include <ias/ai/nlp/sentence.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandSay::kIdentifier[] = "say";

// END Constants. ////////////////////////////////////////////////////

CommandSay::CommandSay( void ) :
    Command(kIdentifier) {
    // TODO Implement.
}

CommandSay::~CommandSay( void ) {
    // Nothing to do here.
}

std::string CommandSay::execute( const std::string & parameters ) {
    std::string output;

    if( parameters.length() > 0 ) {
        Sentence sentence(parameters);
        
        // TODO Implement.
        output = kProtocolAck;
    } else {
        output = kProtocolNack;
    }
    
    return ( output );
}
