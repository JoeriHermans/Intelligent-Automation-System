/**
 * A class which describes the properties and actions of a device session.
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
#include <cassert>
#include <cstring>
#include <iostream>

// Application dependencies.
#include <ias/channel/device_channel.h>
#include <ias/server/session/device_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void DeviceSession::initialize( void ) {
    mDispatcher = nullptr;
    mFlagRunning = false;
}

void DeviceSession::setDispatcher( Dispatcher<const std::string &> * d ) {
    // Checking the precondition.
    assert( d != nullptr );

    mDispatcher = d;
}

void DeviceSession::authorize( void ) {
    std::uint8_t type;
    std::uint8_t deviceIdentifier;

    logi("Authorizing device.");
    if( !readBytes(reinterpret_cast<char *>(&type),1) ) return;
    if( type == 0x00 && readBytes(reinterpret_cast<char *>(&deviceIdentifier),1) ) {
        char identifier[deviceIdentifier + 1];
        if( !readBytes(identifier,deviceIdentifier) ) return;
        identifier[deviceIdentifier] = 0;
        if( strlen(identifier) > 0 && containsDevice(identifier) &&
            !mDispatcher->containsChannel(identifier) ) {
            mFlagRunning = true;
            mDevice = identifier;
            mDispatcher->addChannel(identifier,new DeviceChannel(getSocket()));
            logi(mDevice + " has been authorized.");
        } else {
            stop();
        }
    }
    if( !mFlagRunning )
        loge("Device authorization failed.");
}

void DeviceSession::setDevices( const std::vector<std::string> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

bool DeviceSession::containsDevice( const std::string & identifier ) const {
    bool contains;

    contains = false;
    for( auto it = mDevices->begin() ; it != mDevices->end() ; ++it ) {
        if( (*it) == identifier ) {
            contains = true;
            break;
        }
    }

    return ( contains );
}

void DeviceSession::updateDeviceState( void ) {
    std::uint8_t length[2];

    memset(&length,0,2);
    if( !readBytes(reinterpret_cast<char *>(length),2) ) return;
    char buffer[length[0] + length[1]];
    if( !readBytes(buffer,length[0] + length[1]) ) return;
    char stateIdentifier[length[0] + 1];
    char value[length[1] + 1];
    memcpy(stateIdentifier,buffer,length[0]);
    memcpy(value,buffer + length[0],length[1]);
    stateIdentifier[length[0]] = 0;
    value[length[1]] = 0;
    sendDeviceState(stateIdentifier,value);
}

void DeviceSession::sendDeviceState( const std::string & stateIdentifier,
                                     const std::string & value ) {
    std::uint8_t header[4];
    std::string message;
    std::size_t n;
    Writer * writer;
    bool success;

    // Checking the precondition.
    assert( !stateIdentifier.empty() && !value.empty() );

    header[0] = 0x01;
    header[1] = static_cast<std::uint8_t>(mDevice.length());
    header[2] = static_cast<std::uint8_t>(stateIdentifier.length());
    header[3] = static_cast<std::uint8_t>(value.length());
    message = mDevice + stateIdentifier + value;
    writer = mServerSocket->getWriter();
    success = true;
    writer->lock();
    n = writer->writeBytes(reinterpret_cast<char *>(header),4);
    success &= ( n > 0 );
    n = writer->writeBytes(reinterpret_cast<const char *>(message.c_str()),
                           message.length());
    success &= ( n > 0 );
    writer->unlock();
    if( !success ) {
        stop();
    }
}

void DeviceSession::setServerSocket( Socket * serverSocket ) {
    // Checking the precondition.
    assert( serverSocket != nullptr );

    mServerSocket = serverSocket;
}

DeviceSession::DeviceSession( Socket * socket,
                              Socket * serverSocket,
                              Dispatcher<const std::string &> * d,
                              const std::vector<std::string> * devices ) :
    Session(socket) {
    initialize();
    setDispatcher(d);
    setServerSocket(serverSocket);
    setDevices(devices);
}

DeviceSession::~DeviceSession( void ) {
    stop();
}

void DeviceSession::run( void ) {
    std::uint8_t type;
    std::size_t nBytes;
    Reader * reader;

    authorize();
    if( getSocket()->isConnected() ) {
        reader = getSocket()->getReader();
        while( mFlagRunning && mServerSocket->isConnected() &&
               getSocket()->isConnected() ) {
            nBytes = reader->readByte(reinterpret_cast<char *>(&type));
            if( nBytes == 0 ) {
                stop();
            } else {
                switch(type) {
                case 0x01:
                    updateDeviceState();
                    break;
                default:
                    stop();
                    break;
                }
            }
        }
    }
    if( !mDevice.empty() )
        mDispatcher->removeChannel(mDevice);
    getSocket()->closeConnection();
}

void DeviceSession::stop( void ) {
    const static std::uint8_t close = 0xff;
    Socket * socket;
    Writer * writer;

    if( mFlagRunning ) {
        logi("Closing device session.");
        mFlagRunning = false;
        socket = getSocket();
        if( socket->isConnected() ) {
            writer = getSocket()->getWriter();
            writer->lock();
            writer->writeBytes(reinterpret_cast<const char *>(&close),1);
            writer->unlock();
            socket->closeConnection();
        }
    }
}
