/**
 * A class which represents the properties and actions of a POSIX
 * TCP socket.
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
#include <string>
#include <mutex>

// Application dependencies.
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_POSIX_TCP_SOCKET_H_
#define IAS_POSIX_TCP_SOCKET_H_

namespace ias {

class posix_tcp_socket : public socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Contains the file descriptor which is associated with the TCP socket.
     */
    mutable int mFileDescriptor;

    /**
     * Contains the reader which is associated with the POSIX TCP socket.
     *
     * @note In this case the socket is not connected, this member will be
     *       equal to the null reference.
     */
    ias::reader * mReader;

    /**
     * Contains the writer which is associated with the POSIX TCP socket.
     *
     * @note In the case the socket is not connected, this member will be
     *       equal to the null reference.
     */
    ias::writer * mWriter;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_file_descriptor(const int fd);

    bool initialize_connection(const std::string & address,
                               const std::size_t port);

    void poll_socket(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    posix_tcp_socket(void);

    posix_tcp_socket(const int fd);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~posix_tcp_socket(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void close_connection(void);

    virtual bool create_connection(const std::string & address,
                                   const std::size_t port);

    virtual bool is_connected(void) const;

    virtual ias::reader * get_reader(void) const;

    virtual ias::writer * get_writer(void) const;

    virtual void set_send_timeout(const struct timeval & tv);

    virtual void set_receive_timeout(const struct timeval & tv);

    int get_file_descriptor(void) const;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
