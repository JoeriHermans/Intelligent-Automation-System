/**
 * A class which describes the actions and properties of a user session.
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
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <sstream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/server/session/user_session.h>
#include <ias/util/util.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void UserSession::initialize( void ) {
    mUsers = nullptr;
    mUser = nullptr;
    mFlagRunning = true;
}

void UserSession::setUserContainer( Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );
    
    mUsers = users;
}

void UserSession::authorize( void ) {
    std::uint8_t type;
    std::uint8_t length;
    std::string hashedPassword;
    Reader * reader;
    
    logi("Authorizing user.");
    type = 0xff;
    length = 0x00;
    if( readBytes((char *) &type,1) &&
        readBytes((char *) &length,1) ) {
        char username[length + 1];
        reader = getSocket()->getReader();
        if( readBytes(username,length) ) {
            username[length] = 0;
            length = 0x00;
            if( readBytes((char *) &length,1) ) {
                char password[length + 1];
                if( readBytes(password,length) ) {
                    password[length] = 0;
                    hashedPassword = sha256GlobalSalts(password);
                    mUser = authenticateUser(username,hashedPassword.c_str());
                    logi(mUser->getIdentifier() + " has been authorized.");
                }
            }
        }
    }
    if( mUser == nullptr )
        loge("User authorization failed.");
    if( mUser == nullptr ) {
        getSocket()->closeConnection();
    } else {
        std::uint8_t code[2];
        Writer * w;

        w = getSocket()->getWriter();
        code[0] = 0x00;
        code[1] = 0x01;
        w->writeBytes((char *) &code,2);
    }
}

void UserSession::setDispatcher( CommandDispatcher * dispatcher ) {
    //Checking the precondition.
    assert( dispatcher != nullptr );
    
    mDispatcher = dispatcher;
}

User * UserSession::authenticateUser( const char * username,
                                      const char * password ) const {
    User * user;
    
    // Checking the precondition.
    assert( username != nullptr && password != nullptr );
    
    user = mUsers->get(username);
    if( user == nullptr ||
        !user->matchesPassword(password) ) {
        user = nullptr;
    }
    
    return ( user );
}

void UserSession::processCommand( void ) {
    Reader * reader;
    std::uint8_t size;
    
    reader = getSocket()->getReader();
    size = 0x00;
    reader->readByte((char *) &size);
    char buffer[size + 1];
    if( readBytes(buffer,size) ) {
        buffer[size] = 0;
        analyzeCommand(buffer);
    } else {
        getSocket()->closeConnection();
    }
}

void UserSession::analyzeCommand( const char * command ) {
    std::stringstream ss;
    std::string cmd;
    std::string identifier;
    std::string parameters;
    std::string response;
    
    // Checking the precondition.
    assert( command != nullptr );

    cmd = command;
    ss << cmd;
    ss >> identifier;
    if( mDispatcher->registered(identifier) ) {
        parameters = cmd.substr(identifier.length());
        trim(parameters);
        response = mDispatcher->dispatch(identifier,parameters);
        assert( response.length() != 0 );
    } else {
        response = kProtocolNack;
    }
    sendResponse(response.c_str(),response.length());
}

void UserSession::sendResponse( const char * buffer , const std::size_t n ) {
    std::uint8_t b;
    std::uint16_t messageSize;
    Writer * writer;
    
    b = 0x01;
    writer = getSocket()->getWriter();
    writer->writeBytes((char *) &b,1);
    messageSize = (std::uint16_t) n;
    messageSize = htons(messageSize);
    writer->writeBytes((char *) &messageSize,sizeof(messageSize));
    writer->writeBytes(buffer,n);
}

UserSession::UserSession( Socket * socket, 
                          Container<User *> * users,
                          CommandDispatcher * dispatcher ) :
    Session(socket) {
    initialize();
    setUserContainer(users);
    setDispatcher(dispatcher);
}

UserSession::~UserSession( void ) {
    stop();
}

void UserSession::run( void ) {
    std::uint8_t type;
    std::size_t nBytes;
    Reader * reader;
    Socket * socket;
    
    authorize();
    if( mUser != nullptr ) {
        socket = getSocket();
        reader = socket->getReader();
        while( mFlagRunning && socket->isConnected() ) {
            type = 0xff;
            nBytes = reader->readByte((char *) &type);
            if( nBytes == 0 ) {
                stop();
            } else {
                switch(type) {
                case 0x01:
                    processCommand();
                    break;
                default:
                    stop();
                    break;
                }
            }
        }
    }
}

void UserSession::stop( void ) {
    logi("Closing user session.");
    mFlagRunning = false;
    getSocket()->closeConnection();
}
