/**
 * A class which describes the abstract properties of a session.
 *
 * @date					July 6, 2014
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

#ifndef SESSION_H_
#define SESSION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/util/observable.h>

// END Includes. /////////////////////////////////////////////////////

class Session : public Observable {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the socket which is associated with the session.
     */
    Socket * mSocket;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void setSocket( Socket * socket ) {
        // Checking the preconditions.
        assert( socket != nullptr );
        
        mSocket = socket;
    }
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
    
    bool readBytes( char * buffer , const std::size_t n ) {
        std::size_t bytesRead;
        std::size_t nBytes;
        Reader * reader;
        
        // Checking the precondition.
        assert( buffer != nullptr && n > 0 );
        
        if( !mSocket->isConnected() ) return ( false );
        
        reader = mSocket->getReader();
        bytesRead = 0;
        while( bytesRead != n ) {
            nBytes = reader->readBytes(buffer + bytesRead,n - bytesRead);
            if( nBytes == 0 )
                return ( false );
            bytesRead += nBytes;
        }
        
        return ( true );
    }
    
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
        
    Session( Socket * socket ) {
        setSocket(socket);
    }
        
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Session( void ) {
        delete mSocket; mSocket = nullptr;
    }
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void ) = 0;
    
    virtual void stop( void ) = 0;
    
    Socket * getSocket( void ) const {
        return ( mSocket );
    }
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* SESSION_H_ */
