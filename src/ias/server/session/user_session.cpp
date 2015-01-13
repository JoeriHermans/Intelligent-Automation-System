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
#include <ctime>
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
    mDbConnection = nullptr;
    mFlagRunning = true;
}

void UserSession::setUserContainer( Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );

    mUsers = users;
}

void UserSession::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr );

    mDbConnection = dbConnection;
}

void UserSession::authorize( void ) {
    std::uint8_t type = 0xff;

    logi("Authorizing user.");
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
                if( length > 1 && readBytes(password,length) ) {
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
    if( readBytes(reinterpret_cast<char *>(&length),1) && length > 0 ) {
        char key[length + 1];
        key[length] = 0;
        if( length > 1 && readBytes(key,length) ) {
            hashedKey = sha256GlobalSalts(std::string(key));
            validateApiKey(hashedKey);
        }
    }
}

void UserSession::validateApiKey( const std::string & key ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    User * user;
    std::size_t id;

    // Checking the precondition.
    assert( key.length() > 0 );

    if( mDbConnection->isConnected() ) {
        // Query is safe, because it has been hashed.
        std::string sql = "SELECT user_id, expires "
                          "FROM api_keys "
                          "WHERE api_keys.key = '" + key + "';";
        statement = mDbConnection->createStatement(sql);
        if( statement != nullptr ) {
            result = statement->execute();
            if( result != nullptr && result->hasNext() ) {
                row = result->next();
                id = static_cast<std::size_t>(
                        std::stoull(row->getColumn(0),nullptr,0));
                user = mUsers->get(id);
                if( user != nullptr ) {
                    mUser = user;
                    logi(key + " authenticated.");
                }
                delete row;
            }
            delete result;
            delete statement;
        }
    }
    if( mUser == nullptr )
        loge(key + " could not be authenticated.");
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

    std::cout << "Executing command." << std::endl;
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
    messageSize = static_cast<std::uint16_t>(n);
    messageSize = htons(messageSize);
    writer->writeBytes(reinterpret_cast<const char *>(&b),1);
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

void UserSession::setLoginTimeouts( void ) {
    Socket * socket;
    struct timeval tv;

    tv.tv_sec = 60;
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
                          CommandDispatcher * dispatcher,
                          DatabaseConnection * dbConnection ) :
    Session(socket) {
    initialize();
    setUserContainer(users);
    setDispatcher(dispatcher);
    setDatabaseConnection(dbConnection);
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

    setLoginTimeouts();
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
