/**
 * A class which is responsible for writing bytes to a POSIX TCP
 * socket.
 *
 * @date                    29 04 2016
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

// Application dependencies.
#include <ias/io/writer/network/posix/posix_tcp_socket_writer.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    void posix_tcp_socket_writer::set_socket(ias::posix_tcp_socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr);

        mSocket = socket;
    }

    posix_tcp_socket_writer::posix_tcp_socket_writer(ias::posix_tcp_socket * socket) {
        set_socket(socket);
    }

    void posix_tcp_socket_writer::close_writer(void) {
        mSocket->close_connection();
    }

    std::size_t posix_tcp_socket_writer::write_byte(const char byte) {
        int nBytes;
        int fd;

        nBytes = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            nBytes = write(fd, &byte, 1);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t posix_tcp_socket_writer::write_bytes(const char * bytes,
                                                     const std::size_t bufferSize) {
        int nBytes;
        int fd;

        nBytes = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            nBytes = write(fd, bytes, bufferSize);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t posix_tcp_socket_writer::write_all(const char * buffer,
                                                   const std::size_t bufferSize) {
        int nBytes;
        std::size_t writtenSum;
        int fd;

        writtenSum = 0;
        if(mSocket->is_connected()) {
            fd = mSocket->get_file_descriptor();
            while(writtenSum != bufferSize && mSocket->is_connected()) {
                nBytes = write(fd, buffer + writtenSum, bufferSize - writtenSum);
                if(nBytes < 0) {
                    mSocket->close_connection();
                } else {
                    writtenSum += static_cast<std::size_t>(nBytes);
                }
            }
        }

        return writtenSum;
    }

};
