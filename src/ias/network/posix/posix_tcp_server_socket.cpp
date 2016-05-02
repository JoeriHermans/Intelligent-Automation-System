/**
 * A class which describes the actions and properties of
 * a POSIX TCP server socket.
 *
 * @date                    02 05 2016
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
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/posix_tcp_server_socket.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    void posix_tcp_server_socket::set_file_descriptor(const int fd) {
        // Checking the precondition.
        assert(fd >= 0);

        mFileDescriptor = fd;
    }

    posix_tcp_server_socket::posix_tcp_server_socket(const std::size_t port) :
        server_socket(port) {
        set_file_descriptor(-1);
    }

    posix_tcp_server_socket::~posix_tcp_server_socket(void) {
        stop_listening();
    }

    void posix_tcp_server_socket::stop_listening(void) {
        if(is_bound()) {
            close(mFileDescriptor);
            set_file_descriptor(-1);
        }
    }

    bool posix_tcp_server_socket::bind_to_port(void) {
        struct addrinfo hints;
        struct addrinfo * serverInfo;
        std::string portString;
        bool bounded;
        int fd;

        if(is_bound()) {
            bounded = true;
        } else {
            bounded = false;
            memset(&hints, 0, sizeof hints);
            hints.ai_family = AF_UNSPEC;
            hints.ai_socktype = SOCK_STREAM;
            hints.ai_flags = AI_PASSIVE;
            portString = std::to_string(get_port());
            if(getaddrinfo(nullptr, portString.c_str(), &hints, &serverInfo) == 0) {
                fd = ::socket(serverInfo->ai_family, serverInfo->ai_socktype,
                              serverInfo->ai_protocol);
                if(fd >= 0) {
                    int yes = 1;

                    setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes);
                    if(bind(fd, serverInfo->ai_addr, serverInfo->ai_addrlen) == 0 &&
                       listen(fd, 256) == 0) {
                        bounded = true;
                        FD_ZERO(&mRfds);
                        FD_SET(fd, &mRfds);
                        set_file_descriptor(fd);
                    } else {
                        close(fd);
                    }
                freeaddrinfo(serverInfo);
                }
            }
        }

        return bounded;
    }

    bool posix_tcp_server_socket::is_bound(void) const {
        return mFileDescriptor >= 0;
    }

    ias::socket * posix_tcp_server_socket::accept_socket(void) {
        ias::socket * s;
        struct sockaddr addr;
        socklen_t addrLength;
        int fd;

        s = nullptr;
        if(is_bound()) {
            memset(&addr, 0, sizeof addr);
            memset(&addrLength, 0, sizeof addrLength);
            fd = accept(mFileDescriptor, &addr, &addrLength);
            if(fd >= 0)
                s = new ias::posix_tcp_socket(fd);
        }

        return s;
    }

    ias::socket * posix_tcp_server_socket::accept_socket(const std::time_t seconds) {
        struct sockaddr addr;
        socklen_t addrLength;
        timeval tv;
        ias::socket * s;
        int fd;

        s = nullptr;
        tv.tv_usec = 0;
        tv.tv_sec = seconds;
        FD_ZERO(&mRfds);
        FD_SET(mFileDescriptor, &mRfds);
        if(is_bound() && select(mFileDescriptor + 1, &mRfds, nullptr, nullptr, &tv) > 0) {
            memset(&addr, 0, sizeof addr);
            memset(&addrLength, 0, sizeof addrLength);
            fd = accept(mFileDescriptor, &addr, &addrLength);
            if(fd >= 0)
                s = new ias::posix_tcp_socket(fd);
        }

        return s;
    }

}
