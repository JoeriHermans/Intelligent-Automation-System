/**
 * A class which describes the properties and actions of an abstract server
 * socket.
 *
 * @date					Jul 6, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

#ifndef SERVER_SOCKET_H_
#define SERVER_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <ctime>

// Application dependencies.
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class ServerSocket {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the port to which this socket will bind or is bounded to.
     */
    unsigned int mPort;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void setPort( const unsigned int port ) {
        // Checking the precondition.
        assert( port > 0 );
        
        mPort = port;
    }
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
    
    unsigned int getPort( void ) const {
        return ( mPort );
    }
    
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
        
    ServerSocket( const unsigned int port ) {
        setPort(port);
    }
        
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ServerSocket( void ){}
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    virtual void stopListening( void ) = 0;
    
    virtual bool bindToPort( void ) = 0;
    
    virtual bool isBound( void ) const = 0;
    
    virtual Socket * acceptSocket( void ) = 0;
    
    virtual Socket * acceptSocket( const std::time_t seconds ) = 0;
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* SERVER_SOCKET_H_ */
