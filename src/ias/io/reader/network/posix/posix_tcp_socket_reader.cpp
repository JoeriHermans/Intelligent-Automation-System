/**
 * A reader which is able to read bytes from a POSIX TCP socket.
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
#include <unistd.h>
#include <sys/socket.h>
#include <cerrno>

// Application dependencies.
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/io/reader/network/posix/posix_tcp_socket_reader.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    void posix_tcp_socket_reader::set_socket(ias::posix_tcp_socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr);

        mSocket = socket;
    }

    posix_tcp_socket_reader::posix_tcp_socket_reader(ias::posix_tcp_socket * socket) {
        set_socket(socket);
    }

    void posix_tcp_socket_reader::close_reader(void) {
        mSocket->close_connection();
    }

    std::size_t posix_tcp_socket_reader::read_byte(char * byte) {
        int nBytes;
        int fd;

        nBytes = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            nBytes = read(fd, byte, 1);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t posix_tcp_socket_reader::read_bytes(char * buffer,
                                                    const std::size_t bufferSize) {
        int nBytes;
        int fd;

        nBytes = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            nBytes = read(fd, buffer, bufferSize);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t posix_tcp_socket_reader::read_all(char * buffer,
                                                  const std::size_t bufferSize) {
        std::size_t readSum;
        int nBytes;
        int fd;

        readSum = 0;
        nBytes = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            while(readSum != bufferSize && mSocket->is_connected()) {
                nBytes = read(fd, buffer + readSum, bufferSize - readSum);
                if(nBytes < 0) {
                    mSocket->close_connection();
                } else {
                    readSum += static_cast<std::size_t>(nBytes);
                }
            }
        }

        return readSum;
    }

};
