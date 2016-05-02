/**
 * An abstract class which describes the properties and actions of an
 * abstract server socket (listerning socket).
 *
 * @date                    28 04 2016
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
#include <ctime>

// Application dependencies.
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SERVER_SOCKET_H_
#define IAS_SERVER_SOCKET_H_

namespace ias {

class server_socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the port number to which this socket will bind, or is bounded to.
     */
    std::size_t mPort;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ///////////////////////////////////////////////

    void set_port(const std::size_t port) {
        // Checking the precondition.
        assert(port > 0);

        mPort = port;
    }

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////

    std::size_t get_port(void) const {
        return mPort;
    }

    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    server_socket(const std::size_t port) {
        set_port(port);
    }

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~server_socket(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void stop_listening(void) = 0;

    virtual bool bind_to_port(void) = 0;

    virtual bool is_bound(void) const = 0;

    virtual ias::socket * accept_socket(void) = 0;

    virtual ias::socket * accept_socket(const std::time_t seconds) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
