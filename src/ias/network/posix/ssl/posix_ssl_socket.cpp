/**
 * A class which describes the properties and actions of an SSL socket.
 *
 * @date                    August 21, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <poll.h>
#include <netdb.h>
#include <errno.h>

// Application dependencies.
#include <ias/io/reader/network/ssl/ssl_reader.h>
#include <ias/io/writer/network/ssl/ssl_writer.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>

// END Includes. /////////////////////////////////////////////////////

inline void PosixSslSocket::initialize( void ) {
    mSsl = nullptr;
    mReader = nullptr;
    mWriter = nullptr;
}

void PosixSslSocket::setSslEnvironment( SSL * ssl ) {
    // Checking the precondition.
    assert( ssl != nullptr );

    mSsl = ssl;
}

bool PosixSslSocket::initializeConnection( const std::string & address,
                                           const unsigned int port ) {
    struct addrinfo hints;
    struct addrinfo * results;
    std::string portString;
    bool connected;
    int fd;

    // Checking the precondition.
    assert( !address.empty() && port > 0 );

    connected = false;
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    portString = std::to_string(port);
    getaddrinfo(address.c_str(),portString.c_str(),&hints,&results);
    fd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
    if( fd >= 0 ) {
        if( connect(fd,results->ai_addr,results->ai_addrlen) == 0 ) {
            connected = true;
            // TODO Set SSL socket.
            // Free old reader and writer.
            delete mReader; mReader = nullptr;
            delete mWriter; mWriter = nullptr;
            // Allocate reader and writer.
            // TODO Allocate reader and writer.
        } else {
            close(fd);
        }
    }
    freeaddrinfo(results);

    return ( connected );
}

PosixSslSocket::PosixSslSocket( void ) {
    initialize();
}

PosixSslSocket::PosixSslSocket( SSL * ssl ) {
    initialize();
    setSslEnvironment(ssl);
}

PosixSslSocket::~PosixSslSocket( void ) {
    closeConnection();
    delete mReader; mReader = nullptr;
    delete mWriter; mWriter = nullptr;
}

void PosixSslSocket::closeConnection( void ) {
    if( isConnected() ) {
        SSL_free(mSsl);
        close(SSL_get_fd(mSsl));
        mSsl = nullptr;
    }
}

bool PosixSslSocket::createConnection( const std::string & address,
                                       const unsigned int port ) {
    // TODO Implement initializeConnection(address,port).

    return ( false );
}

bool PosixSslSocket::isConnected( void ) const {
    return ( mSsl != nullptr );
}

Reader * PosixSslSocket::getReader( void ) const {
    return ( mReader );
}

Writer * PosixSslSocket::getWriter( void ) const {
    return ( mWriter );
}
