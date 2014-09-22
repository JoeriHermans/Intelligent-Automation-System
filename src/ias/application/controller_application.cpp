/**
 * A class which describes the abstract properties and actions of a
 * controller.
 *
 * @date                    Jun 2, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
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
#include <sys/types.h>
#include <sys/wait.h>

// Application dependencies.
#include <ias/application/controller_application.h>
#include <ias/application/constants.h>
#include <ias/server/device_server.h>
#include <ias/network/posix/posix_tcp_socket.h>
#include <ias/network/posix/posix_tcp_server_socket.h>

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
        connectToServer();
        if( mSocket != nullptr ) {
            authenticateWithServer();
            if( mSocket->isConnected() ) {
                readDevices();
                allocateDeviceServer();
                if( mDeviceServer != nullptr )
                    startDeviceProcesses();
            } else {
                std::cout << "Could not authenticate with the remote server." << std::endl;
            }
        } else {
            std::cout << "Could not connect to the server." << std::endl;
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

void ControllerApplication::connectToServer( void ) {
    unsigned int port;
    Socket * socket;
    
    const std::string & serverAddress = mProperties.get(kConfigHost);
    const std::string & serverPort = mProperties.get(kConfigHostPort);
    
    if( !serverAddress.empty() ) {
        if( serverPort.empty() )
            port = kDefaultControllerServerPort;
        else
            port = (unsigned int) atol(serverPort.c_str());
        socket = new PosixTcpSocket();
        if( socket->createConnection(serverAddress,port) ) {
            mSocket = socket;
        } else {
            delete socket;
        }
    }
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
        mDevices.push_back(deviceIdentifier);
        mDeviceCommands.push_back(deviceBash);
    }
    file.close();
}

void ControllerApplication::allocateDeviceServer( void ) {
    ServerSocket * serverSocket;
    std::string stringPort;
    unsigned int port;
    
    if( mProperties.contains(kConfigNetworkDevicePort) )
        stringPort = mProperties.get(kConfigNetworkDevicePort);
    if( !stringPort.empty() )
        port = (unsigned int) atol(stringPort.c_str());
    else
        port = kDefaultDeviceServerPort;
    serverSocket = new PosixTcpServerSocket(port);
    if( serverSocket->bindToPort() ) {
        mDeviceServer = new DeviceServer(serverSocket,
                                         mSocket,
                                         mDevices);
    } else {
        delete serverSocket;
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
        return;
    }
    
    success = true;
    header[0] = 0x00;
    header[1] = (std::uint8_t) controllerIdentifier.length();
    header[2] = (std::uint8_t) securityCode.length();
    message = controllerIdentifier + securityCode;
    writer = mSocket->getWriter();
    writer->lock();
    n = writer->writeBytes((char *) header,3);
    success &= ( n > 0 );
    n = writer->writeBytes((char *) message.c_str(),message.length());
    success &= ( n > 0 );
    writer->unlock();
    if( !success )
        mSocket->closeConnection();
}

void ControllerApplication::startDeviceProcesses( void ) {
    std::string path;
    std::string argument;
    std::size_t nArguments;
    pid_t processId;
    char ** environ;
    int status;
    
    for( auto it = mDeviceCommands.begin() ;  it != mDeviceCommands.end() ; ++it ) {
        const std::string & command = (*it);
        std::stringstream ss;

        ss << command;
        ss >> path;
        nArguments = numWords(command);
        char * argv[nArguments + 1];
        argv[nArguments] = (char *) 0;
        argv[0] = new char[path.length() + 1];
        strcpy(argv[0],path.c_str());
        for( int i = 1 ; i < nArguments ; ++i ) {
            ss >> argument;
            argv[i] = new char[argument.length() + 1];
            strcpy(argv[i],argument.c_str());
        }
        status = posix_spawn(&processId,path.c_str(),nullptr,nullptr,
                             argv,nullptr);
        if( status == 0 ) {
            mPids.push_back(processId);
        }
        for( int i = 0 ; i < nArguments ; ++i )
            delete [] argv[i];
    }
}

void ControllerApplication::cleanupDeviceProcesses( void ) {
    int status;
    std::size_t n;
    
    n = mPids.size();
    for( int i = 0 ; i < n ; ++i ) {
        waitpid(mPids.at(i),&status,0);
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
        mDeviceServer->start();
        mDeviceServer->join();
    }
}

void ControllerApplication::stop( void ) {
    if( mDeviceServer != nullptr ) {
        mDeviceServer->stop();
        mSocket->closeConnection();
    }
}
