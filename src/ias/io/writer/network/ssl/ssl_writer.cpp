/**
 * Describes the properties and actions of a class which is
 * responsible for reading bytes from an SSL socket.
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
#include <cassert>

// Application dependencies.
#include <ias/io/writer/network/ssl/ssl_writer.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    void ssl_writer::set_socket(ias::socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr);

        mSocket = socket;
    }

    void ssl_writer::set_ssl_environment(SSL * ssl) {
        // Checking the precondition.
        assert(ssl != nullptr);

        mSsl = ssl;
    }

    ssl_writer::ssl_writer(ias::socket * socket, SSL * ssl) {
        set_socket(socket);
        set_ssl_environment(ssl);
    }

    void ssl_writer::close_writer(void) {
        mSocket->close_connection();
    }

    std::size_t ssl_writer::write_byte(const char byte) {
        int nBytes;

        nBytes = 0;
        if(mSocket->is_connected()) {
            nBytes = SSL_write(mSsl, &byte, 1);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t ssl_writer::write_bytes(const char * buffer,
                                        const std::size_t bufferSize) {
        int nBytes;

        nBytes = 0;
        if(mSocket->is_connected()) {
            nBytes = SSL_write(mSsl, buffer, bufferSize);
            if(nBytes < 0) {
                mSocket->close_connection();
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t ssl_writer::write_all(const char * buffer,
                                     const std::size_t bufferSize) {
        std::size_t writtenSum;
        int nBytes;

        writtenSum = 0;
        while(writtenSum != bufferSize && mSocket->is_connected()) {
            nBytes = SSL_write(mSsl, buffer + writtenSum,
                               bufferSize - writtenSum);
            if(nBytes < 0)
                mSocket->close_connection();
            else
                writtenSum += static_cast<std::size_t>(nBytes);
        }

        return writtenSum;
    }

};
