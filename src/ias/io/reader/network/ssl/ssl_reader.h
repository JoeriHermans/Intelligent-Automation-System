/**
 * A class which describes the properties and actions of an SSL reader.
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

#ifndef SSL_READER_H_
#define SSL_READER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <mutex>

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class SslReader : public Reader {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the SSL socket from which the reading will be reading the
     * encrypted bytes.
     */
    Socket * mSocket;

    /**
     * Contains the SSL environment of the specified socket.
     */
    SSL * mSsl;

    /**
     * Mutex which is responsible for synchronous I/O.
     */
    std::mutex mMutex;

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

    SslReader( Socket * socket , SSL * ssl );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~SslReader( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void closeReader( void );

    virtual std::size_t readByte( char * byte );

    virtual std::size_t readBytes( char * buffer , const std::size_t bufferSize );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SSL_READER_H_ */
