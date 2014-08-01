/**
 * A set of functions and method which assist the main function to set up
 * the requested feature of the Intelligent Automation System.
 *
 * @date                    Jul 2, 2014
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
#include <string>
#include <iostream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/client_application.h>
#include <ias/application/controller_application.h>
#include <ias/application/server_application.h>
#include <ias/main.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

int main( const int argc , const char ** argv ) {
    if( controllerRequested(argc,argv) )
        startController(argc,argv);
    else
    if( serverRequested(argc,argv) )
        startServer(argc,argv);
    else
    if( clientRequested(argc,argv) )
        startClient(argc,argv);
    else
        usage();
    
    return ( 0 );
}

void startController( const int argc , const char ** argv ) {
    ControllerApplication application(argc,argv);
    
    application.run();
}

void startClient( const int argc , const char ** argv ) {
    ClientApplication application(argc,argv);
    
    application.run();
}

void startServer( const int argc , const char ** argv ) {
    ServerApplication application(argc,argv);
    
    application.run();
}

bool serverRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagServer) );
}

bool clientRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagClient) );
}

bool controllerRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagController) );
}

void usage( void ) {
    std::cout << kVersion << std::endl;
    std::cout << "Basic usage: " << std::endl;
    std::cout << "Run as server: ias --server --config <path>" << std::endl;
    std::cout << "Run as controller: ias --controller --config <path>" << std::endl;
    std::cout << "Run as client: ias --client [options]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " --address [hostname]" << std::endl;
}
