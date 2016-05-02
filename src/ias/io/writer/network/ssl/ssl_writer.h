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
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/io/writer/writer.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SSL_WRITER_H_
#define IAS_SSL_WRITER_H_

namespace ias {

class ssl_writer : public writer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket to which we will be writing.
     */
    ias::socket * mSocket;

    /**
     * Holds the SSL object to which we will be writing raw, unencrypted bytes.
     */
    SSL * mSsl;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    void set_socket(ias::socket * socket);

    void set_ssl_environment(SSL * ssl);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    ssl_writer(ias::socket * socket, SSL * ssl);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~ssl_writer(void) = default;

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
