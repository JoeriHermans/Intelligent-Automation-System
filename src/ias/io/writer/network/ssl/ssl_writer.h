/**
 * A class which describes the properties and actions of a SSL writer.
 *
 * @date                    Sep 15, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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

#ifndef SSL_WRITER_H_
#define SSL_WRITER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/io/writer/writer.h>

// END Includes. /////////////////////////////////////////////////////

class SslWriter : public Writer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains a the socket to which we will be writing.
     */
    Socket * mSocket;

    /**
     * Contains the SSL socket to which we will be writing the raw
     * unencrypted bytes.
     */
    SSL * mSsl;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setSocket( Socket * socket );

    void setSslEnvironment( SSL * ssl );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    SslWriter( Socket * socket , SSL * ssl );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~SslWriter( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void closeWriter( void );

    virtual std::size_t writeByte( const char byte );

    virtual std::size_t writeBytes( const char * buffer , const std::size_t bufferSize );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SSL_WRITER_H_ */
