/**
 * A class which represents the properties and actions of a POSIX TCP socket.
 *
 * @date                    July 6, 2014
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
#include <ias/io/reader/network/posix/posix_tcp_socket_reader.h>
#include <ias/io/writer/network/posix/posix_tcp_socket_writer.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/util.h>

// END Includes. /////////////////////////////////////////////////////

inline void PosixTcpSocket::initialize( void ) {
    setFileDescriptor(-1);
    mReader = nullptr;
    mWriter = nullptr;
}

void PosixTcpSocket::setFileDescriptor( const int fd ) {
    // Checking the precondition.
    assert( fd >= -1 );

    mFileDescriptor = fd;
}

bool PosixTcpSocket::initializeConnection( const std::string & address,
                                           const std::size_t port ) {
    bool connected;
    int fd;

    fd = connect(address,port);
    if( fd >= 0 ) {
        mFileDescriptor = fd;
        enableKeepAlive(fd);
        disableNagle(fd);
        connected = true;
        delete mReader; mReader = nullptr;
        delete mWriter; mWriter = nullptr;
        mReader = new PosixTcpSocketReader(this);
        mWriter = new PosixTcpSocketWriter(this);
    } else {
        connected = false;
    }

    return ( connected );
}

void PosixTcpSocket::pollSocket( void ) const {
    struct pollfd pfd;

    if( mFileDescriptor >= 0 ) {
        pfd.fd = mFileDescriptor;
        #if defined(__linux__)
        pfd.events = POLLNVAL | POLLHUP | POLLRDHUP;
        #else
        pfd.events = POLLNVAL | POLLHUP;
        #endif
        pfd.revents = 0;
        if( poll(&pfd,1,0) >= 1 ) {
            close(mFileDescriptor);
            mFileDescriptor = -1;
        }
    }
}

PosixTcpSocket::PosixTcpSocket( void ) {
    initialize();
}

PosixTcpSocket::PosixTcpSocket( const int fd ) {
    setFileDescriptor(fd);
    // Allocate reader and writer.
    mReader = new PosixTcpSocketReader(this);
    mWriter = new PosixTcpSocketWriter(this);
}

PosixTcpSocket::~PosixTcpSocket( void ) {
    closeConnection();
    delete mReader; mReader = nullptr;
    delete mWriter; mWriter = nullptr;
}

void PosixTcpSocket::closeConnection( void ) {
    if( isConnected() )
        close(mFileDescriptor);
    setFileDescriptor(-1);
}

bool PosixTcpSocket::createConnection( const std::string & address,
                                       const std::size_t port ) {
    closeConnection();

    return ( initializeConnection(address,port) );
}

bool PosixTcpSocket::isConnected( void ) const {
    pollSocket();

    return ( mFileDescriptor >= 0 );
}

Reader * PosixTcpSocket::getReader( void ) const {
    return ( mReader );
}

Writer * PosixTcpSocket::getWriter( void ) const {
    return ( mWriter );
}

int PosixTcpSocket::getFileDescriptor( void ) const {
    return ( mFileDescriptor );
}
