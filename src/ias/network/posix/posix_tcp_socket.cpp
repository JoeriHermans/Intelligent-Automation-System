/**
 * A class which represents the properties and actions of a POSIX
 * TCP socket.
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
#include <poll.h>
#include <netdb.h>
#include <errno.h>

// Application dependencies.
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/network_util.h>
#include <ias/io/reader/network/posix/posix_tcp_socket_reader.h>
#include <ias/io/writer/network/posix/posix_tcp_socket_writer.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void posix_tcp_socket::initialize(void) {
        set_file_descriptor(-1);
        mReader = nullptr;
        mWriter = nullptr;
    }

    void posix_tcp_socket::set_file_descriptor(const int fd) {
        mFileDescriptor = fd;
    }

    bool posix_tcp_socket::initialize_connection(const std::string & address,
                                                 const std::size_t port) {
        bool connected;
        int fd;

        fd = ias::connect(address, port);
        if(fd >= 0) {
            mFileDescriptor = fd;
            connected = true;
            delete mReader; mReader = nullptr;
            delete mWriter; mWriter = nullptr;
            mReader = new ias::posix_tcp_socket_reader(this);
            mWriter = new ias::posix_tcp_socket_writer(this);
        } else {
            connected = false;
        }

        return connected;
    }

    void posix_tcp_socket::poll_socket(void) {
        struct pollfd pfd;

        // Check if the file descriptor is opened.
        if(mFileDescriptor >= 0) {
            pfd.fd = mFileDescriptor;
            pfd.events = POLLNVAL | POLLHUP | POLLRDHUP;
            pfd.revents = 0;
            if(poll(&pfd, 1, 0) >= 1) {
                close(mFileDescriptor);
                mFileDescriptor = -1;
            }
        }
    }

    posix_tcp_socket::posix_tcp_socket(void) {
        initialize();
    }

    posix_tcp_socket::posix_tcp_socket(const int fd) {
        initialize();
        set_file_descriptor(fd);
        // Allocate the associated reader and writer.
        mReader = new ias::posix_tcp_socket_reader(this);
        mWriter = new ias::posix_tcp_socket_writer(this);
    }

    posix_tcp_socket::~posix_tcp_socket(void) {
        close_connection();
        delete mReader; mReader = nullptr;
        delete mWriter; mWriter = nullptr;
    }

    void posix_tcp_socket::close_connection(void) {
        // Check if the socket is connected.
        if(mFileDescriptor >= 0) {
            close(mFileDescriptor);
            set_file_descriptor(-1);
        }
    }

    bool posix_tcp_socket::create_connection(const std::string & address,
                                             const std::size_t port) {
        close_connection();

        return initialize_connection(address, port);
    }

    bool posix_tcp_socket::is_connected(void) const {
        return mFileDescriptor >= 0;
    }

    ias::reader * posix_tcp_socket::get_reader(void) const {
        ias::reader * reader;

        if(is_connected())
            reader = mReader;
        else
            reader = nullptr;

        return reader;
    }

    ias::writer * posix_tcp_socket::get_writer(void) const {
        ias::writer * writer;

        if(is_connected())
            writer = mWriter;
        else
            writer = nullptr;

        return writer;
    }

    void posix_tcp_socket::set_send_timeout(const struct timeval & tv) {
        if(is_connected())
            setsockopt(mFileDescriptor, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
    }

    void posix_tcp_socket::set_receive_timeout(const struct timeval & tv) {
        if(is_connected())
            setsockopt(mFileDescriptor, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
    }

    int posix_tcp_socket::get_file_descriptor(void) const {
        return mFileDescriptor;
    }

};
