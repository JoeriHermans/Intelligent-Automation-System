/**
 * An application which is responsible for handling the client inputs.
 *
 * @date                    Jul 17, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2013 Joeri HERMANS
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

#ifndef CLIENT_APPLICATION_H_
#define CLIENT_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/application/application.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// END Includes. /////////////////////////////////////////////////////

class ClientApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the socket which is connected with the remote IAS host.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    Socket * mSocket;

    /**
     * A flag which indicates if the user is logged in.
     *
     * @note    By default, this member will be equal to false.
     */
    bool mLoggedIn;

    /**
     * Contains the username of the authenticated used.
     *
     * @note    By default, this member will be equal to the empty string.
     */
    std::string mUsername;

    /**
     * Contains the SSL context.
     */
    SSL_CTX * mSslContext;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void initializeSslContext( void );

    void analyzeArguments( const int argc , const char ** argv );

    std::string fetchAddress( const int argc , const char ** argv ) const;

    std::size_t fetchPort( const int argc , const char ** argv ) const;

    std::string fetchSocksServer( const int argc , const char ** argv ) const;

    bool sslRequested( const int argc , const char ** argv ) const;

    int connectToSocksProxy( const std::string & proxy,
                             const std::string & clientAddress,
                             const std::size_t clientPort ) const;

    void login( void );

    void processCommands( void );

    void writeMessage( const std::string & message ) const;

    void readResponse( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ClientApplication( const int argc , const char ** argv );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ClientApplication( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CLIENT_APPLICATION_H_ */
