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
#include <cassert>
#include <cstring>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <netinet/in.h>
#include <poll.h>
#include <netdb.h>
#include <errno.h>

// Application dependencies.
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/io/reader/network/ssl/ssl_reader.h>
#include <ias/io/writer/network/ssl/ssl_writer.h>
#include <ias/network/network_util.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void posix_ssl_socket::initialize(void) {
        mSsl = nullptr;
        mSslContext = nullptr;
        mWriter = nullptr;
        mReader = nullptr;
    }

    void posix_ssl_socket::set_ssl_environment(SSL * ssl) {
        // Checking the precondition.
        assert(ssl != nullptr);

        // Check if an old SSL object is available.
        if(mSsl != nullptr)
            SSL_free(mSsl);
        mSsl = ssl;
        // Allocate a new reader and writer associated with this new
        // SSL object.
        delete mReader; delete mWriter;
        mReader = new ias::ssl_reader(this, ssl);
        mWriter = new ias::ssl_writer(this, ssl);
    }

    void posix_ssl_socket::set_ssl_context(SSL_CTX * sslContext) {
        // Checking the precondition.
        assert(sslContext != nullptr);

        mSslContext = sslContext;
    }

    bool posix_ssl_socket::initialize_connection(const std::string & address,
                                                 const std::size_t port) {
        bool connected;
        SSL * ssl;
        int fd;

        delete mReader; mReader = nullptr;
        delete mWriter; mWriter = nullptr;
        connected = false;
        fd = ias::connect(address, port);
        if(fd >= 0) {
            ssl = SSL_new(mSslContext);
            SSL_set_fd(ssl, fd);
            if(SSL_connect(ssl) <= 0) {
                SSL_free(mSsl);
                mSsl = nullptr;
                SSL_free(ssl);
                close(fd);
            } else {
                connected = true;
                set_ssl_environment(ssl);
            }
        }

        return connected;
    }

    void posix_ssl_socket::poll_socket(void) const {
        struct pollfd pfd;
        int fd;

        // Check if an SSL object is available.
        if(mSsl == nullptr)
            return;
        fd = SSL_get_fd(mSsl);
        if(fd >= 0) {
            pfd.fd = fd;
            pfd.events = POLLNVAL | POLLHUP | POLLRDHUP;
            pfd.revents = 0;
            if(poll(&pfd, 1, 0) >= 1)
                shutdown_connection();
        }
    }

    void posix_ssl_socket::shutdown_connection(void) const {
        int fd;

        fd = SSL_get_fd(mSsl);
        SSL_shutdown(mSsl);
        if(fd >= 0)
            close(fd);
        SSL_set_fd(mSsl, -1);
    }

    posix_ssl_socket::posix_ssl_socket(SSL * ssl) {
        initialize();
        set_ssl_environment(ssl);
    }

    posix_ssl_socket::posix_ssl_socket(SSL_CTX * context) {
        initialize();
        set_ssl_context(context);
    }

    posix_ssl_socket::~posix_ssl_socket(void) {
        close_connection();
        if(mSsl != nullptr)
            SSL_free(mSsl);
        mSsl = nullptr;
        delete mReader; mReader = nullptr;
        delete mWriter; mWriter = nullptr;
    }

    void posix_ssl_socket::close_connection(void) {
        if(is_connected())
            shutdown_connection();
    }

    bool posix_ssl_socket::create_connection(const std::string & address,
                                             const std::size_t port) {
        // Checking the precondition.
        assert(!address.empty() && port > 0);

        return initialize_connection(address, port);
    }

    bool posix_ssl_socket::is_connected(void) const {
        return mSsl != nullptr && SSL_get_fd(mSsl) >= 0;
    }

    ias::reader * posix_ssl_socket::get_reader(void) const {
        ias::reader * reader;

        if(is_connected())
            reader = mReader;
        else
            reader = nullptr;

        return reader;
    }

    ias::writer * posix_ssl_socket::get_writer(void) const {
        ias::writer * writer;

        if(is_connected())
            writer = mWriter;
        else
            writer = nullptr;

        return writer;
    }

    void posix_ssl_socket::set_send_timeout(const struct timeval & tv) {
        if(mSsl != nullptr) {
            int fd;

            fd = SSL_get_fd(mSsl);
            setsockopt(fd, SOL_SOCKET, SO_SNDTIMEO, &tv, sizeof tv);
        }
    }

    void posix_ssl_socket::set_receive_timeout(const struct timeval & tv) {
        if(mSsl != nullptr) {
            int fd;

            fd = SSL_get_fd(mSsl);
            setsockopt(fd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof tv);
        }
    }

};
