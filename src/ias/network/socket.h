/**
 * A class which describes the properties and actions of a socket.
 *
 * @date                    Jul 6, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
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

#ifndef SOCKET_H_
#define SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <sys/time.h>

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/io/writer/writer.h>

// END Includes. /////////////////////////////////////////////////////

class Socket {

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

    Socket( void ) = default;

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Socket( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void closeConnection( void ) = 0;

    virtual bool createConnection( const std::string & address,
                                   const std::size_t port ) = 0;

    virtual bool isConnected( void ) const = 0;

    virtual Reader * getReader( void ) const = 0;

    virtual Writer * getWriter( void ) const = 0;

    virtual void setReceiveTimeout( const struct timeval & tv ) = 0;

    virtual void setSendTimeout( const struct timeval & tv ) = 0;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SOCKET_H_ */
