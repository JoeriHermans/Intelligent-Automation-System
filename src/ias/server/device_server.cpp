/**
 * A server which is responsible for interacting with devices.
 *
 * @date					July 7, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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
                    });
            } else if( !serverSocket->isBound() ) {
                stop();
            }
            cleanupFinishingThreads();
        }
        signalSessions();
        mSocket->closeConnection();
        while( mSessions.size() > 0 ||
               mInactiveThreads.size() > 0 )
            cleanupFinishingThreads();
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
    Reader * reader;
    Writer * writer;
    
    if( !mSocket->isConnected() )
        stop();
    reader = mSocket->getReader();
    writer = mSocket->getWriter();
    if( !readBytes((char *) &deviceLength,1) ) return;
    if( !readBytes((char *) &identifierLength,1) ) return;
    if( !readBytes((char *) &parameterLength,1) ) return;
    char deviceIdentifier[deviceLength + 1];
    char identifier[identifierLength + 1];
    char parameter[parameterLength + 1];
    if( !readBytes(deviceIdentifier,deviceLength) ) return;
    if( !readBytes(identifier,identifierLength) ) return;
    if( !readBytes(parameter,parameterLength) ) return;
    deviceIdentifier[deviceLength] = 0;
    identifier[identifierLength] = 0;
    parameter[parameterLength] = 0;
    // Format the message
    // TODO I have a fealing std::string handles this the wrong way.
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
        
        reader = mSocket->getReader();
        while( mFlagRunning && mSocket->isConnected() ) {
            nBytes = reader->readByte((char *) &type);
            if( nBytes == 0 ) { 
                stop();
            } else {
                switch(type) {
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
    
    session = (Session *) argument;
    it = mSessions.find(session);
    if( it != mSessions.end() ) {
        mInactiveThreads.push_back(it->second);
        mMutexSessions.lock();
        mSessions.erase(it);
        mMutexSessions.unlock();
    }
}
