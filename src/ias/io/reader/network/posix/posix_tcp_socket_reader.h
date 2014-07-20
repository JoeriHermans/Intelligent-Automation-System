/**
 * A reader which is responsible for reading bytes from a POSIX TCP socket.
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

#ifndef POSIX_TCP_SOCKET_READER_H_
#define POSIX_TCP_SOCKET_READER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/io/reader/reader.h>

// Forward declarations.
class PosixTcpSocket;

// END Includes. /////////////////////////////////////////////////////

class PosixTcpSocketReader : public Reader {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the socket from which we will be reading.
     */
    PosixTcpSocket * mSocket;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void setSocket( PosixTcpSocket * socket );
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    PosixTcpSocketReader( PosixTcpSocket * socket );
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~PosixTcpSocketReader( void );
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    virtual void closeReader( void );
    
    virtual std::size_t readByte( char * byte );
    
    virtual std::size_t readBytes( char * buffer , const std::size_t bufferSize );
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* POSIX_TCP_SOCKET_READER_H_ */
