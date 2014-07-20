/**
 * A class which describes the abstract properties and actions of a server
 * routine.
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

#ifndef SERVER_H_
#define SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/network/server_socket.h>
#include <ias/network/socket.h>
#include <ias/util/observer.h>

// END Includes. /////////////////////////////////////////////////////

class Server : public Observer {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
    
    /**
     * Contains the socket which will listen for incoming connections.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    ServerSocket * mServerSocket;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void setServerSocket( ServerSocket * socket ) {
        // Checking the precondition.
        assert( socket != nullptr && socket->isBound() );
        
        mServerSocket = socket;
    }
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
    
    ServerSocket * getServerSocket( void ) const {
        return ( mServerSocket );
    }
    
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    Server( ServerSocket * socket ) {
        setServerSocket(socket);
    }
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Server( void ) {
        delete mServerSocket; mServerSocket = nullptr;
    }

	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////

    virtual void start( void ) = 0;

    virtual void stop( void ) = 0;

    virtual void join( void ) = 0;
    
    virtual void update( void ) = 0;
    
    virtual void update( void * argument ) = 0;

	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* SERVER_H_ */
