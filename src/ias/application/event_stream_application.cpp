/**
 * An application which outputs the raw event stream data from the IAS server to
 * std::cout.
 *
 * @date                    18 January, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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
#include <string>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/event_stream_application.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventStreamApplication::initialize( void ) {
    mSocket = nullptr;
    mFlagRunning = true;
    mServicePort = kDefaultEventServerPort;
    mFlagSslRequested = false;
}

void EventStreamApplication::analyzeArguments( const int argc,
                                               const char ** argv ) {
    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    fetchServiceAddress(argc,argv);
    fetchSslRequested(argc,argv);
}

void EventStreamApplication::fetchServiceAddress( const int argc,
                                                  const char ** argv ) {
    std::string stringPort;

    // Fetch the specified address.
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagAddress) == 0 && (i + 1) < argc ) {
            mServiceAddress = std::string(argv[i + 1]);
            break;
        }
    }
    // Fetch the specified port.
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagPort) == 0 && (i + 1) < argc ) {
            stringPort = std::string(argv[i + 1]);
            break;
        }
    }
    // Parse port, if specified.
    if( !stringPort.empty() && isNumber(stringPort) ) {
        std::size_t port;

        port = strtoul(stringPort.c_str(),nullptr,0);
        if( port > 0 )
            mServicePort = port;
    }
}

void EventStreamApplication::fetchSslRequested( const int argc,
                                                const char ** argv ) {
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagSsl) == 0 ) {
            mFlagSslRequested = true;
            break;
        }
    }
}

void EventStreamApplication::connectToStream( void ) {
    // TODO Implement.
}

EventStreamApplication::EventStreamApplication( const int argc,
                                                const char ** argv ) {
    initialize();
    analyzeArguments(argc,argv);
}

EventStreamApplication::~EventStreamApplication( void ) {
    delete mSocket; mSocket = nullptr;
}

void EventStreamApplication::run( void ) {
    // TODO Implement.
}

void EventStreamApplication::stop( void ) {
    mFlagRunning = false;
}
