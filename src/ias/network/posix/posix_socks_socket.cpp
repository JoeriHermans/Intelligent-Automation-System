/**
 * A class which describes the properties and actions of a POSIX SOCKS
 * proxy socket. This socket will connect to a remote SOCKS proxy server.
 *
 * Please note that this class only allows outgoing connections to the proxy
 * server.
 *
 * Implementation according to RFC 1928 (https://www.ietf.org/rfc/rfc1928.txt)
 * and RFC 1929 (http://tools.ietf.org/html/rfc1929).
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
#include <ias/io/reader/network/posix/posix_tcp_socket_reader.h>
#include <ias/io/writer/network/posix/posix_tcp_socket_writer.h>

// END Includes. /////////////////////////////////////////////////////

inline void PosixSocksSocket::initialize( void ) {
    mSocket = new PosixTcpSocket();
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
    // Checking the precondition (according to RFC 1929).
    assert( username.length() <= 255 && password.length() <= 255 );

    mUsername = username;
    mPassword = password;
}

bool PosixSocksSocket::initializeConnection( void ) {
    return ( mSocket->createConnection(mProxyAddress,mProxyPort) );
}

bool PosixSocksSocket::negotiate( void ) {
    std::uint8_t message[4];
    std::uint8_t response[2];
    std::uint8_t version;
    std::uint8_t method;
    bool connected;

    // Checking the precondition.
    assert( mSocket->isConnected() );

    connected = false;
    // Prepare the message for the SOCKS proxy.
    message[0] = kProtocolVersion;
    message[1] = 2; // Number of methods supplied.
    message[2] = kMethodNoAuthentication;
    message[3] = kMethodUsernamePassword;
    mSocket->getWriter()->writeBytes(reinterpret_cast<char *>(message),4);
    mSocket->getReader()->readBytes(reinterpret_cast<char *>(response),2);
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
        if( connected )
            connected = request();
    }

    return ( connected );
}

bool PosixSocksSocket::authenticate( void ) {
    // Authentication message layout:
    //  Version: 1 byte
    //  Username length: 1 byte (n)
    //  Username: n bytes
    //  Password length: 1 byte (m)
    //  Password: m bytes.
    std::size_t messageLength = 2 + mUsername.length() + 1 + mPassword.length();
    std::uint8_t message[messageLength];
    std::uint8_t response[2];
    std::size_t messageIndex;
    const char * username;
    const char * password;
    bool connected;

    connected = false;
    message[0] = kVersionAuthenticationMethod;
    message[1] = static_cast<std::uint8_t>(mUsername.length());
    username = mUsername.c_str();
    for( std::size_t i = 0 ; i < mUsername.length() ; ++i )
        message[2 + i] = username[i];
    messageIndex = 2 + mUsername.length();
    message[messageIndex++] = static_cast<std::uint8_t>(mPassword.length());
    password = mPassword.c_str();
    for( std::size_t i = 0 ; i < mPassword.length() ; ++i )
        message[messageIndex + i] = password[i];
    memset(response,0,2);
    mSocket->getWriter()->writeBytes(reinterpret_cast<char *>(message),messageLength);
    mSocket->getReader()->readBytes(reinterpret_cast<char *>(response),2);
    if( response[0] == kVersionAuthenticationMethod && response[1] == 0 )
        connected = true;

    return ( connected );
}

bool PosixSocksSocket::request( void ) {
    // Request message layout.
    // Version: 1 byte
    // Command: 1 byte
    // Reserved: 1 byte (0x00)
    // Address type: 1 byte
    // Destination address: variable length.
    // Destination port: 2 bytes (network order).
    std::size_t messageLength = 5 + mClientAddress.length();
    std::uint8_t message[messageLength];
    std::uint8_t response[BUFSIZ];
    std::uint16_t port;
    Writer * writer;
    const char * address;
    bool connected;

    connected = false;
    message[0] = kProtocolVersion;
    message[1] = 0x01; // Connect.
    message[2] = 0x00;
    message[3] = 0x03; // Domainname.
    message[4] = static_cast<std::uint8_t>(mClientAddress.length());
    address = mClientAddress.c_str();
    for( std::size_t i = 0 ; i < mClientAddress.size() ; ++i )
        message[5 + i] = address[i];
    port = htons(static_cast<std::uint16_t>(mClientPort));
    writer = mSocket->getWriter();
    writer->writeBytes(reinterpret_cast<char *>(message),messageLength);
    writer->writeBytes(reinterpret_cast<char *>(&port),2);
    std::size_t n = mSocket->getReader()->readBytes(
            reinterpret_cast<char *>(response),BUFSIZ);
    // TODO Add error logging.
    if( n >= 2 && response[1] == 0 )
        connected = true;

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
    delete mSocket; mSocket = nullptr;
}

void PosixSocksSocket::closeConnection( void ) {
    mSocket->closeConnection();
}

bool PosixSocksSocket::createConnection( const std::string & address,
                                         const std::size_t port ) {
    bool connected;

    connected = false;
    setClientAddress(address,port);
    if( initializeConnection() ) {
        connected = negotiate();
    }
    if( !connected )
        closeConnection();

    return ( connected );
}

bool PosixSocksSocket::isConnected( void ) const {
    return ( mSocket->isConnected() );
}

Reader * PosixSocksSocket::getReader( void ) const {
    return ( mSocket->getReader() );
}

Writer * PosixSocksSocket::getWriter( void ) const {
    return ( mSocket->getWriter() );
}
