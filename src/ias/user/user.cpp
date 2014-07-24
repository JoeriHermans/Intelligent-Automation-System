/**
 * A class which describes the properties and actions of a user.
 *
 * @date                    Jul 9, 2014
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
#include <ias/user/user.h>

// END Includes. /////////////////////////////////////////////////////

void User::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

User::User( const std::size_t id,
            const std::string & username,
            const std::string & password ) {
    setId(id);
    setUsername(username);
    setPassword(password);
}

User::~User( void ) {
    // Nothing to do here.
}

std::size_t User::getId( void ) const {
    return ( mId );
}

void User::setUsername( const std::string & username ) {
    // Checking the precondition.
    assert( username.length() > 0 );
    
    mUsername = username;
}

const std::string & User::getUsername( void ) const {
    return ( mUsername );
}

const std::string & User::getIdentifier( void ) const {
    return ( getUsername() );
}

void User::setPassword( const std::string & password ) {
    // Checking the precondition.
    assert( password.length() > 0 );
    
    mPassword = password;
}

bool User::matchesPassword( const std::string & password ) const {
    return ( mPassword == password );
}
