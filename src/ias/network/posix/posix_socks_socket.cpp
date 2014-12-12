/**
 * A class which describes the properties and actions of a POSIX SOCKS
 * proxy socket. This socket will connect to a remote SOCKS proxy server.
 *
 * Please note that this class only allows outgoing connections to the proxy
 * server.
 *
 * Implementation according to RFC 1928 (https://www.ietf.org/rfc/rfc1928.txt).
 *
 * @date                    December 12, 2014
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
#include <iostream>

// Application dependencies.
#include <ias/network/posix/posix_socks_socket.h>

// END Includes. /////////////////////////////////////////////////////

inline void PosixSocksSocket::initialize( void ) {
    mFileDescriptor = -1;
    mReader = nullptr;
    mWriter = nullptr;
}

void PosixSocksSocket::setFileDescriptor( const int fd ) {
    mFileDescriptor = fd;
}

void PosixSocksSocket::setClientAddress( const std::string & clientAddress,
                                         const std::size_t clientPort ) {
    // Checking the precondition.
    assert( clientAddress.length() > 0 && clientPort > 0 );

    mClientAddress = clientAddress;
    mClientPort = clientPort;
}

void PosixSocksSocket::setProxyAddress( const std::string & proxyAddress,
                                        const std::size_t proxyPort ) {
    // Checking the precondition.
    assert( proxyAddress.length() > 0 && proxyPort > 0 );

    mProxyAddress = proxyAddress;
    mProxyPort = proxyPort;
}

void PosixSocksSocket::setCredentials( const std::string & username,
                                       const std::string & password ) {
    mUsername = username;
    mPassword = password;
}

void PosixSocksSocket::pollSocket( void ) const {
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

void PosixSocksSocket::resetReaderAndWriter( void ) {
    delete mReader; mReader = nullptr;
    delete mWriter; mWriter = nullptr;
}

bool PosixSocksSocket::initializeConnection( void ) {
    struct addrinfo hints;
    struct addrinfo * results;
    std::string portString;
    bool connected;
    int fd;

    // Checking the precondition.
    assert( !mProxyAddress.empty() && mProxyPort > 0 );

    connected = false;
    memset(&hints,0,sizeof hints);
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;
    portString = std::to_string(mProxyPort);
    getaddrinfo(mProxyAddress.c_str(),portString.c_str(),&hints,&results);
    fd = socket(results->ai_family,results->ai_socktype,results->ai_protocol);
    if( fd >= 0 ) {
        if( connect(fd,results->ai_addr,results->ai_addrlen) == 0) {
            connected = true;
            setFileDescriptor(fd);
            //resetReaderAndWriter();
            // TODO Allocate and set reader and writer.
        } else {
            close(fd);
        }
    }
    freeaddrinfo(results);

    return ( connected );
}

bool PosixSocksSocket::negotiate( void ) {
    std::uint8_t message[4];
    std::uint8_t response[2];
    std::uint8_t version;
    std::uint8_t method;
    bool connected;

    // Checking the precondition.
    assert( mFileDescriptor >= 0 );

    connected = false;
    // Prepare the message for the SOCKS proxy.
    message[0] = kProtocolVersion;
    message[1] = 2; // Number of methods supplied.
    message[2] = kMethodNoAuthentication;
    message[3] = kMethodUsernamePassword;
    // Send message to server.
    write(mFileDescriptor,static_cast<unsigned char *>(message),4);
    // Read the response from the server.
    read(mFileDescriptor,static_cast<unsigned char *>(response),2);
    version = response[0];
    method = response[1];
    if( version == kProtocolVersion ) {
        switch(method) {
        case 0:
            connected = true;
            break;
        case kMethodUsernamePassword:
            connected = authenticate();
            break;
        }
    }

    return ( connected );
}

bool PosixSocksSocket::authenticate( void ) {
    bool connected;

    // TODO Implement.
    std::cout << "Authenticating." << std::endl;
    connected = false;

    return ( connected );
}

PosixSocksSocket::PosixSocksSocket( const std::string & proxyAddress,
                                    const std::size_t proxyPort ) {
    initialize();
    setProxyAddress(proxyAddress,proxyPort);
}

PosixSocksSocket::PosixSocksSocket( const std::string & proxyAddress,
                                    const std::size_t proxyPort,
                                    const std::string & username,
                                    const std::string & password ) {
    initialize();
    setProxyAddress(proxyAddress,proxyPort);
    setCredentials(username,password);
}

PosixSocksSocket::~PosixSocksSocket( void ) {
    closeConnection();
    resetReaderAndWriter();
}

void PosixSocksSocket::closeConnection( void ) {
    if( isConnected() )
        closeConnection();
    setFileDescriptor(-1);
}

bool PosixSocksSocket::createConnection( const std::string & address,
                                         const std::size_t port ) {
    bool connected;

    setClientAddress(address,port);
    if( initializeConnection() )
        connected = negotiate();
    else
        connected = false;

    return ( connected );
}

bool PosixSocksSocket::isConnected( void ) const {
    pollSocket();

    return ( mFileDescriptor );
}

Reader * PosixSocksSocket::getReader( void ) const {
    return ( mReader );
}

Writer * PosixSocksSocket::getWriter( void ) const {
    return ( mWriter );
}
