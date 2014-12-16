/**
 * A class which describes the actions and properties of a TPC server socket.
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
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

// Application dependencies.
#include <ias/network/posix/posix_tcp_server_socket.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/util.h>

// END Includes. /////////////////////////////////////////////////////

void PosixTcpServerSocket::setFileDescriptor( const int fd ) {
    mFileDescriptor = fd;
}

PosixTcpServerSocket::PosixTcpServerSocket( const unsigned int port ) :
    ServerSocket(port) {
    setFileDescriptor(-1);
}

PosixTcpServerSocket::~PosixTcpServerSocket( void ) {
    stopListening();
}

void PosixTcpServerSocket::stopListening( void ) {
    if( isBound() ) {
        close(mFileDescriptor);
        setFileDescriptor(-1);
    }
}

bool PosixTcpServerSocket::bindToPort( void ) {
    struct addrinfo hints;
    struct addrinfo * serverInfo;
    std::string portString;
    bool bound;
    int fd;

    if( isBound() ) {
        bound = true;
    } else {
        bound = false;
        memset(&hints,0,sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        portString = std::to_string(getPort());
        if( getaddrinfo(nullptr,portString.c_str(),&hints,&serverInfo) == 0 ) {
            fd = socket(serverInfo->ai_family,serverInfo->ai_socktype,
                        serverInfo->ai_protocol);
            if( fd >= 0 ) {
                int yes = 1;

                setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes);
                if( bind(fd,serverInfo->ai_addr,serverInfo->ai_addrlen) == 0 &&
                    listen(fd,20) == 0 ) {
                    bound = true;
                    FD_ZERO(&mRfds);
                    FD_SET(fd,&mRfds);
                    setFileDescriptor(fd);
                    enableKeepAlive(fd);
                    disableNagle(fd);
                }
            }
            freeaddrinfo(serverInfo);
        }
    }

    return ( bound );
}

bool PosixTcpServerSocket::isBound( void ) const {
    return ( mFileDescriptor >= 0 );
}

Socket * PosixTcpServerSocket::acceptSocket( void ) {
    struct sockaddr addr;
    socklen_t addrLength;
    Socket * socket;
    int fd;

    socket = nullptr;
    if( isBound() ) {
        memset(&addr,0,sizeof addr);
        memset(&addrLength,0,sizeof addrLength);
        fd = accept(mFileDescriptor,&addr,&addrLength);
        if( fd >= 0 ) {
            enableKeepAlive(fd);
            disableNagle(fd);
            socket = new PosixTcpSocket(fd);
        }
    }

    return ( socket );
}

Socket * PosixTcpServerSocket::acceptSocket( const std::time_t seconds ) {
    struct sockaddr addr;
    socklen_t addrLength;
    timeval tv;
    Socket * socket;
    int fd;

    socket = nullptr;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    FD_ZERO(&mRfds);
    FD_SET(mFileDescriptor,&mRfds);
    if( isBound() &&
        select(mFileDescriptor + 1,&mRfds,nullptr,nullptr,&tv) > 0 ) {
        memset(&addr,0,sizeof addr);
        memset(&addrLength,0,sizeof addrLength);
        fd = accept(mFileDescriptor,&addr,&addrLength);
        if( fd >= 0 ) {
            enableKeepAlive(fd);
            disableNagle(fd);
            socket = new PosixTcpSocket(fd);
        }
    }

    return ( socket );
}
