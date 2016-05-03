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
#include <string>

// Application dependencies.
#include <ias/channel/channel.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SOCKET_CHANNEL_H_
#define IAS_SOCKET_CHANNEL_H_

namespace ias {

class socket_channel : public channel<const std::string &> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket to which we will be writing the byte sequence.
     */
    ias::socket * mSocket;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    void set_socket(ias::socket * socket);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    socket_channel(ias::socket * socket);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~socket_channel(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void pipe(const std::string & argument);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
