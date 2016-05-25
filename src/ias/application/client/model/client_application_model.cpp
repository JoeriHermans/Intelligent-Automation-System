/**
 * A class which decribes the properties and actions of a client
 * application.
 *
 * @date                    24 05 2016
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
#include <unistd.h>
#include <string>
#include <netinet/in.h>

// Application dependencies.
#include <ias/application/client/model/client_application_model.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char client_application_model::kCommandQuit[] = "quit";

    // END Constants. ////////////////////////////////////////////////

    inline void client_application_model::initialize(void) {
        mSocket = nullptr;
        mLoggedIn = false;
        mSslContext = nullptr;
        mCommunicationThreadSend = nullptr;
        mCommunicationThreadReceive = nullptr;
    }

    void client_application_model::initialize_connection(const int fd) {
        // Checking the precondition.
        assert(fd >= 0);

        // Check if an SSL connection needs to be established.
        if(ssl_requested()) {
            SSL * ssl;

            ssl = SSL_new(mSslContext);
            SSL_set_fd(ssl, fd);
            if(SSL_connect(ssl) <= 0) {
                SSL_free(ssl);
                close(fd);
            } else {
                mSocket = new ias::posix_ssl_socket(ssl);
            }
        } else {
            mSocket = new ias::posix_tcp_socket(fd);
        }
        // Check if a connection could be established.
        if(mSocket != nullptr)
            set_socket_timeouts();
    }

    void client_application_model::process_receive_thread(void) {
        while(mSocket->is_connected())
            read_responses();
    }

    void client_application_model::process_send_thread(void) {
        std::unique_lock<std::mutex> lock(mMutexLockSend);
        std::string command;

        while(mSocket->is_connected()) {
            mMutexCommandQueue.lock();
            // Stop the sending thread if the command
            // queue is empty.
            if(mCommandQueue.empty()) {
                mMutexCommandQueue.unlock();
                mLockSend.wait(lock);
                continue;
            } else {
                command = mCommandQueue.front();
                mMutexCommandQueue.unlock();
            }
            // Check if the socket is connected.
            if(mSocket->is_connected()) {
                send_command(command);
                mMutexCommandQueue.lock();
                mCommandQueue.pop();
                mMutexCommandQueue.unlock();
                if(command == kCommandQuit)
                    close_connection();
            }
        }
    }

    void client_application_model::read_response(void) {
        std::uint16_t messageSize;
        std::size_t size;
        ias::reader * reader;

        if(mSocket->is_connected()) {
            messageSize = 0;
            reader = mSocket->get_reader();
            size = sizeof messageSize;
            if(size == reader->read_all(reinterpret_cast<char *>(&messageSize), size)) {
                messageSize = ntohs(messageSize);
                char buffer[messageSize + 1];
                size = static_cast<std::size_t>(messageSize);
                if(size == reader->read_all(buffer, size)) {
                    buffer[size] = 0;
                    notify_observers(buffer);
                }
            }
        }
    }

    void client_application_model::read_responses(void) {
        std::uint8_t type;
        ias::reader * reader;

        // Checking the precondition.
        assert(mSocket->is_connected());

        reader = mSocket->get_reader();
        // Declare the undefined message type.
        type = 0xff;
        if(reader->read_byte(reinterpret_cast<char *>(&type)) == 1) {
            switch(type) {
            case 0x00:
                send_heartbeat();
                break;
            case 0x01:
                read_response();
                break;
            default:
                close_connection();
                break;
            }
        }
    }

    void client_application_model::send_command(const std::string & command) {
        static const std::uint8_t type = 0x01;
        std::size_t commandLength;
        std::uint8_t header[2];
        ias::writer * writer;

        // Checking the precondition.
        assert(command != kCommandQuit && command.length() <= 0xff);

        writer = mSocket->get_writer();
        commandLength = command.length();
        writer->lock();
        // Prepare the header.
        // Header layout:
        // 0: message type identifier (0x01)
        // 1: data length
        header[0] = type;
        header[1] = static_cast<std::uint8_t>(commandLength);
        writer->write_all(reinterpret_cast<char *>(header), 2);
        writer->write_all(command.c_str(), commandLength);
        writer->unlock();
    }

    void client_application_model::send_heartbeat(void) {
        static const std::uint8_t beat_type = 0x00;
        ias::writer * writer;

        // Checking the precondition.
        assert(mSocket->is_connected());

        writer = mSocket->get_writer();
        writer->lock();
        writer->write_bytes(reinterpret_cast<const char *>(beat_type), 1);
        writer->unlock();
    }

    void client_application_model::set_socket_timeouts(void) {
        struct timeval tv;

        // Checking the precondition.
        assert(mSocket != nullptr);

        tv.tv_sec = 1;
        tv.tv_usec = 0;
        mSocket->set_receive_timeout(tv);
    }

    void client_application_model::start_communication_threads(void) {
        // Spawn the send thread if not allocated.
        if(mCommunicationThreadSend == nullptr) {
            mCommunicationThreadSend = new std::thread([this] {
                process_send_thread();
            });
        }
        // Spawn the receive thread if not allocated.
        if(mCommunicationThreadReceive == nullptr) {
            mCommunicationThreadReceive = new std::thread([this] {
                process_receive_thread();
            });
        }
    }

    void client_application_model::stop_communication_threads(void) {
        // Stop the sending thread.
        if(mCommunicationThreadSend != nullptr) {
            mLockSend.notify_one();
            mCommunicationThreadSend->join();
            delete mCommunicationThreadSend;
            mCommunicationThreadSend = nullptr;
        }
        // Stop the receive thread.
        if(mCommunicationThreadReceive != nullptr) {
            mCommunicationThreadReceive->join();
            delete mCommunicationThreadReceive;
            mCommunicationThreadReceive = nullptr;
        }
    }

    client_application_model::client_application_model(void) {
        initialize();
    }

    client_application_model::~client_application_model(void) {
        delete mSocket; mSocket = nullptr;
        SSL_CTX_free(mSslContext); mSslContext = nullptr;
    }

    void client_application_model::request_ssl(const bool flag) {
        // Checking the precondition.
        assert(mSocket == nullptr);

        if(flag) {
            if(mSslContext == nullptr)
                mSslContext = SSL_CTX_new(SSLv23_client_method());
        } else {
            if(mSslContext != nullptr) {
                SSL_CTX_free(mSslContext);
                mSslContext = nullptr;
            }
        }
    }

    bool client_application_model::ssl_requested(void) const {
        return mSslContext != nullptr;
    }

    void client_application_model::close_connection(void) {
        if(mSocket != nullptr) {
            mSocket->close_connection();
            stop_communication_threads();
            delete mSocket;
            mSocket = nullptr;
            mLoggedIn = false;
        }
        notify_observers();
    }

    bool client_application_model::is_connected(void) const {
        return mSocket != nullptr && mSocket->is_connected();
    }

    bool client_application_model::logged_in(void) const {
        return mLoggedIn;
    }

    void client_application_model::create_connection(const std::string & host,
                                                     const std::size_t port) {
        int fd;

        // Checking the precondition.
        assert(!host.empty() && port > 0 && !is_connected());

        fd = ias::connect(host, port);
        // Check if a connection could be establed.
        if(fd >= 0)
            initialize_connection(fd);
        notify_observers();
    }

    void client_application_model::create_connection(const std::string & host,
                                                     const std::size_t port,
                                                     const std::string & socksHost,
                                                     const std::size_t socksPort) {
        int fd;

        // Checking the precondition.
        assert(!host.empty() && port > 0 &&
               !socksHost.empty() && port > 0 &&
               !is_connected());

        fd = ias::connect_to_socks(socksHost, socksPort, host, port);
        // Check if a connection could be established.
        if(fd >= 0)
            initialize_connection(fd);
        notify_observers();
    }

    void client_application_model::execute(const std::string & command) {
        // Checking the precondition.
        assert(is_connected() && !command.empty() && command.length() <= 0xff);

        mMutexCommandQueue.lock();
        mCommandQueue.push(command);
        mLockSend.notify_one();
        mMutexCommandQueue.unlock();
    }

    void client_application_model::authorize(const std::string & username,
                                             const std::string & password) {
        static const std::uint8_t type = 0x00;
        std::size_t usernameLength;
        std::size_t passwordLength;
        std::uint8_t header[3];
        std::uint8_t byte;
        ias::writer * writer;
        ias::reader * reader;

        // Checking the precondition.
        assert(!username.empty() && username.length() <= 0xff &&
               !password.empty() && password.length() <= 0xff &&
               is_connected());

        writer = mSocket->get_writer();
        reader = mSocket->get_reader();
        usernameLength = username.length();
        passwordLength = password.length();
        // Construct the header of the authorisation message.
        // 0: message type (0x00).
        // 1: username length
        // 2: password length
        header[0] = type;
        header[1] = static_cast<std::uint8_t>(usernameLength);
        header[2] = static_cast<std::uint8_t>(passwordLength);
        // Authentication protocol for IAS 0.1.0
        writer->lock();
        writer->write_all(reinterpret_cast<const char *>(header), 2);
        writer->write_all(username.c_str(), usernameLength);
        writer->write_bytes(reinterpret_cast<const char *>(&header[2]), 1);
        writer->write_all(password.c_str(), passwordLength);
        writer->unlock();
        // Authentication protocol for IAS 0.2.0
        // writer->lock();
        // writer->write_all(reinterpret_cast<const char *>(header), 3);
        // writer->write_all(username.c_str(), usernameLength);
        // writer->write_all(password.c_str(), passwordLength);
        // writer->unlock()
        // Wait for the confirmation message.
        reader->lock();
        if(reader->read_byte(reinterpret_cast<char *>(&byte)) == 1 &&
           byte == type &&
           reader->read_byte(reinterpret_cast<char *>(&byte)) == 1 &&
           byte == 0x01) {
            mLoggedIn = true;
            stop_communication_threads();
            start_communication_threads();
        }
        reader->unlock();
        notify_observers();
    }

};
