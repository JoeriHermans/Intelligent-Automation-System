/**
 * A set of network utility functions which make the life of the
 * developer a little bit more pleasant.
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
#include <netinet/tcp.h>
#include <iostream>
#include <poll.h>
#include <netdb.h>
#include <errno.h>
#include <iostream>

// Application dependencies.
#include <ias/network/network_util.h>
#include <ias/network/proxy/socks.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    int connect(const std::string & address, const std::size_t port) {
        struct addrinfo hints;
        struct addrinfo * results;
        std::string portString;
        int result;
        int fd;

        // Checking the precondition.
        assert(!address.empty() && port > 0);

        result = -1;
        memset(&hints, 0, sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        portString = std::to_string(port);
        int rc = getaddrinfo(address.c_str(), portString.c_str(), &hints, &results);
        if(results != nullptr && rc >= 0) {
            fd = socket(results->ai_family, results->ai_socktype, results->ai_protocol);
            if(fd >= 0) {
                if(connect(fd, results->ai_addr, results->ai_addrlen) == 0)
                    result = fd;
                else
                    close(fd);
            }
            freeaddrinfo(results);
        }

        return result;
    }

    bool enable_keep_alive(const int fd) {
        static const int optval = 1;
        bool success;

        // Checking the precondition.
        assert(fd >= 0);

        success = (setsockopt(fd, SOL_SOCKET, SO_KEEPALIVE, &optval, sizeof optval) >= 0);

        return success;
    }

    bool disable_nagle(const int fd) {
        static const int optval = 1;
        bool success;

        // Checking the precondition.
        assert(fd >= 0);

        success = (setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &optval, sizeof optval) >= 0);

        return success;
    }

    int connect_to_socks(const std::string & proxyAddress,
                         const std::size_t proxyPort,
                         const std::string & address,
                         const std::size_t port) {
        int fd;

        // Checking the preconditions.
        assert(!proxyAddress.empty() && proxyPort >= 0 &&
               !address.empty() && port > 0);

        fd = ias::connect(proxyAddress, proxyPort);
        if(fd >= 0 && !ias::socks_connect(fd, address, port)) {
            close(fd);
            fd = -1;
        }

        return fd;
    }

};
