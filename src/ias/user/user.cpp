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

inline void User::initialize( void ) {
    mLoggedIn = false;
}

void User::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

User::User( const std::size_t id,
            const std::string & username,
            const std::string & password ) {
    initialize();
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

    mMutex.lock();
    mUsername = username;
    mMutex.unlock();
}

const std::string & User::getUsername( void ) const {

    mMutex.lock();
    const std::string & username = mUsername;
    mMutex.unlock();

    return ( username );
}

const std::string & User::getIdentifier( void ) const {
    return ( getUsername() );
}

void User::setPassword( const std::string & password ) {
    // Checking the precondition.
    assert( password.length() > 0 );

    mMutex.lock();
    mPassword = password;
    mMutex.unlock();
}

bool User::matchesPassword( const std::string & password ) const {
    bool match;

    mMutex.lock();
    match = mPassword == password;
    mMutex.unlock();

    return ( match );
}

void User::setLoggedIn( const bool loggedIn ) {
    mMutex.lock();
    mLoggedIn = loggedIn;
    mMutex.unlock();
}

bool User::isLoggedIn( void ) const {
    bool loggedIn;

    mMutex.lock();
    loggedIn = mLoggedIn;
    mMutex.unlock();

    return ( loggedIn );
}
