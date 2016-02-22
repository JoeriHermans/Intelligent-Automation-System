/**
 * A class which describes the actions and properties of an event session. This
 * session will notify the connected endpoint of server events (like device
 * updates, e.d.). This way, we can prevent polling.
 *
 * @date                    17 January, 2015
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
#include <ias/server/session/event_session.h>
#include <ias/logger/logger.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventSession::initialize( void ) {
    mDbConnection = nullptr;
    mEventDispatcher = nullptr;
    mChannel = nullptr;
    mFlagRunning = true;
}

void EventSession::setDatabaseConnection( DatabaseConnection * connection ) {
    // Checking the precondition.
    assert( connection != nullptr );

    mDbConnection = connection;
}

void EventSession::setEventDispatcher( EventDispatcher * eventDispatcher ) {
    // Checking the precondition.
    assert( eventDispatcher != nullptr );

    mEventDispatcher = eventDispatcher;
}

void EventSession::setAuthenticationTimeouts( void ) {
    struct timeval tv;
    Socket * socket;

    tv.tv_sec = 60;
    tv.tv_usec = 0;
    socket = getSocket();
    socket->setReceiveTimeout(tv);
}

void EventSession::setTimeouts( void ) {
    struct timeval tv;
    Socket * socket;

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    socket = getSocket();
    socket->setReceiveTimeout(tv);
}

void EventSession::authorize( void ) {
    std::uint8_t type = 0xff;

    logi("Authorizing event stream.");
    if( readBytes(reinterpret_cast<char *>(&type),1) ) {
        switch(type) {
        case 0x01:
            authorizeApiKey();
            break;
        default:
            mFlagRunning = false;
            break;
        }
    }
    if( !mFlagRunning ) {
        loge("Could not authenticate event stream.");
        getSocket()->closeConnection();
    } else {
        std::uint8_t code[2];
        Writer * w;

        // Send authorization byte.
        w = getSocket()->getWriter();
        code[0] = 0x00;
        code[1] = 0x01;
        w->writeBytes(reinterpret_cast<char *>(&code),2);
        setEventChannel();
    }
}

void EventSession::authorizeApiKey( void ) {
    std::uint8_t length;
    std::string hashedKey;

    logi("Authorizing event stream using API key.");
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

void EventSession::validateApiKey( const std::string & key ) {
    DatabaseStatement * statement;
    DatabaseResult * result;

    // Checking the precondition.
    assert( key.length() > 0 );

    if( mDbConnection->isConnected() && key.length() == 64 ) {
        // Query is safe, because it has been hashed.
        std::string sql = "SELECT user_id, expires "
                          "FROM api_keys "
                          "WHERE api_keys.key = '" + key + "' "
                          "AND api_keys.expires <= NOW() "
                          "OR api_keys.key = '" + key + "' "
                          "AND api_keys.expires = 0;";
        statement = mDbConnection->createStatement(sql);
        if( statement != nullptr ) {
            result = statement->execute();
            if( result == nullptr || !result->hasNext() ) {
                mFlagRunning = false;
                loge("Event stream could not be authenticated.");
            } else {
                logi("Event stream has been authenticated.");
            }
            delete result;
            delete statement;
        }
    }
}

bool EventSession::heartbeat( void ) {
    static const char beat = 0x00;
    Writer * writer;
    bool ok;

    writer = getSocket()->getWriter();
    ok = (writer->writeByte(beat) == 1);

    return ( ok );
}

void EventSession::setEventChannel( void ) {
    // Checking the precondition.
    assert( getSocket() != nullptr );

    mChannel = new EventChannel(getSocket());
    mEventDispatcher->addChannel(mChannel);
}

EventSession::EventSession( Socket * socket, DatabaseConnection * connection,
                            EventDispatcher * eventDispatcher ) :
    Session(socket) {
    initialize();
    setDatabaseConnection(connection);
    setEventDispatcher(eventDispatcher);
}

EventSession::~EventSession( void ) {
    if( mChannel != nullptr ) {
        mEventDispatcher->removeChannel(mChannel);
        delete mChannel; mChannel = nullptr;
    }
}

void EventSession::run( void ) {
    bool heartbeatSend = false;
    std::uint8_t type;
    std::size_t nBytes;
    Socket * socket;
    Reader * reader;

    setAuthenticationTimeouts();
    authorize();
    if( mFlagRunning ) {
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
            default:
                stop();
                break;
            }
            heartbeatSend = false;
        }
    }
}

void EventSession::stop( void ) {
    if( mFlagRunning ) {
        logi("Closing event stream session.");
        mFlagRunning = false;
    }
}
