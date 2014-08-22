/**
 * A class which describes the properties and actions of an SSL server socket.
 *
 * @date                    August 22, 2014
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

#ifndef SSL_SERVER_SOCKET_H_
#define SSL_SERVER_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/network/server_socket.h>

// END Includes. /////////////////////////////////////////////////////

class SslServerSocket : public ServerSocket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    SslServerSocket( const unsigned int port );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~SslServerSocket( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void stopListening( void );

    virtual bool bindToPort( void );

    virtual bool isBound( void ) const;

    virtual Socket * acceptSocket( void );

    virtual Socket * acceptSocket( const std::time_t seconds );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SSL_SERVER_SOCKET_H_ */
