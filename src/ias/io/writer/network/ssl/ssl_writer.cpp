/**
 * A class which describes the properties and actions of a SSL writer.
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
#include <ias/io/writer/network/ssl/ssl_writer.h>

// END Includes. /////////////////////////////////////////////////////

void SslWriter::setSocket( Socket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );

    mSocket = socket;
}

void SslWriter::setSslEnvironment( SSL * ssl ) {
    // Checking the precondition.
    assert( ssl != nullptr );

    mSsl = ssl;
}

SslWriter::SslWriter( Socket * socket , SSL * ssl ) {
    setSocket(socket);
    setSslEnvironment(ssl);
}

void SslWriter::closeWriter( void ) {
    mSocket->closeConnection();
}

std::size_t SslWriter::writeByte( const char byte ) {
    int nBytes;

    nBytes = 0;
    if( mSocket->isConnected() ) {
        mMutex.lock();
        nBytes = SSL_write(mSsl,&byte,1);
        if( nBytes < 0 ) {
            nBytes = 0;
        }
        mMutex.unlock();
    }

    return ( static_cast<std::size_t>(nBytes) );
}

std::size_t SslWriter::writeBytes( const char * buffer , const std::size_t bufferSize ) {
    int nBytes;

    // Checking the precondition.
    assert( buffer != nullptr );

    nBytes = 0;
    if( mSocket->isConnected() ) {
        mMutex.lock();
        nBytes = SSL_write(mSsl,buffer,static_cast<int>(bufferSize));
        if( nBytes < 0 ) {
            nBytes = 0;
        }
        mMutex.unlock();
    }

    return ( static_cast<std::size_t>(nBytes) );
}
