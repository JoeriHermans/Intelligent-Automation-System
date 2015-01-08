/**
 * A class which is responsible for providing information about users.
 * By default, when no parameters are specified, this function will list the
 * users which are currently logged in into the system (like the UNIX command).
 *
 * @date                    8 January, 2015
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
#include <ias/user/command/command_users.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandUsers::kIdentifier[] = "users";

// END Constants. ////////////////////////////////////////////////////

void CommandUsers::setContainer( const Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );

    mUsers = users;
}

std::string CommandUsers::onlineUsers( void ) const {
    std::string response;
    User * user;

    std::vector<User *> users = mUsers->getAll();
    for( auto it = users.begin() ; it != users.end() ; ++it ) {
        user = (*it);
        if( user->isLoggedIn() )
            response += user->getUsername() + "\n";
    }

    return ( response );
}

CommandUsers::CommandUsers( const Container<User *> * users ) :
    Command(kIdentifier) {
    setContainer(users);
}

std::string CommandUsers::execute( const std::string & parameters ) {
    std::string response;

    // TODO Implement.
    response = onlineUsers();

    return ( response );
}
