/**
 * An abstract class which describes the abstract properties and actions
 * of a server routine.
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
#include <ias/network/server_socket.h>
#include <ias/network/socket.h>
#include <ias/util/observer.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SERVER_H_
#define IAS_SERVER_H_

namespace ias {

class server : public observer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket which will listen for incoming connections.
     *
     * @note By default, this member will be equal to the null reference.
     */
    ias::server_socket * mServerSocket;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    void set_server_socket(ias::server_socket * socket) {
        // Checking the precondition.
        assert(socket != nullptr && socket->is_bound());

        mServerSocket = socket;
    }

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////

    ias::server_socket * get_server_socket(void) const {
        return mServerSocket;
    }

    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    server(ias::server_socket * socket) {
        set_server_socket(socket);
    }

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~server(void) {
        delete mServerSocket;
        mServerSocket = nullptr;
    }

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void start(void) = 0;

    virtual void stop(void) = 0;

    virtual void join(void) = 0;

    virtual void update(void) = 0;

    virtual void update(void * argument) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
