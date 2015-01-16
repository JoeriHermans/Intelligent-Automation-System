/**
 * A class which describes the actions and properties of a device channel.
 *
 * @date                    Jul 7, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
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

// Application dependencies.
#include <ias/channel/socket_channel.h>

// END Includes. /////////////////////////////////////////////////////

void SocketChannel::setSocket( Socket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );

    mSocket = socket;
}

SocketChannel::SocketChannel( Socket * socket ) {
    setSocket(socket);
}

SocketChannel::~SocketChannel( void ) {
    // Nothing to do here.
}

void SocketChannel::pipe( const std::string & argument ) {
    if( mSocket->isConnected() ) {
        Writer * writer;

        writer = mSocket->getWriter();
        writer->lock();
        writer->writeBytes(argument.c_str(),argument.length());
        writer->unlock();
    }
}
