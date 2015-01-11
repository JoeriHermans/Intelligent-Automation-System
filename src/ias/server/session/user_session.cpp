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

    logi("Authorizing user.");
    type = 0xff;
    if( readBytes(reinterpret_cast<char *>(&type),1) ) {
        switch(type) {
        case 0x00:
            authorizeNormal();
            break;
        case 0x01:
            authorizeApiKey();
            break;
        }
    }
    printf("Type: %u\n",type);
    if( mUser == nullptr )
        loge("User authorization failed.");
    if( mUser == nullptr ) {
        getSocket()->closeConnection();
    } else {
        std::uint8_t code[2];
        Writer * w;

        // Send authorization byte.
        w = getSocket()->getWriter();
        code[0] = 0x00;
        code[1] = 0x01;
        w->writeBytes(reinterpret_cast<char *>(&code),2);
    }
}

void UserSession::authorizeNormal( void ) {
    std::uint8_t length;
    std::string hashedPassword;

    logi("Authorizing user using username and password.");
    length = 0x00;
    if( readBytes(reinterpret_cast<char *>(&length),1) ) {
        char username[length + 1];
        if( length > 1 && readBytes(username,length) ) {
            username[length] = 0;
            length = 0x00;
            if( readBytes(reinterpret_cast<char *>(&length),1) ) {
                char password[length + 1];
                if( readBytes(password,length) && length > 1 ) {
                    password[length] = 0;
                    hashedPassword = sha256GlobalSalts(password);
                    mUser = authenticateUser(username,hashedPassword.c_str());
                    if( mUser != nullptr ) {
                        if( !mUser->isLoggedIn() ) {
                            mUser->setLoggedIn(true);
                            logi(mUser->getUsername() +
                                    " has been authorized.");
                        } else {
                            loge(mUser->getUsername() +
                                    " is already logged in");
                            mUser = nullptr;
                        }
                    } else {
                        loge(std::string(username) +
                                " could not be authorized.");
                    }
                }
            }
        }
    }
}

void UserSession::authorizeApiKey( void ) {
    std::uint8_t length;
    std::string hashedKey;

    logi("Authorizing user using API key.");
    length = 0xff;
    if( readBytes(reinterpret_cast<char *>(&length),1) && length == 64 ) {
        char key[length + 1];
        if( length > 1 && readBytes(key,length) ) {
            hashedKey = sha256GlobalSalts(std::string(key));
            logi("API key: " + hashedKey);
            // TODO Implement.
        }
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

    if( strlen(username) > 0 ) {
        user = mUsers->get(username);
        if( user != nullptr && !user->matchesPassword(password) ) {
            user = nullptr;
        }
    } else {
        user = nullptr;
    }

    return ( user );
}

void UserSession::processCommand( void ) {
    Reader * reader;
    std::uint8_t size;

    reader = getSocket()->getReader();
    size = 0x00;
    reader->readByte(reinterpret_cast<char *>(&size));
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
    writer->writeBytes(reinterpret_cast<const char *>(&b),1);
    messageSize = static_cast<std::uint16_t>(n);
    messageSize = htons(messageSize);
    writer->writeBytes(reinterpret_cast<const char *>(&messageSize),
                       sizeof(messageSize));
    writer->writeBytes(buffer,n);
}

void UserSession::setTimeouts( void ) {
    Socket * socket;
    struct timeval tv;

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    socket = getSocket();
    socket->setReceiveTimeout(tv);
    socket->setSendTimeout(tv);
}

bool UserSession::heartbeat( void ) {
    static const char beat = 0x00;
    Writer * writer;
    bool ok;

    writer = getSocket()->getWriter();
    ok = (writer->writeByte(beat) == 1);

    return ( ok );
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
    if( mUser != nullptr )
        mUser->setLoggedIn(false);
}

void UserSession::run( void ) {
    bool heartbeatSend = false;
    std::uint8_t type;
    std::size_t nBytes;
    Reader * reader;
    Socket * socket;

    authorize();
    if( mUser != nullptr ) {
        socket = getSocket();
        reader = socket->getReader();
        setTimeouts();
        while( mFlagRunning && socket->isConnected() ) {
            type = 0xff;
            nBytes = reader->readByte(reinterpret_cast<char *>(&type));
            if( nBytes == 0 ) {
                if( !heartbeat() || heartbeatSend )
                    stop();
                else
                    heartbeatSend = true;
                continue;
            }
            switch(type) {
            case 0x00:
                if( !heartbeatSend )
                    heartbeat();
                break;
            case 0x01:
                processCommand();
                break;
            default:
                stop();
                break;
            }
            heartbeatSend = false;
        }
    }
    getSocket()->closeConnection();
}

void UserSession::stop( void ) {
    if( mFlagRunning ) {
        logi("Closing user session.");
        mFlagRunning = false;
    }
}
