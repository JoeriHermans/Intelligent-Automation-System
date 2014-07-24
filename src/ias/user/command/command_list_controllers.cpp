/**
 * A class which is responsible for listing all controllers and their properties
 * in IAS.
 *
 * @date                    Jul 20, 2014
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

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_list_controllers.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandListControllers::kIdentifier[] = "lsc";

// END Constants. ////////////////////////////////////////////////////

void CommandListControllers::setControllerContainer( 
    Container<Controller *> * c ) {
    // Checking the precondition.
    assert( c != nullptr );
    
    mControllers = c;
}

CommandListControllers::CommandListControllers( Container<Controller *> * c ) :
    Command(kIdentifier) {
    setControllerContainer(c);
}

CommandListControllers::~CommandListControllers( void ) {
    // Nothing to do here.
}

std::string CommandListControllers::execute( const std::string & params ) {
    std::string output;
    std::vector<Controller *> controllers;
    Controller * c;
    std::size_t n;
    
    controllers = mControllers->getAll();
    n = controllers.size();
    for( std::size_t i = 0 ; i < n ; ++i ) {
        c = controllers.at(i);
        output += c->getIdentifier() + " - ";
        if( c->isConnected() )
            output += kOnline;
        else
            output += kOffline;
        if( n > 1 && i < ( n - 1 ) )
            output += '\n';
    }
    
    return ( output );
}
