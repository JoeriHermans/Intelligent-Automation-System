/**
 * A class which describes the properties and actions of an SSL server socket.
 *
 * @date                    August 22, 2014
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
#include <arpa/inet.h>
#include <cassert>
#include <cstring>
#include <ctime>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>

// Application dependencies.
#include <ias/network/posix/ssl/posix_ssl_server_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void PosixSslServerSocket::initialize( void ) {
    mSslContext = nullptr;
}

void PosixSslServerSocket::setFileDescriptor( const int fd ) {
    mFileDescriptor = fd;
}

void PosixSslServerSocket::loadCertificates( const std::string & certificateFile,
                                             const std::string & keyFile ) {
    SSL_CTX * sslContext;
    int rc;

    sslContext = SSL_CTX_new(SSLv3_server_method());
    rc = SSL_CTX_load_verify_locations(sslContext,certificateFile.c_str(),keyFile.c_str());
    if( rc < 0 )
        loge("Error verifing certificate locations.");
    rc = SSL_CTX_set_default_verify_paths(sslContext);
    if( rc < 0 )
        loge("Can't set default verification paths.");
    rc = SSL_CTX_use_certificate_file(sslContext,certificateFile.c_str(),SSL_FILETYPE_PEM);
    if( rc < 0 )
        loge("Can't use \"" + certificateFile + "\" as a certificate file.");
    rc = SSL_CTX_use_PrivateKey_file(sslContext,keyFile.c_str(),SSL_FILETYPE_PEM);
    if( rc < 0 )
        loge("Can't use \"" + keyFile + "\" as a keyfile.");
    setSslContext(sslContext);
}

void PosixSslServerSocket::setSslContext( SSL_CTX * sslContext ) {
    // Checking the precondition.
    assert( sslContext != nullptr );

    mSslContext = sslContext;
}

Socket * PosixSslServerSocket::allocateSocket( const int fd ) const {
    Socket * socket;
    SSL * ssl;

    // Checking the precondition.
    assert( fd >= 0 );

    ssl = SSL_new(mSslContext);
    SSL_set_fd(ssl, fd);
    socket = new PosixSslSocket(ssl);

    return ( socket );
}

PosixSslServerSocket::PosixSslServerSocket( const unsigned int port,
                                            SSL_CTX * sslContext ) :
    ServerSocket(port) {
    initialize();
    setFileDescriptor(-1);
    setSslContext(sslContext);
}

PosixSslServerSocket::PosixSslServerSocket( const unsigned int port,
                                            const std::string & certificatFile,
                                            const std::string & keyFile ) :
    ServerSocket(port) {
    initialize();
    setFileDescriptor(-1);
    loadCertificates(certificatFile,keyFile);
}

PosixSslServerSocket::~PosixSslServerSocket( void ) {
    stopListening();
}

void PosixSslServerSocket::stopListening( void ) {
    if( isBound() ) {
        close(mFileDescriptor);
        setFileDescriptor(-1);
        SSL_CTX_free(mSslContext);
        mSslContext = nullptr;
    }
}

bool PosixSslServerSocket::bindToPort( void ) {
    struct addrinfo hints;
    struct addrinfo * serverInfo;
    std::string portString;
    bool bound;
    int fd;

    if( isBound() ) {
        bound = true;
    } else {
        bound = false;
        memset(&hints,0,sizeof hints);
        hints.ai_family = AF_UNSPEC;
        hints.ai_socktype = SOCK_STREAM;
        hints.ai_flags = AI_PASSIVE;
        portString = std::to_string(getPort());
        if( getaddrinfo(nullptr,portString.c_str(),&hints,&serverInfo) == 0 ) {
            fd = socket(serverInfo->ai_family,serverInfo->ai_socktype,
                        serverInfo->ai_protocol);
            if( fd >= 0 ) {
                int yes = 1;

                setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&yes,sizeof yes);
                if( bind(fd,serverInfo->ai_addr,serverInfo->ai_addrlen) == 0 &&
                    listen(fd,20) == 0 ) {
                    bound = true;
                    FD_ZERO(&mRfds);
                    FD_SET(fd,&mRfds);
                    setFileDescriptor(fd);
                }
            }
            freeaddrinfo(serverInfo);
        }
    }

    return ( bound );
}

bool PosixSslServerSocket::isBound( void ) const {
    return ( mFileDescriptor >= 0 );
}

Socket * PosixSslServerSocket::acceptSocket( void ) {
    struct sockaddr addr;
    socklen_t addrLength;
    Socket * socket;
    int fd;

    socket = nullptr;
    if( isBound() ) {
        memset(&addr,0,sizeof addr);
        memset(&addrLength,0,sizeof addrLength);
        fd = accept(mFileDescriptor,&addr,&addrLength);
        if( fd >= 0 ) {
            socket = allocateSocket(fd);
        }
    }

    return ( socket );
}

Socket * PosixSslServerSocket::acceptSocket( const std::time_t seconds ) {
    struct sockaddr addr;
    socklen_t addrLength;
    timeval tv;
    Socket * socket;
    int fd;

    socket = nullptr;
    tv.tv_sec = seconds;
    tv.tv_usec = 0;
    FD_ZERO(&mRfds);
    FD_SET(mFileDescriptor,&mRfds);
    if( isBound() &&
        select(mFileDescriptor + 1,&mRfds,nullptr,nullptr,&tv) > 0 ) {
        memset(&addr,0,sizeof addr);
        memset(&addrLength,0,sizeof addrLength);
        fd = accept(mFileDescriptor,&addr,&addrLength);
        if( fd >= 0 ) {
            socket = allocateSocket(fd);
        }
    }

    return ( socket );
}
