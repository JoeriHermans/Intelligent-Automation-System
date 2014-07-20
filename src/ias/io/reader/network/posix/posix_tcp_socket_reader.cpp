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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <unistd.h>

// Application dependencies.
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/io/reader/network/posix/posix_tcp_socket_reader.h>

// END Includes. /////////////////////////////////////////////////////

void PosixTcpSocketReader::setSocket( PosixTcpSocket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );
    
    mSocket = socket;
}

PosixTcpSocketReader::PosixTcpSocketReader( PosixTcpSocket * socket ) {
    setSocket(socket);
}

PosixTcpSocketReader::~PosixTcpSocketReader( void ) {
    // Nothing to do here.
}

void PosixTcpSocketReader::closeReader( void ) {
    mSocket->closeConnection();
}

std::size_t PosixTcpSocketReader::readByte( char * byte ) {
    int nBytes;
    
    nBytes = 0;
    if( mSocket->isConnected() ) {
        nBytes = read(mSocket->getFileDescriptor(),byte,1);
        if( nBytes < 0 ) {
            mSocket->closeConnection();
            nBytes = 0;
        }
    }
    
    return ( (std::size_t) nBytes );
}

std::size_t PosixTcpSocketReader::readBytes( char * buffer,
                                             const std::size_t bufferSize ) {
    int nBytes;
    
    // Checking the precondition.
    assert( buffer != nullptr && bufferSize > 0 );
    
    nBytes = 0;
    if( mSocket->isConnected() ) {
        nBytes = read(mSocket->getFileDescriptor(),buffer,bufferSize);
        if( nBytes < 0 ) {
            mSocket->closeConnection();
            nBytes = 0;
        }
    }
    
    return ( (std::size_t) nBytes );
}
