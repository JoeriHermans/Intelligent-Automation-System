/**
 * A class which is responsible for writing bytes to a POSIX TCP socket.
 *
 * @date                    July 6, 2014
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <unistd.h>

// Application dependencies.
#include <ias/io/writer/network/posix/posix_tcp_socket_writer.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

void PosixTcpSocketWriter::setSocket( PosixTcpSocket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );

    mSocket = socket;
}

PosixTcpSocketWriter::PosixTcpSocketWriter( PosixTcpSocket * socket ) {
    setSocket(socket);
}

void PosixTcpSocketWriter::closeWriter( void ) {
    mSocket->closeConnection();
}

std::size_t PosixTcpSocketWriter::writeByte( const char byte ) {
    long nBytes;

    nBytes = 0;
    if( mSocket->isConnected() ) {
        mMutex.lock();
        nBytes = write(mSocket->getFileDescriptor(),&byte,1);
        if( nBytes < 0 ) {
            nBytes = 0;
            mSocket->closeConnection();
        }
        mMutex.unlock();
    }

    return ( static_cast<std::size_t>(nBytes) );
}

std::size_t PosixTcpSocketWriter::writeBytes( const char * buffer,
                                              const std::size_t bufferSize ) {
    long nBytes;

    // Checking the precondition.
    assert( buffer != nullptr && bufferSize > 0 );

    nBytes = 0;
    if( mSocket->isConnected() ) {
        mMutex.lock();
        nBytes = write(mSocket->getFileDescriptor(),buffer,bufferSize);
        if( nBytes < 0 ) {
            nBytes = 0;
            mSocket->closeConnection();
        }
        mMutex.unlock();
    }

    return ( static_cast<std::size_t>(nBytes) );
}
