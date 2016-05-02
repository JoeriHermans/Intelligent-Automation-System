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
        std::size_t n;

        // Checking the precondition.
        assert(byte != nullptr);

        if(mSocket->is_connected()) {
            n = static_cast<std::size_t>(read(mSocket->get_file_descriptor(), byte, 1));
        } else {
            n = 0;
        }

        return n;
    }

    std::size_t posix_tcp_socket_reader::read_bytes(char * buffer,
                                                    const std::size_t bufferSize) {
        std::size_t n;

        // Checking the preconditions.
        assert(buffer != nullptr && bufferSize > 0);

        if(mSocket->is_connected()) {
            n = static_cast<std::size_t>(read(mSocket->get_file_descriptor(), buffer, bufferSize));
        } else {
            n = 0;
        }

        return n;
    }

};
