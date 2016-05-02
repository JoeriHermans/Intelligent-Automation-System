/**
 * A class which describes the properties and actions of a
 * POSIX SSL socket.
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

// System dependencies.
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/io/reader/reader.h>
#include <ias/io/writer/writer.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_POSIX_SSL_SOCKET_H_
#define IAS_POSIX_SSL_SOCKET_H_

namespace ias {

class posix_ssl_socket : public socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the SSL objects which is associated with this socket.
     *
     * @note By default, this object will be equal to the null reference.
     */
    mutable SSL * mSsl;

    /**
     * Holds the SSL context of the socket.
     *
     * @note By default, this object will be equal to the null reference.
     */
    SSL_CTX * mSslContext;

    /**
     * Holds a pointer to the writer and reader which are responsible for
     * reading and writing bytes to or from the socket.
     *
     * @note By default, these members will be equal to the null reference.
     */
    ias::reader * mReader;
    ias::writer * mWriter;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_ssl_environment(SSL * ssl);

    void set_ssl_context(SSL_CTX * context);

    bool initialize_connection(const std::string & address,
                               const std::size_t port);

    void poll_socket(void) const;

    void shutdown_connection(void) const;

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    posix_ssl_socket(SSL_CTX * sslContext);

    posix_ssl_socket(SSL * ssl);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~posix_ssl_socket(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void close_connection(void);

    virtual bool is_connected(void) const;

    virtual bool create_connection(const std::string & address,
                                   const std::size_t port);

    virtual ias::reader * get_reader(void) const;

    virtual ias::writer * get_writer(void) const;

    virtual void set_receive_timeout(const struct timeval & tv);

    virtual void set_send_timeout(const struct timeval & tv);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
