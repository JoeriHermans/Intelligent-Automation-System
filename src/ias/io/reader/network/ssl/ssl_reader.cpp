/**
 * A class which describes the properties and actions of an SSL
 * reader. Furthermore, this class' main objective is to read
 * encrypted bytes from the SSL socket.
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
#include <ias/io/reader/network/ssl/ssl_reader.h>
#include <ias/io/reader/reader.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    void ssl_reader::set_socket(ias::socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr);

        mSocket = socket;
    }

    void ssl_reader::set_ssl_environment(SSL * ssl) {
        // Checking the precondition.
        assert(ssl != nullptr);

        mSsl = ssl;
    }

    ssl_reader::ssl_reader(ias::socket * socket, SSL * ssl) {
        set_socket(socket);
        set_ssl_environment(ssl);
    }

    void ssl_reader::close_reader(void) {
        mSocket->close_connection();
    }

    std::size_t ssl_reader::read_byte(char * byte) {
        int nBytes;

        // Checking the precondition.
        assert(byte != nullptr);

        nBytes = 0;
        if(mSocket->is_connected()) {
            nBytes = SSL_read(mSsl, byte, 1);
            if(nBytes < 0) {
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t ssl_reader::read_bytes(char * buffer,
                                       const std::size_t bufferSize) {
        int nBytes;

        // Checking the precondition.
        assert(buffer != nullptr && bufferSize > 0);

        nBytes = 0;
        if(mSocket->is_connected()) {
            nBytes = SSL_read(mSsl, buffer, bufferSize);
            if(nBytes < 0) {
                nBytes = 0;
            }
        }

        return static_cast<std::size_t>(nBytes);
    }

    std::size_t ssl_reader::read_all(char * buffer,
                                     const std::size_t bufferSize) {
        std::size_t readSum;
        int nBytes;

        // Checking the precondition.
        assert(buffer != nullptr && bufferSize > 0);

        readSum = 0;
        nBytes = 0;
        while(readSum != bufferSize && mSocket->is_connected()) {
            nBytes = SSL_read(mSsl, buffer + readSum, bufferSize - readSum);
            if(nBytes < 0)
                mSocket->close_connection();
            else
                readSum += static_cast<std::size_t>(nBytes);
        }

        return readSum;
    }

};
