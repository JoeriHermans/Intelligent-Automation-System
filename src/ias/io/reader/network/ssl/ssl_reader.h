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
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SSL_READER_H_
#define IAS_SSL_READER_H_

namespace ias {

class ssl_reader : public reader {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket object from which we will be reading bytes.
     */
    ias::socket * mSocket;

    /**
     * Holds the SSL object which we will use to read encrypted bytes.
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

    ssl_reader(ias::socket * socket, SSL * ssl);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~ssl_reader(void) = default;

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
