/**
 * A class which describes the abstract properties and actions of a
 * controller.
 *
 * @date                    Jun 2, 2014
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
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

// Application dependencies.
#include <ias/application/controller_application.h>
#include <ias/application/constants.h>
#include <ias/server/device_server.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/posix_tcp_server_socket.h>
#include <ias/network/posix/ssl/posix_ssl_socket.h>
#include <ias/network/proxy/socks.h>
#include <ias/network/util.h>
#include <ias/logger/logger.h>
#include <ias/logger/file/file_logger.h>
#include <ias/logger/console/console_logger.h>

// END Includes. /////////////////////////////////////////////////////

void ControllerApplication::initialize( void ) {
    mSocket = nullptr;
    mDeviceServer = nullptr;
}

void ControllerApplication::setup( const int argc , const char ** argv ) {
    int index;

    // Retrieve the configuration file path.
    index = flagIndex(argc,argv,kFlagConfig);
    if( index >= 0 && (index + 1) <= argc && strlen(argv[index + 1]) > 0 ) {
        std::string configurationPath;

        configurationPath = argv[index + 1];
        readConfiguration(configurationPath);
        initializeLogger();
        connectToServer();
        if( mSocket != nullptr ) {
            authenticateWithServer();
            if( mSocket->isConnected() ) {
                readDevices();
                allocateDeviceServer();
                if( mDeviceServer != nullptr )
                    startDeviceProcesses();
            }
        }
    }
}

void ControllerApplication::readConfiguration( const std::string & filePath ) {
    std::ifstream file(filePath);
    std::string line;
    std::string key;
    std::string value;
    std::size_t i;

    // Checking the precondition.
    assert( !filePath.empty() );

    while( std::getline(file,line) ) {
        trim(line);
        if( line.empty() || line.at(0) == '#' )
            continue;
        i = line.find('=');
        key = line.substr(0,i);
        value = line.substr(i + 1,line.length());
        trim(key); trim(value);
        if( !key.empty() && !value.empty() )
            mProperties.add(key,value);
    }
    file.close();
}

void ControllerApplication::initializeSslContext( void ) {
    mSslContext = SSL_CTX_new(SSLv23_client_method());
}

bool ControllerApplication::sslRequested( void ) const {
    return ( !mProperties.get(kConfigHostSslEnabled).empty() );
}

int ControllerApplication::connectToProxy( const std::string & proxyAddress,
                                           const std::string & proxyPort,
                                           const std::string & serverAddress,
                                           const std::string & serverPort ) const {
    std::size_t pPort;
    std::size_t sPort;
    int fd;

    // Checking the precondition.
    assert( !proxyAddress.empty() && !proxyPort.empty() &&
            !serverAddress.empty() && !serverPort.empty() );

    fd = -1;
    // Parse the specified ports.
    pPort = static_cast<std::size_t>(std::stoi(proxyPort));
    sPort = static_cast<std::size_t>(std::stoi(serverPort));
    if( sPort > 0 && pPort > 0 ) {
        fd = connect(proxyAddress,pPort);
        if( fd >= 0 && !socksConnect(serverAddress,sPort,fd) ) {
            close(fd);
            fd = -1;
        }
    }

    return ( fd );
}

void ControllerApplication::connectToServer( void ) {
    const std::string & serverAddress = mProperties.get(kConfigHost);
    const std::string & serverPort = mProperties.get(kConfigHostPort);
    const std::string & proxyAddress = mProperties.get(kConfigSocksAddress);
    const std::string & proxyPort = mProperties.get(kConfigSocksPort);
    std::size_t port;
    int fd;

    fd = -1;
    if( !proxyAddress.empty() && !proxyPort.empty() ) {
        fd = connectToProxy(proxyAddress,proxyPort,
                            serverAddress,serverPort);
    } else {
        port = static_cast<std::size_t>(std::stoi(serverPort));
        fd = connect(serverAddress,port);
    }
    // Check if a successful connection could be made.
    if( fd >= 0 ) {
        if( sslRequested() ) {
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

std::size_t ControllerApplication::getServerPort( void ) const {
    const std::string & serverPort = mProperties.get(kConfigHostPort);
    std::size_t port;

    if( serverPort.empty() ||
        (port = static_cast<std::size_t>(std::stoi(serverPort))) == 0 )
        port = kDefaultControllerServerPort;

    return ( port );
}

void ControllerApplication::readDevices( void ) {
    std::string filePath;

    filePath = mProperties.get(kConfigDeviceList);
    if( filePath.empty() )
        return;

    std::ifstream file(filePath);
    std::string line;
    std::string deviceIdentifier;
    std::string deviceBash;

    logi("Retrieving devices.");
    while( std::getline(file,line) ) {
        trim(line);
        if( line.empty() || line.at(0) == '#' )
            continue;
        deviceIdentifier = line;
        std::getline(file,line);
        trim(line);
        if( line.empty() || line.at(0) == '#' )
            return;
        deviceBash = line;
        logi("Adding " + deviceIdentifier + ".");
        mDevices.push_back(deviceIdentifier);
        mDeviceCommands.push_back(deviceBash);
    }
    file.close();
    logi("Devices have been read.");
}

void ControllerApplication::allocateDeviceServer( void ) {
    ServerSocket * serverSocket;
    std::string stringPort;
    unsigned int port;

    if( mProperties.contains(kConfigNetworkDevicePort) )
        stringPort = mProperties.get(kConfigNetworkDevicePort);
    if( !stringPort.empty() )
        port = static_cast<unsigned int>(atol(stringPort.c_str()));
    else
        port = kDefaultDeviceServerPort;
    logi("Allocating device server at port " + std::to_string(port) + ".");
    serverSocket = new PosixTcpServerSocket(port);
    if( serverSocket->bindToPort() ) {
        mDeviceServer = new DeviceServer(serverSocket,
                                         mSocket,
                                         mDevices);
        logi("Device server has been allocated.");
    } else {
        delete serverSocket;
        loge("Could not bind device server to port " + std::to_string(port) + ".");
    }
}

void ControllerApplication::authenticateWithServer( void ) {
    std::uint8_t header[3];
    std::string message;
    std::size_t n;
    Writer * writer;
    bool success;

    const std::string & controllerIdentifier =
        mProperties.get(kConfigControllerIdentifier);
    const std::string & securityCode =
        mProperties.get(kConfigControllerSecurityCode);

    if( controllerIdentifier.empty() ||
        securityCode.empty() ) {
        stop();
        loge("Authentication credentials missing.");
        return;
    }

    logi("Authenticating with server.");
    success = true;
    header[0] = 0x00;
    header[1] = static_cast<std::uint8_t>(controllerIdentifier.length());
    header[2] = static_cast<std::uint8_t>(securityCode.length());
    message = controllerIdentifier + securityCode;
    writer = mSocket->getWriter();
    writer->lock();
    n = writer->writeBytes(reinterpret_cast<const char *>(header),3);
    success &= ( n > 0 );
    n = writer->writeBytes(reinterpret_cast<const char *>(message.c_str()),
                           message.length());
    success &= ( n > 0 );
    writer->unlock();
    if( !success ) {
        mSocket->closeConnection();
        logi("Authentication failed.");
    } else {
        logi("Authenticated.");
    }
}

void ControllerApplication::startDeviceProcesses( void ) {
    std::string path;
    std::string argument;
    std::size_t nArguments;
    pid_t processId;
    int status;

    logi("Starting devices processes.");
    for( auto it = mDeviceCommands.begin() ;  it != mDeviceCommands.end() ; ++it ) {
        const std::string & command = (*it);
        std::stringstream ss;

        ss << command;
        ss >> path;
        nArguments = numWords(command);
        char * argv[nArguments + 1];
        argv[nArguments] = static_cast<char *>(0);
        argv[0] = new char[path.length() + 1];
        strcpy(argv[0],path.c_str());
        for( std::size_t i = 1 ; i < nArguments ; ++i ) {
            ss >> argument;
            argv[i] = new char[argument.length() + 1];
            strcpy(argv[i],argument.c_str());
        }
        status = posix_spawn(&processId,path.c_str(),nullptr,nullptr,
                             argv,nullptr);
        if( status == 0 ) {
            mPids.push_back(processId);
        }
        for( std::size_t i = 0 ; i < nArguments ; ++i )
            delete [] argv[i];
    }
    logi("Device processes have been started.");
}

void ControllerApplication::cleanupDeviceProcesses( void ) {
    int status;
    std::size_t n;

    n = mPids.size();
    for( std::size_t i = 0 ; i < n ; ++i ) {
        waitpid(mPids.at(i),&status,0);
    }
}

void ControllerApplication::initializeLogger( void ) {
    std::string type;

    if( mProperties.contains(kConfigLoggerType) ) {
        type = mProperties.get(kConfigLoggerType);
        if( type == std::string(ConsoleLogger::kType) ) {
            Logger::setLogger(new ConsoleLogger());
            std::cout.flush();
        } else
        if( type == std::string(FileLogger::kType) &&
            mProperties.contains(kConfigLoggerLogfilePath) ) {
            std::string logfile = mProperties.get(kConfigLoggerLogfilePath);
            if( !logfile.empty() )
                Logger::setLogger(new FileLogger(logfile));
        }
    }
}

ControllerApplication::ControllerApplication( const int argc,
                                              const char ** argv ) {
    initialize();
    setup(argc,argv);
}

ControllerApplication::~ControllerApplication( void ) {
    delete mSocket; mSocket = nullptr;
    delete mDeviceServer; mDeviceServer = nullptr;
    cleanupDeviceProcesses();
}

void ControllerApplication::run( void ) {
    if( mDeviceServer != nullptr ) {
        logi("Starting device server.");
        mDeviceServer->start();
        logi("Device server has been started.");
        mDeviceServer->join();
        logi("Device server has been stopped.");
    }
}

void ControllerApplication::stop( void ) {
    if( mDeviceServer != nullptr ) {
        logi("Stopping the device server.");
        mDeviceServer->stop();
        mSocket->closeConnection();
    }
}
