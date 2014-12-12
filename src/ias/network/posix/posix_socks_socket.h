/**
 * A class which describes the properties and actions of a POSIX SOCKS
 * proxy socket. This socket will connect to a remote SOCKS proxy server.
 *
 * Please note that this class only allows outgoing connections to the proxy
 * server.
 *
 * @date                    December 12, 2014
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

#ifndef POSIX_SOCKS_SOCKET_H_
#define POSIX_SOCKS_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

class PosixSocksSocket : public Socket {

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
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~PosixSocksSocket( void );

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

#endif /* POSIX_SOCKS_SOCKET_H_ */
