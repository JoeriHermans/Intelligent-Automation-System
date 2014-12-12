/**
 * A set of functions which will prepare a socket to connect with a remote
 * SOCKS proxy.
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

// Application dependencies.
#include <ias/network/proxy/socks.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char kProxyIdentifierSocks[] = "socks";
const std::uint8_t kSocksProtocolVersion = 0x05;
const std::uint8_t kSocksMethodNoAuthentication = 0x00;
const std::uint8_t kSocksMethodUsernamePassword = 0x02;
const std::uint8_t kSocksVersionAuthenticateMethod = 0x01;

// END Constants. ////////////////////////////////////////////////////

bool socksConnect( const std::string & clientAddress,
                   const std::size_t clientPort,
                   const int fd ) {
    bool r;

    r = socksConnect(clientAddress,clientPort,"","",fd);

    return ( r );
}

bool socksConnect( const std::string & clientAddress,
                   const std::size_t clientPort,
                   const std::string & username,
                   const std::string & password,
                   const int fd ) {
    bool connected;

    // Checking the precondition.
    assert( fd >= 0 );

    connected = false;
    if( socksNegotiate(username,password,fd)  ) {
        connected = socksRequest(clientAddress,clientPort,fd);
    }

    return ( connected );
}

bool socksNegotiate( const std::string & username,
                     const std::string & password,
                     const int fd ) {
    std::uint8_t message[4];
    std::uint8_t response[2];
    std::uint8_t version;
    std::uint8_t method;
    bool connected;

    // Checking the precondition.
    assert( fd >= 0 );

    connected = false;
    // Prepare the message for the SOCKS proxy.
    message[0] = kSocksProtocolVersion;
    message[1] = 2; // Number of methods supplied.
    message[2] = kSocksMethodNoAuthentication;
    message[3] = kSocksMethodUsernamePassword;
    write(fd,static_cast<unsigned char *>(message),4);
    read(fd,static_cast<unsigned char *>(response),2);
    version = response[0];
    method = response[1];
    if( version == kSocksProtocolVersion ) {
        switch(method) {
        case 0:
            connected = true;
            break;
        case kSocksMethodUsernamePassword:
            connected = socksAuthenticate(username,password,fd);
            break;
        }
    }

    return ( connected );
}

bool socksAuthenticate( const std::string & username,
                        const std::string & password,
                        const int fd ) {
    // Authentication message layout:
    //  Version: 1 byte
    //  Username length: 1 byte (n)
    //  Username: n bytes
    //  Password length: 1 byte (m)
    //  Password: m bytes.
    std::size_t messageLength = 2 + username.length() + 1 + password.length();
    std::uint8_t message[messageLength];
    std::uint8_t response[2];
    std::size_t messageIndex;
    const char * u;
    const char * p;
    bool connected;

    connected = false;
    message[0] = kSocksVersionAuthenticateMethod;
    message[1] = static_cast<std::uint8_t>(username.length());
    u = username.c_str();
    for( std::size_t i = 0 ; i < username.length() ; ++i )
        message[2 + i] = u[i];
    messageIndex = 2 + username.length();
    message[messageIndex++] = static_cast<std::uint8_t>(password.length());
    p = password.c_str();
    for( std::size_t i = 0 ; i < password.length() ; ++i )
        message[messageIndex + i] = p[i];
    memset(response,0,2);
    write(fd,static_cast<unsigned char *>(message),messageLength);
    read(fd,static_cast<unsigned char *>(response),2);
    if( response[0] == kSocksVersionAuthenticateMethod && response[1] == 0 )
        connected = true;

    return ( connected );
}

bool socksRequest( const std::string & clientAddress,
                   const std::size_t clientPort,
                   const int fd ) {
    // Request message layout.
    // Version: 1 byte
    // Command: 1 byte
    // Reserved: 1 byte (0x00)
    // Address type: 1 byte
    // Destination address: variable length.
    // Destination port: 2 bytes (network order).
    std::size_t messageLength = 5 + clientAddress.length();
    std::uint8_t message[messageLength];
    std::uint8_t response[BUFSIZ];
    std::uint16_t port;
    const char * address;
    bool connected;

    connected = false;
    message[0] = kSocksProtocolVersion;
    message[1] = 0x01; // Connect.
    message[2] = 0x00;
    message[3] = 0x03; // Domainname.
    message[4] = static_cast<std::uint8_t>(clientAddress.length());
    address = clientAddress.c_str();
    for( std::size_t i = 0 ; i < clientAddress.size() ; ++i )
        message[5 + i] = address[i];
    port = htons(static_cast<std::uint16_t>(clientPort));
    write(fd,static_cast<unsigned char *>(message),messageLength);
    write(fd,reinterpret_cast<char *>(&port),2);
    std::size_t n = read(fd,reinterpret_cast<char *>(response),BUFSIZ);
    // TODO Add logging.
    if( n >= 2 && response[1] == 0 )
        connected = true;

    return ( connected );
}
