/**
 * A class which describes the properties and actions of an SSL socket.
 *
 * @date                    August 21, 2014
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

#ifndef SSL_SOCKET_H_
#define SSL_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/io/writer/writer.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class PosixSslSocket : public Socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the SSL object which is associated with this socket.
     */
    mutable SSL * mSsl;

    /**
     * Contains the SSL context of the socket.
     */
    SSL_CTX * mSslContext;

    /**
     * Contains a reference to the writer and reader which are responsible
     * for reading and writing bytes to the socket.
     */
    Reader * mReader;
    Writer * mWriter;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setSslEnvironment( SSL * ssl );

    void setSslContext( SSL_CTX * sslContext );

    bool initializeConnection( const std::string & address,
                               const std::size_t port );

    void pollSocket( void ) const;

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    PosixSslSocket( SSL_CTX * sslContext );

    PosixSslSocket( SSL * ssl );

    PosixSslSocket( const int fd );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~PosixSslSocket( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void closeConnection( void );

    virtual bool createConnection( const std::string & address,
                                   const std::size_t port );

    virtual bool isConnected( void ) const;

    virtual Reader * getReader( void ) const;

    virtual Writer * getWriter( void ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SSL_SOCKET_H_ */
