/**
 * A set of functions which will prepare a socket to connect with a
 * remote SOCKS proxy. Please note that this class only allows outgoing
 * connections to the proxy server. Implementation according to
 * RFC 1928 and RFC 1929.
 *
 * @date                    28 04 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char kProxyIdentifierSocks[] = "socks";
    const std::uint8_t kSocksProtocolVersion = 0x05;
    const std::uint8_t kSocksMethodNoAuthentication = 0x00;
    const std::uint8_t kSocksMethodUsernamePassword = 0x02;
    const std::uint8_t kSocksVersionAuthenticateMethod = 0x01;

    // END Constants. ////////////////////////////////////////////////

    bool socks_connect(const int fd,
                       const std::string & address,
                       const std::size_t port) {
        bool connected;

        // Checking the precondition.
        assert(fd >= 0);

        connected = ias::socks_connect(fd, address, port, "", "");

        return connected;
    }

    bool socks_connect(const int fd,
                       const std::string & address,
                       const std::size_t port,
                       const std::string & username,
                       const std::string & password) {
        bool connected;

        // Checking the precondition.
        assert(fd >= 0);

        if(ias::socks_negotiate(fd, username, password)) {
            connected = ias::socks_request(fd, address, port);
        } else {
            connected = false;
        }

        return connected;
    }

    bool socks_negotiate(const int fd,
                         const std::string & username,
                         const std::string & password) {
        std::uint8_t message[4];
        std::uint8_t response[2];
        std::uint8_t version;
        std::uint8_t method;
        bool connected;

        // Checking the precondition.
        assert(fd >= 0);

        connected = false;
        // Prepare the message for the SOCKS proxy.
        message[0] = kSocksProtocolVersion;
        message[1] = 2; // Number of method supplied.
        message[2] = kSocksMethodNoAuthentication;
        message[3] = kSocksMethodUsernamePassword;
        write(fd, static_cast<unsigned char *>(message), 4);
        read(fd, static_cast<unsigned char *>(response), 2);
        version = response[0];
        method = response[1];
        if(version == kSocksProtocolVersion) {
            switch(method) {
            case 0:
                connected = true;
                break;
            case kSocksMethodUsernamePassword:
                connected = ias::socks_authenticate(fd, username, password);
                break;
            }
        }

        return connected;
    }

    bool socks_authenticate(const int fd,
                            const std::string & username,
                            const std::string & password) {
        // Authentication message layout:
        //  Version: 1 byte
        //  Username length: 1 byte (n)
        //  Username: n bytes
        //  Password length: 1 byte (m)
        //  Password: m bytes
        std::size_t lengthUsername = username.length();
        std::size_t lengthPassword = password.length();
        std::size_t messageLength = 2 + lengthUsername + lengthPassword;
        std::uint8_t message[messageLength];
        std::uint8_t response[2];
        std::size_t index;
        const char * u;
        const char * p;
        bool connected;

        connected = false;
        message[0] = kSocksVersionAuthenticateMethod;
        message[1] = static_cast<std::uint8_t>(lengthUsername);
        u = username.c_str();
        for(std::size_t i = 0; i < lengthUsername; ++i)
            message[2 + i] = u[i];
        index = 2 + lengthUsername;
        message[index++] = static_cast<std::uint8_t>(lengthPassword);
        p = password.c_str();
        for(std::size_t i = 0; i < lengthPassword; ++i)
            message[index + i] = p[i];
        memset(response, 0, 2);
        write(fd, static_cast<unsigned char *>(message), messageLength);
        read(fd, static_cast<unsigned char *>(response), 2);
        if(response[0] == kSocksVersionAuthenticateMethod && response[1] == 0x00)
            connected = true;

        return connected;
    }

    bool socks_request(const int fd,
                       const std::string & address,
                       const std::size_t port) {
        // Request message layout:
        //  Version: 1 byte
        //  Command: 1 byte
        //  Reserverd: 1 byte (0x00)
        //  Address type: 1 byte
        //  Destination address: variable length
        //  Destination port: 2 bytes (network order)
        std::size_t addressLength = address.length();
        std::size_t messageLength = 5 + addressLength;
        std::uint8_t message[messageLength];
        std::uint8_t response[BUFSIZ];
        std::uint16_t p;
        const char * a;
        bool connected;

        connected = false;
        message[0] = kSocksProtocolVersion;
        message[1] = 0x01; // Connect.
        message[2] = 0x00;
        message[3] = 0x03; // Domainname.
        message[4] = static_cast<std::uint8_t>(addressLength);
        a = address.c_str();
        for(std::size_t i = 0; i < addressLength; ++i)
            message[5 + i] = a[i];
        p = htons(static_cast<std::uint16_t>(port));
        write(fd, static_cast<unsigned char *>(message), messageLength);
        write(fd, reinterpret_cast<char *>(&p), 2);
        std::size_t n = read(fd, reinterpret_cast<char *>(response), BUFSIZ);
        if(n >= 2 && response[1] == 0x00) {
            connected = true;
            // TODO Add logger.
        } else {
            // TODO Add logger.
        }

        return connected;
    }

};
