/**
 * A class which describes the actions and properties of
 * a POSIX TCP server socket.
 *
 * @date                    02 05 2016
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

// Application dependencies.
#include <ias/network/server_socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_POSIX_TCP_SERVER_SOCKET_H_
#define IAS_POSIX_TCP_SERVER_SOCKET_H_

namespace ias {

class posix_tcp_server_socket : public server_socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Hold the file descriptor which is associated with the listening
     * socket.
     */
    int mFileDescriptor;

    /**
     * A set of read file descriptors. This set will only contain the listening
     * file descriptor in order to check if new connections are available.
     */
    fd_set mRfds;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    void set_file_descriptor(const int fd);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    posix_tcp_server_socket(const std::size_t port);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~posix_tcp_server_socket(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void stop_listening(void);

    virtual bool bind_to_port(void);

    virtual bool is_bound(void) const;

    virtual ias::socket * accept_socket(void);

    virtual ias::socket * accept_socket(const std::time_t seconds);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
