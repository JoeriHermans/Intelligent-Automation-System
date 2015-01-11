/**
 * A class which is responsible for listing all commands in IAS.
 *
 * @date                    Jul 18, 2014
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
#include <iostream>

// Application dependencies.
#include <ias/user/command/command_list_commands.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandListCommands::kIdentifier[] = "help";

// END Constants. ////////////////////////////////////////////////////

void CommandListCommands::setDispatcher( const CommandDispatcher * dispatcher ) {
    // Checking the precondition.
    assert( dispatcher != nullptr );

    mDispatcher = dispatcher;
}

CommandListCommands::CommandListCommands( const CommandDispatcher * dispatcher ) :
        Command(kIdentifier) {
    setDispatcher(dispatcher);
}

CommandListCommands::~CommandListCommands( void ) {
    // Nothing to do here.
}

std::string CommandListCommands::execute( const std::string & parameters ) {
    std::vector<Command *> commands;
    std::string output;
    std::size_t n;

    commands = mDispatcher->getCommands();
    n = commands.size();
    output = "{\"commands\":[\n";
    for( std::size_t i = 0 ; i < n ; ++i ) {
        Command * c = commands.at(i);
        output += "\"" + c->getIdentifier() + "\"\n";
    }
    output = "]}";

    return ( output );
}
