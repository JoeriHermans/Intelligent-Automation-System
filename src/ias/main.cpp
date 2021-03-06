/**
 * A set of functions and method which assist the main function to set up
 * the requested feature of the Intelligent Automation System.
 *
 * @date                    Jul 2, 2014
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
#include <string>
#include <iostream>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/client/client_application.h>
#include <ias/application/controller_application.h>
#include <ias/application/server_application.h>
#include <ias/application/event_stream_application.h>
#include <ias/application/add_controller/add_controller_application.h>
#include <ias/application/hash_generation/hash_generation_application.h>
#include <ias/main.h>
#include <ias/util/util.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

void initializeRandomGenerator( void ) {
    srand((unsigned int) time(0));
}

int main( const int argc , const char ** argv ) {
    if( flagSpecified(argc,argv,kFlagLogo) )
        displayLogo();
    initializeRandomGenerator();
    initializeSsl();
    // Not the most beautiful piece of initialization code :)
    if( controllerRequested(argc,argv) )
        startController(argc,argv);
    else
    if( serverRequested(argc,argv) )
        startServer(argc,argv);
    else
    if( clientRequested(argc,argv) )
        startClient(argc,argv);
    else
    if( eventStreamRequested(argc,argv) )
        startEventStream(argc,argv);
    else
    if( generateHashRequested(argc,argv) )
        startGenerateHash(argc,argv);
    else
    if( addControllerRequested(argc,argv) )
        startAddController(argc,argv);
    else
        usage();
    cleanupSsl();
    cleanupLogger();

    return EXIT_SUCCESS;
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

void startEventStream( const int argc , const char ** argv ) {
    EventStreamApplication application(argc,argv);

    application.run();
}

void startGenerateHash( const int argc , const char ** argv ) {
    HashGenerationApplication application(argc,argv);

    application.run();
}

void startAddController( const int argc , const char ** argv ) {
    AddControllerApplication application(argc,argv);

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

bool eventStreamRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagEventStream) );
}

bool generateHashRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagGenerateHash) );
}

bool addControllerRequested( const int argc , const char ** argv ) {
    return ( flagSpecified(argc,argv,kFlagAddController) );
}

void usage( void ) {
    std::cout << kVersion << std::endl;
    std::cout << "Basic usage: " << std::endl;
    std::cout << "Run as server: ias --server --config <path>" << std::endl;
    std::cout << "Run as controller: ias --controller --config <path>" << std::endl;
    std::cout << "Run as client: ias --client [options]" << std::endl;
    std::cout << "Run as eventstream: ias --eventstream --key <API key> [options]" << std::endl;
    std::cout << "Generate hash: ias --hash <string> --config <path>" << std::endl;
    std::cout << "Add controller: ias --addc" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << " --address [hostname]" << std::endl;
    std::cout << " --ssl" << std::endl;
    std::cout << " --logo" << std::endl;
}

void initializeSsl( void ) {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void cleanupSsl( void ) {
    CONF_modules_free();
    ERR_remove_state(0);
    ENGINE_cleanup();
    CONF_modules_unload(1);
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
}

void cleanupLogger( void ) {
    Logger::cleanup();
}

void displayLogo( void ) {
    std::cout << " __    ______    ______    " << std::endl;
    std::cout << "/\\ \\  /\\  __ \\  /\\  ___\\   " << std::endl;
    std::cout << "\\ \\ \\ \\ \\  __ \\ \\ \\___  \\  " << std::endl;
    std::cout << " \\ \\_\\ \\ \\_\\ \\_\\ \\/\\_____\\ " << std::endl;
    std::cout << "  \\/_/  \\/_/\\/_/  \\/_____/ " << std::endl;
    std::cout << std::endl << std::endl;
}
