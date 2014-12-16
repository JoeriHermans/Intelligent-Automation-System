/**
 * An application which is responsible for handling the client inputs.
 *
 * @date                    Jul 17, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2013 Joeri HERMANS
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
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include <termios.h>
#include <sys/types.h>
#include <sstream>
#include <netinet/in.h>
#include <limits>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/application/client_application.h>
#include <ias/application/constants.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/network/proxy/socks.h>
#include <ias/network/util.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

inline void ClientApplication::initialize( void ) {
    writeMessage("Initializing client.");
    mSocket = nullptr;
    mLoggedIn = false;
    mSslContext = nullptr;
}

void ClientApplication::initializeSslContext( void ) {
    mSslContext = SSL_CTX_new(SSLv23_client_method());
}

void ClientApplication::analyzeArguments( const int argc,
                                          const char ** argv ) {
    std::string socksServer;
    std::string address;
    std::size_t port;
    int fd;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    address = fetchAddress(argc,argv);
    port = fetchPort(argc,argv);
    fd = -1;
    if( !(socksServer = fetchSocksServer(argc,argv)).empty() ) {
        fd = connectToSocksProxy(socksServer,address,port);
    } else {
        fd = connect(address,port);
    }
    if( fd >= 0 ) {
        if( sslRequested(argc,argv) ) {
            SSL * ssl;

            initializeSslContext();
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
}

int ClientApplication::connectToSocksProxy( const std::string & proxy,
                                            const std::string & clientAddress,
                                            const std::size_t clientPort ) const {
    std::istringstream iss(proxy);
    std::string proxyAddress;
    std::string strProxyPort;
    std::size_t proxyPort;
    int fd;

    // Checking the precondition.
    assert( !proxy.empty() );

    fd = -1;
    std::getline(iss,proxyAddress,':');
    std::getline(iss,strProxyPort);
    proxyPort = static_cast<std::size_t>(std::stoi(strProxyPort));
    if( !proxyAddress.empty() && proxyPort > 0 ) {
        // Connect to the remote proxy server.
        fd = connect(proxyAddress,proxyPort);
        if( fd >= 0 && !socksConnect(clientAddress,clientPort,fd) ) {
            close(fd);
            fd = -1;
        }
    }

    return ( fd );
}

std::string ClientApplication::fetchSocksServer( const int argc,
                                                 const char ** argv ) const {
    std::string server;

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(kFlagSocks,argv[i]) == 0 && (i + 1) < argc ) {
            server = argv[i + 1];
            break;
        }
    }

    return ( server );
}

std::string ClientApplication::fetchAddress( const int argc,
                                             const char ** argv ) const {
    std::string address;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagAddress) == 0 && (i + 1) < argc ) {
            address = argv[i + 1];
            break;
        }
    }
    if( address.empty() )
        address = kDefaultServerAddress;

    return ( address );
}

std::size_t ClientApplication::fetchPort( const int argc,
                                          const char ** argv ) const {
    std::size_t port;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    port = 0;
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagPort) == 0 && ( i + 1 ) < argc ) {
            port = static_cast<std::size_t>(atol(argv[i + 1]));
            break;
        }
    }
    if( port == 0 ) {
        if( sslRequested(argc,argv) )
            port = kDefaultUserServerPortSsl;
        else
            port = kDefaultUserServerPort;
    }

    return ( port );
}

bool ClientApplication::sslRequested( const int argc , const char ** argv ) const {
    bool sslRequested;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    sslRequested = false;
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagSsl) == 0 ) {
            sslRequested = true;
            break;
        }
    }

    return ( sslRequested );
}

void ClientApplication::login( void ) {
    struct termios tty;
    std::string username;
    std::string password;
    Reader * reader;
    Writer * writer;
    std::uint8_t type;
    std::uint8_t byte;

    reader = mSocket->getReader();
    writer = mSocket->getWriter();
    writeMessage("Client initialized.");
    std::cout << kVersion << std::endl;
    std::cout << "Username: ";
    std::cin >> username;
    tcgetattr(STDIN_FILENO,&tty);
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO,TCSANOW,&tty);
    std::cout << "Password: ";
    std::cin >> password;
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO,TCSANOW,&tty);
    if( mSocket->isConnected() ) {
        writeMessage("Authenticating...");
        type = 0x00;
        byte = static_cast<std::uint8_t>(username.length());
        writer->writeBytes(reinterpret_cast<char *>(&type),1);
        writer->writeBytes(reinterpret_cast<char *>(&byte),1);
        writer->writeBytes(username.c_str(),byte);
        byte = static_cast<std::uint8_t>(password.length());
        writer->writeByte(byte);
        writer->writeBytes(password.c_str(),byte);
        byte = 0xff;
        if( reader->readByte(reinterpret_cast<char *>(&byte)) == 1 &&
            byte == 0x00 &&
            reader->readByte(reinterpret_cast<char *>(&byte)) == 1 &&
            byte == 0x01 ) {
            mLoggedIn = true;
            mUsername = username;
            writeMessage("Authenticated.");
        } else {
            writeMessage("Authentication failed.");
        }
    }
}

void ClientApplication::writeMessage( const std::string & message ) const {
    std::cout << "> " << message << std::endl;
}

void ClientApplication::responseHeartbeat( void ) {
    static const char beat = 0x00;
    Writer * writer;

    writer = mSocket->getWriter();
    writer->writeByte(beat);
}

void ClientApplication::responseMessage( void ) {
    Reader * reader;
    std::size_t nBytes;
    std::size_t bytesRead;
    std::uint16_t messageSize;

    reader = mSocket->getReader();
    messageSize = 0;
    reader->readBytes(reinterpret_cast<char *>(&messageSize),2);
    messageSize = ntohs(messageSize);
    bytesRead = 0;
    char buffer[messageSize + 1];
    while( mSocket->isConnected() && bytesRead < messageSize ) {
        nBytes = reader->readBytes(buffer+bytesRead,messageSize-bytesRead);
        if( nBytes == 0 )
            break;
        bytesRead += nBytes;
    }
    buffer[messageSize] = 0;
    puts(buffer);
}

void ClientApplication::readResponse( void ) {
    Reader * reader;
    std::uint8_t type;

    reader = mSocket->getReader();
    type = 0xff;
    while( mSocket->isConnected() &&
           reader->readBytes(reinterpret_cast<char *>(&type),1) == 1 ) {
        switch(type) {
        case 0x00:
            std::cout << "Respond to heartbeat" << std::endl;
            responseHeartbeat();
            break;
        case 0x01:
            responseMessage();
            break;
        }
    }
}

void ClientApplication::processCommands( void ) {
    std::string prefix;
    std::string command;
    std::string identifier;
    Writer * writer;
    std::uint8_t b;
    std::uint8_t bytesWritten;
    std::size_t n;

    writer = mSocket->getWriter();
    prefix = "[" + mUsername + "@ias]$ ";
    std::cin.clear();
    std::cin.ignore();
    while( mSocket->isConnected() ) {
        std::cout << prefix;
        std::getline(std::cin,command);
        trim(command);
        if( command.length() > 0 ) {
            if( command == std::string("quit") ) {
                mSocket->closeConnection();
                continue;
            }
            b = 0x01;
            writer->writeBytes(reinterpret_cast<char *>(&b),1);
            if( command.length() > 0xff ) {
                b = 0xff;
                writeMessage("Command exceeded max size, writing 255 bytes.");
            } else {
                b = static_cast<std::uint8_t>(command.length());
            }
            writer->writeBytes(reinterpret_cast<char *>(&b),1);
            bytesWritten = 0;
            while( mSocket->isConnected() && bytesWritten < b ) {
                n = writer->writeBytes(command.c_str() + bytesWritten,
                                       b - bytesWritten);
                if( n == 0 )
                    break;
                bytesWritten += n;
            }
            std::stringstream ss;

            readResponse();
            ss << command;
            ss >> identifier;
            trim(identifier);
            if( identifier == "stop" ) {
                mSocket->closeConnection();
            }
        }
    }
    writeMessage("Disconnected.");
}

ClientApplication::ClientApplication( const int argc , const char ** argv ) {
    initialize();
    analyzeArguments(argc,argv);
}

ClientApplication::~ClientApplication( void ) {
    delete mSocket; mSocket = nullptr;
    if( mSslContext != nullptr ) {
        SSL_CTX_free(mSslContext);
        mSslContext = nullptr;
    }
}

void ClientApplication::run( void ) {
    if( mSocket != nullptr && mSocket->isConnected() ) {
        login();
        if( mLoggedIn )
            processCommands();
    }
}

void ClientApplication::stop( void ) {
    if( mSocket != nullptr )
        mSocket->closeConnection();
}
