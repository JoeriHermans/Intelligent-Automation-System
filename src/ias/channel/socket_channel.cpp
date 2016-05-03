/**
 * A class which describes the actions and properties of a socket
 * channel. This channel will write raw byte sequences to a socket.
 *
 * @date                    03 05 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

namespace ias {

    void socket_channel::set_socket(ias::socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr);

        mSocket = socket;
    }

    socket_channel::socket_channel(ias::socket * socket) {
        set_socket(socket);
    }

    void socket_channel::pipe(const std::string & argument) {
        // Check if the socket is connected.
        if(mSocket->is_connected()) {
            ias::writer * writer;

            writer = mSocket->get_writer();
            writer->lock();
            writer->write_all(argument.c_str(), argument.length());
            writer->unlock();
        }
    }

};
