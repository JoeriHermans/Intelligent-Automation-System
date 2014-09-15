/**
 * A class which describes the properties and actions of an SSL reader.
 *
 * @date                    Sep 15, 2014
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/io/reader/network/ssl/ssl_reader.h>

// END Includes. /////////////////////////////////////////////////////

void SslReader::setSocket( Socket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );

    mSocket = socket;
}

void SslReader::setSslEnvironment( SSL * ssl ) {
    // Checking the precondition.
    assert( ssl != nullptr );

    mSsl = ssl;
}

SslReader::SslReader( Socket * socket , SSL * ssl ) {
    setSocket(socket);
    setSslEnvironment(ssl);
}

void SslReader::closeReader( void ) {
    mSocket->closeConnection();
}

std::size_t SslReader::readByte( char * byte ) {
    int nBytes;

    // Checking the precondition.
    assert( byte != nullptr );

    nBytes = 0;
    if( mSocket->isConnected() ) {
        nBytes = SSL_read(mSsl,byte,1);
        if( nBytes < 0 ) {
            mSocket->closeConnection();
            nBytes = 0;
        }
    }

    return ( (std::size_t) nBytes );
}

std::size_t SslReader::readBytes( char * buffer , const std::size_t bufferSize ) {
    int nBytes;

    nBytes = 0;
    if( mSocket->isConnected() ) {
        nBytes = SSL_read(mSsl,buffer,bufferSize);
        if( nBytes < 0 ) {
            mSocket->closeConnection();
            nBytes = 0;
        }
    }

    return ( (std::size_t) nBytes );
}
