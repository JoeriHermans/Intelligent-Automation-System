/**
 * A set of network utility functions.
 *
 * @date                    December 13, 2014
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
#include <netinet/tcp.h>
#include <iostream>
#include <poll.h>
#include <netdb.h>
#include <errno.h>

// System dependencies.
#include <ias/network/util.h>

// END Includes. /////////////////////////////////////////////////////

int connect( const std::string & address, const std::size_t port ) {
    struct addrinfo hints;
    struct addrinfo * results;
    std::string portString;
    int result;
    int fd;

    // Checking the precondition.
    assert( !address.empty() && port > 0 );

    result = -1;
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    portString = std::to_string(port);
    getaddrinfo(address.c_str(),portString.c_str(),&hints,&results);
    if( results != nullptr ) {
        fd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
        if( fd >= 0 ) {
            if( connect(fd,results->ai_addr,results->ai_addrlen) == 0 )
                result = fd;
            else
                close(fd);
        }
        freeaddrinfo(results);
    }

    return ( result );
}

bool enableKeepAlive( const int fd ) {
    static const int optval = 1;
    bool s;

    // Checking the precondition.
    assert( fd >= 0 );

    s = (setsockopt(fd,SOL_SOCKET,SO_KEEPALIVE,&optval,sizeof optval) >= 0);

    return ( s );
}

bool disableNagle( const int fd ) {
    static const int optval = 1;
    bool s;

    // Checking the precondition.
    assert( fd >= 0 );

    s = (setsockopt(fd,IPPROTO_TCP,TCP_NODELAY,&optval,sizeof optval) >= 0);

    return (s);
}
