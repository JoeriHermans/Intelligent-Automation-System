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

// Application dependencies.
#include <ias/io/writer/writer.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_POSIX_TCP_SOCKET_WRITER_H_
#define IAS_POSIX_TCP_SOCKET_WRITER_H_

namespace ias {

class posix_tcp_socket_writer : public writer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds to socket to which we will write to.
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

    posix_tcp_socket_writer(ias::posix_tcp_socket * socket);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~posix_tcp_socket_writer(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void close_writer(void);

    virtual std::size_t write_byte(const char byte);

    virtual std::size_t write_bytes(const char * buffer,
                                    const std::size_t bufferSize);

    virtual std::size_t write_all(const char * buffer,
                                  const std::size_t bufferSize);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
