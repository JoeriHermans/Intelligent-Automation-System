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

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_POSIX_TCP_SOCKET_READER_H_
#define IAS_POSIX_TCP_SOCKET_READER_H_

namespace ias {

class posix_tcp_socket_reader : public reader {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket from which the reader will be reading bytes.
     */
    ias::posix_tcp_socket * mSocket;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    void set_socket(ias::posix_tcp_socket * socket);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    posix_tcp_socket_reader(ias::posix_tcp_socket * socket);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~posix_tcp_socket_reader(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void close_reader(void);

    virtual std::size_t read_byte(char * byte);

    virtual std::size_t read_bytes(char * buffer,
                                   const std::size_t bufferSize);

    virtual std::size_t read_all(char * buffer,
                                 const std::size_t bufferSize);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
