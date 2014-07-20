/**
 * A class which is responsible for dispatching user command to actions.
 *
 * @date					Jul 18, 2014
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

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/user/command/command_dispatcher.h>

// END Includes. /////////////////////////////////////////////////////

CommandDispatcher::CommandDispatcher( void ) {
    // Nothing to do here.
}

CommandDispatcher::~CommandDispatcher( void ) {
    for( auto it = mCommands.begin() ; it != mCommands.end() ; ++it ) {
        delete it->second;
    }
}

void CommandDispatcher::registerCommand( const std::string & identifier,
                                         Command * command ) {
    // Checking the precondition.
    assert( identifier.length() > 0 && command != nullptr );

    mCommands[identifier] = command;
}

bool CommandDispatcher::registered( const std::string & identifier ) const {
    bool registered;
    
    auto it = mCommands.find(identifier);
    if( it != mCommands.end() )
        registered = true;
    else
        registered = false;
    
    return ( registered );
}

std::string CommandDispatcher::dispatch( const std::string & identifier,
                                         const std::string & parameters ) {
    std::map<std::string,Command *>::const_iterator it;
    Command * command;
    std::string result;
    
    it = mCommands.find(identifier);
    if( it != mCommands.end() ) {
        command = it->second;
        result = command->execute(parameters);
    }
    
    return ( result );
}
