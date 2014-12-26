/**
 * A class which describes the properties and actions of a client application.
 *
 * @date                    December 25, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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
#include <vector>
#include <unistd.h>
#include <netinet/in.h>

// Application dependencies.
#include <ias/application/client/model/client_application_model.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/network/proxy/socks.h>
#include <ias/network/util.h>

// END Includes. /////////////////////////////////////////////////////

void ClientApplicationModel::initialize( void ) {
    mSocket = nullptr;
    mSslContext = nullptr;
    mSocksHost.clear();
    mSocksPort = 0;
    mLoggedIn = false;
}

void ClientApplicationModel::setSocketTimeouts( void ) {
    struct timeval tv;

    // Checking the precondition.
    assert( mSocket != nullptr );

    tv.tv_sec = 10;
    tv.tv_usec = 0;
    mSocket->setReceiveTimeout(tv);
}

int ClientApplicationModel::connectToSocksProxy( const std::string & host,
                                                 const std::size_t port ) const {
    int fd;

    fd = connectToSocks(mSocksHost,mSocksPort,host,port);

    return ( fd );
}

void ClientApplicationModel::readResponses( void ) {
    std::uint8_t messageType;
    Reader * reader;

    // Checking the precondition.
    assert( mSocket->isConnected() );

    reader = mSocket->getReader();
    messageType = 0xff;
    if( reader->readBytes(reinterpret_cast<char *>(&messageType),1) == 1 ) {
        switch(messageType) {
        case 0x01:
            readResponse();
            break;
        }
    }
}

void ClientApplicationModel::readResponse( void ) {
    Reader * reader;
    std::uint16_t messageSize;

    // Checking the precondition.
    assert( mSocket->isConnected() );

    reader = mSocket->getReader();
    messageSize = 0;
    reader->readBytes(reinterpret_cast<char *>(&messageSize),
                      sizeof(messageSize));
    messageSize = ntohs(messageSize);
    char buffer[messageSize + 1];
    reader->readBytes(buffer,static_cast<std::size_t>(messageSize));
    buffer[messageSize] = 0;
    notifyObservers(buffer);
}

ClientApplicationModel::ClientApplicationModel( void ) {
    initialize();
}

ClientApplicationModel::~ClientApplicationModel( void ) {
    delete mSocket; mSocket = nullptr;
    SSL_CTX_free(mSslContext); mSslContext = nullptr;
}

void ClientApplicationModel::setProxy( const std::string & host,
                                       const std::size_t port ) {
    mSocksHost = host;
    mSocksPort = port;
}

bool ClientApplicationModel::proxySpecified( void ) const {
    return ( !mSocksHost.empty() && mSocksPort > 0 );
}

void ClientApplicationModel::closeConnection( void ) {
    if( mSocket != nullptr ) {
        mSocket->closeConnection();
        delete mSocket;
        mSocket = nullptr;
        mLoggedIn = false;
    }
    notifyObservers();
}

void ClientApplicationModel::requestSsl( const bool flag ) {
    // Checking the precondition.
    assert( mSocket == nullptr );

    if( flag ) {
        if( mSslContext == nullptr )
            mSslContext = SSL_CTX_new(SSLv23_client_method());
    } else {
        if( mSslContext != nullptr ) {
            SSL_CTX_free(mSslContext);
            mSslContext = nullptr;
        }
    }
}

bool ClientApplicationModel::sslRequested( void ) const {
    return ( mSslContext != nullptr );
}

bool ClientApplicationModel::isConnected( void ) const {
    return ( mSocket != nullptr && mSocket->isConnected() );
}

void ClientApplicationModel::createConnection( const std::string & host,
                                               const std::size_t port ) {
    int fd;

    // Checking the precondition.
    assert( !host.empty() && port > 0 && !isConnected() );

    fd = -1;
    // Initialize the connection with the remote IAS service.
    if( proxySpecified() )
        fd = connectToSocksProxy(host,port);
    else
        fd = connect(host,port);
    // Check if a connection could be established.
    if( fd >= 0 ) {
        if( sslRequested() ) {
            SSL * ssl;

            ssl = SSL_new(mSslContext);
            SSL_set_fd(ssl,fd);
            if( SSL_connect(ssl) <= 0 ) {
                SSL_free(ssl);
                close(fd);
            } else {
                mSocket = new PosixSslSocket(ssl);
            }
        } else {
            mSocket = new PosixTcpSocket(fd);
        }
    }
    notifyObservers();
}

bool ClientApplicationModel::isLoggedIn( void ) const {
    return ( mLoggedIn );
}

void ClientApplicationModel::authorize( const std::string & username,
                                        const std::string & password ) {
    static const std::uint8_t message_type = 0x00;
    std::uint8_t byte;
    Writer * writer;
    Reader * reader;

    // Checking the precondition.
    assert( !username.empty() && username.length() <= 0xff &&
            !password.empty() && !password.length() <= 0xff &&
            mSocket != nullptr );

    if( mSocket->isConnected() ) {
        writer = mSocket->getWriter();
        reader = mSocket->getReader();
        // Send the message type.
        writer->writeBytes(reinterpret_cast<const char *>(&message_type),1);
        // Send the username length and username.
        byte = static_cast<std::uint8_t>(username.length());
        writer->writeBytes(reinterpret_cast<const char *>(&byte),1);
        writer->writeBytes(username.c_str(),byte);
        // Send the password length and password.
        byte = static_cast<std::uint8_t>(password.length());
        writer->writeBytes(reinterpret_cast<const char *>(&byte),1);
        writer->writeBytes(password.c_str(),byte);
        // Check if authentication is successful.
        if( reader->readByte(reinterpret_cast<char *>(&byte)) == 1 &&
            byte == 0x00 &&
            reader->readByte(reinterpret_cast<char *>(&byte)) == 1 &&
            byte == 0x01 ) {
            mLoggedIn = true;
        }
    }
    notifyObservers();
}

void ClientApplicationModel::execute( const std::string & command ) {
    static const std::uint8_t message_type = 0x01;
    Writer * writer;
    std::uint8_t bytesWritten;
    std::uint8_t commandLength;
    std::uint8_t dBytes;
    std::size_t n;

    // Checking the precondition.
    assert( isConnected() && !command.empty() && command.length() <= 0xff );

    writer = mSocket->getWriter();
    writer->writeBytes(reinterpret_cast<const char *>(&message_type),1);
    // Retrieve the command's length.
    commandLength = static_cast<std::uint8_t>(command.length());
    writer->writeBytes(reinterpret_cast<const char *>(&commandLength),1);
    bytesWritten = 0;
    while( mSocket->isConnected() && bytesWritten < commandLength ) {
        dBytes = commandLength - bytesWritten;
        n = writer->writeBytes(command.c_str() + bytesWritten,dBytes);
        if( n == 0 )
            break;
        bytesWritten += n;
    }
    readResponses();
}
