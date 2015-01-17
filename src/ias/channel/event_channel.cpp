/**
 * A class which describes the properties and actions of an event channel. This
 * channel will write the incoming events to the specified socket.
 *
 * @date                    17 January, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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
#include <ias/channel/event_channel.h>

// END Includes. /////////////////////////////////////////////////////

void EventChannel::setSocket( Socket * socket ) {
    // Checking the precondition.
    assert( socket != nullptr );

    mSocket = socket;
}

EventChannel::EventChannel( Socket * socket ) {
    setSocket(socket);
}

void EventChannel::pipe( const Event * argument ) {
    // Checking the precondition.
    assert( argument != nullptr );

    // TODO Implement.
}
