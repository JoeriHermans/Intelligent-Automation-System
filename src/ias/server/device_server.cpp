/**
 * A server which is responsible for interacting with devices.
 *
 * @date                    July 7, 2014
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
#include <arpa/inet.h>
#include <cassert>
#include <cstdio>
#include <iostream>

// Application dependencies.
#include <ias/server/device_server.h>
#include <ias/server/session/device_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void DeviceServer::initialize( void ) {
    mSocket = nullptr;
    mListenThread = nullptr;
    mDispatchThread = nullptr;
    mFlagRunning = true;
}

void DeviceServer::setSocket( Socket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr && socket->isConnected() );

    mSocket = socket;
}

void DeviceServer::setDeviceIdentifiers( const std::vector<std::string> & i ) {
    mDeviceIdentifiers = i;
}

void DeviceServer::startListenThread( void ) {
    mListenThread = new std::thread([this](){
        ServerSocket * serverSocket;
        Session * session;
        Socket * socket;

        serverSocket = getServerSocket();
        while( mFlagRunning && mSocket->isConnected() ) {
            socket = serverSocket->acceptSocket(1);
            if( socket != nullptr ) {
                logi("Starting new device session.");
                session = new DeviceSession(socket,
                                            mSocket,
                                            &mConnectedDevices,
                                            &mDeviceIdentifiers);
                session->addObserver(this);
                mSessions[session] =
                    new std::thread([session]{
                        session->run();
                        session->notifyObservers(session);
                        delete session;
                        logi("Device session terminated.");
                    });
            } else if( !serverSocket->isBound() ) {
                stop();
            }
            cleanupFinishingThreads();
        }
        signalSessions();
        mSocket->closeConnection();
        while( mSessions.size() > 0 ||
               mInactiveThreads.size() > 0 ) {
            signalSessions();
            cleanupFinishingThreads();
        }
    });
}

bool DeviceServer::readBytes( char * buffer , const unsigned int n ) {
    std::size_t bytesRead;
    std::size_t nBytes;
    Reader * reader;

    // Checking the precondition.
    assert( buffer != nullptr && n > 0 );

    if( !mSocket->isConnected() ) return ( false );

    reader = mSocket->getReader();
    bytesRead = 0;
    while( bytesRead != n ) {
        nBytes = reader->readBytes(buffer + bytesRead,n - bytesRead);
        if( nBytes == 0 )
            return ( false );
        bytesRead += nBytes;
    }

    return ( true );
}

void DeviceServer::dispatchCommand( void ) {
    std::uint8_t deviceLength;
    std::uint8_t identifierLength;
    std::uint8_t parameterLength;
    std::string message;

    if( !mSocket->isConnected() )
        stop();
    if( !readBytes(reinterpret_cast<char *>(&deviceLength),1) ) return;
    if( !readBytes(reinterpret_cast<char *>(&identifierLength),1) ) return;
    if( !readBytes(reinterpret_cast<char *>(&parameterLength),1) ) return;
    char deviceIdentifier[deviceLength + 1];
    char identifier[identifierLength + 1];
    char parameter[parameterLength + 1];
    if( !readBytes(deviceIdentifier,deviceLength) ) return;
    if( !readBytes(identifier,identifierLength) ) return;
    if( parameterLength > 0 && !readBytes(parameter,parameterLength) ) return;
    deviceIdentifier[deviceLength] = 0;
    identifier[identifierLength] = 0;
    parameter[parameterLength] = 0;
    // Format the message
    message += 0x01;
    message += identifierLength;
    message += parameterLength;
    message.append(identifier);
    message.append(parameter);
    mConnectedDevices.dispatch(deviceIdentifier,message);
}

void DeviceServer::startDispatchThread( void ) {
    mDispatchThread = new std::thread([this](){
        std::size_t nBytes;
        std::uint8_t type;
        Reader * reader;

        setServerTimeouts();
        reader = mSocket->getReader();
        while( mFlagRunning && mSocket->isConnected() ) {
            nBytes = reader->readByte(reinterpret_cast<char *>(&type));
            if( nBytes == 0 && !serverHeartbeat() ) {
                stop();
            } else {
                switch(type) {
                case 0x00:
                    serverHeartbeat();
                    break;
                case 0x01:
                    dispatchCommand();
                    break;
                default:
                    stop();
                    break;
                }
            }
        }
        stop();
    });
}

void DeviceServer::signalSessions( void ) {
    std::map<Session *,std::thread *>::iterator it;

    mMutexSessions.lock();
    for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
        it->first->stop();
    mMutexSessions.unlock();
}

void DeviceServer::cleanupFinishingThreads( void ) {
    std::thread * t;

    while( mInactiveThreads.size() > 0 ) {
        t = mInactiveThreads.front();
        if( t != nullptr ) {
            t->join();
            delete t;
        }
        mInactiveThreads.erase(mInactiveThreads.begin());
    }
}

bool DeviceServer::serverHeartbeat( void ) {
    static const char beat = 0x00;
    Writer * writer;
    bool ok;

    writer = mSocket->getWriter();
    ok = (writer->writeByte(beat) == 1);

    return ( ok );
}

void DeviceServer::setServerTimeouts( void ) {
    struct timeval tv;

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    mSocket->setSendTimeout(tv);
    mSocket->setReceiveTimeout(tv);
}

DeviceServer::DeviceServer( ServerSocket * serverSocket,
                            Socket * socket,
                            const std::vector<std::string> & devices ) :
    Server(serverSocket) {
    initialize();
    setSocket(socket);
    setDeviceIdentifiers(devices);
}

DeviceServer::~DeviceServer( void ) {
    join();
}

void DeviceServer::start( void ) {
    if( mListenThread == nullptr && mDispatchThread == nullptr ) {
        startListenThread();
        startDispatchThread();
    }
}

void DeviceServer::stop( void ) {
    mFlagRunning = false;
    mSocket->closeConnection();
    getServerSocket()->stopListening();
}

void DeviceServer::join( void ) {
    if( mListenThread != nullptr ) {
        mListenThread->join();
        delete mListenThread;
        mListenThread = nullptr;
    }
    if( mDispatchThread != nullptr ) {
        mDispatchThread->join();
        delete mDispatchThread;
        mDispatchThread = nullptr;
    }
}

void DeviceServer::update( void ) {
    // Do nothing.
}

void DeviceServer::update( void * argument ) {
    std::map<Session *,std::thread *>::iterator it;
    Session * session;

    // Checking the precondition.
    assert( argument != nullptr );

    session = static_cast<Session *>(argument);
    it = mSessions.find(session);
    if( it != mSessions.end() ) {
        mInactiveThreads.push_back(it->second);
        mMutexSessions.lock();
        mSessions.erase(it);
        mMutexSessions.unlock();
    }
}
