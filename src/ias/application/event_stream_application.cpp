/**
 * An application which outputs the raw event stream data from the IAS server to
 * std::cout.
 *
 * @date                    18 January, 2015
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
#include <cstring>
#include <string>
#include <unistd.h>
#include <cstdio>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/event_stream_application.h>
#include <ias/network/util.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/util/util.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventStreamApplication::initialize( void ) {
    mSocket = nullptr;
    mSslContext = nullptr;
    mFlagRunning = true;
    mServicePort = kDefaultEventServerPort;
    mFlagSslRequested = false;
}

void EventStreamApplication::analyzeArguments( const int argc,
                                               const char ** argv ) {
    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    fetchServiceAddress(argc,argv);
    fetchSslRequested(argc,argv);
    fetchApiKey(argc,argv);
}

void EventStreamApplication::fetchServiceAddress( const int argc,
                                                  const char ** argv ) {
    std::string stringPort;

    // Fetch the specified address.
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagAddress) == 0 && (i + 1) < argc ) {
            mServiceAddress = std::string(argv[i + 1]);
            break;
        }
    }
    // Fetch the specified port.
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagPort) == 0 && (i + 1) < argc ) {
            stringPort = std::string(argv[i + 1]);
            break;
        }
    }
    // Parse port, if specified.
    if( !stringPort.empty() && isNumber(stringPort) ) {
        std::size_t port;

        port = strtoul(stringPort.c_str(),nullptr,0);
        if( port > 0 )
            mServicePort = port;
    }
}

void EventStreamApplication::fetchSslRequested( const int argc,
                                                const char ** argv ) {
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagSsl) == 0 ) {
            mFlagSslRequested = true;
            break;
        }
    }
}

void EventStreamApplication::fetchApiKey( const int argc,
                                          const char ** argv ) {
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagKey) == 0 && (i + 1) < argc ) {
            mApiKey = std::string(argv[i + 1]);
            break;
        }
    }
}

void EventStreamApplication::authorize( void ) {
    std::uint8_t header[2];
    std::size_t n;
    Writer * writer;
    Reader * reader;

    // Checking the precondition.
    assert( mSocket != nullptr && mSocket->isConnected() &&
            !mApiKey.empty() && mApiKey.length() <= 0xff );

    logi("Authorizing.");
    header[0] = 0x01;
    header[1] = static_cast<std::uint8_t>(mApiKey.length());
    writer = mSocket->getWriter();
    reader = mSocket->getReader();
    writer->writeBytes(reinterpret_cast<const char *>(header),2);
    writer->writeBytes(mApiKey.c_str(),mApiKey.length());
    n = reader->readBytes(reinterpret_cast<char *>(header),2);
    if( n != 2 && !(header[0] == 0x00 && header[1] == 0x01) ) {
        loge("Authorization failed.");
        mFlagRunning = false;
        mSocket->closeConnection();
    } else {
        logi("Authorized.");
    }
}

void EventStreamApplication::connectToStream( void ) {
    int fd;

    // Checking the precondition.
    assert( !mServiceAddress.empty() && mServicePort > 0 );

    logi("Connecting to " + mServiceAddress);
    fd = connect(mServiceAddress,mServicePort);
    if( fd >= 0 ) {
        if( mFlagSslRequested ) {
            SSL * ssl;

            initializeSslContext();
            ssl = SSL_new(mSslContext);
            SSL_set_fd(ssl,fd);
            if( SSL_connect(ssl) <= 0 ) {
                SSL_free(ssl);
                close(fd);
            } else {
                mSocket = new PosixSslSocket(ssl);
            }
        } else {
            mSocket = new PosixTcpSocket(fd);
        }
    }
    if( mSocket == nullptr ) {
        loge("Connection failed.");
        mFlagRunning = false;
    } else {
        logi("Connected.");
    }
}

void EventStreamApplication::initializeSslContext( void ) {
    mSslContext = SSL_CTX_new(SSLv23_client_method());
}

void EventStreamApplication::sendHeartbeat( void ) {
    static const std::uint8_t beat = 0x00;
    Writer * writer;

    // Checking the precondition.
    assert( mSocket->isConnected() );

    writer = mSocket->getWriter();
    writer->writeBytes(reinterpret_cast<const char *>(&beat),1);
}

void EventStreamApplication::readEvent( void ) {
    std::uint8_t size;
    Reader * reader;

    size = 0x00;
    reader = mSocket->getReader();
    reader->readBytes(reinterpret_cast<char *>(&size),1);
    if( size > 0 ) {
        char buffer[size + 1];
        buffer[size] = 0;
        reader->readBytes(buffer,static_cast<std::size_t>(size));
        puts(buffer);
    }
}

EventStreamApplication::EventStreamApplication( const int argc,
                                                const char ** argv ) {
    initialize();
    analyzeArguments(argc,argv);
}

EventStreamApplication::~EventStreamApplication( void ) {
    delete mSocket; mSocket = nullptr;
    if( mSslContext != nullptr ) {
        SSL_CTX_free(mSslContext);
        mSslContext = nullptr;
    }
}

void EventStreamApplication::run( void ) {
    std::uint8_t type;
    std::size_t nBytes;
    Reader * reader;

    connectToStream();
    if( mFlagRunning && mSocket != nullptr && mSocket->isConnected() )
        authorize();
    if( mFlagRunning ) {
        reader = mSocket->getReader();
        while( mFlagRunning && mSocket->isConnected() ) {
            type = 0xff;
            nBytes = reader->readBytes(reinterpret_cast<char *>(&type),1);
            if( nBytes > 0 ) {
                switch(type) {
                case 0x00:
                    sendHeartbeat();
                    break;
                case 0x01:
                    readEvent();
                    break;
                }
            } else {
                mSocket->closeConnection();
            }
        }
    }
    logi("Closing connection.");
}

void EventStreamApplication::stop( void ) {
    mFlagRunning = false;
}
