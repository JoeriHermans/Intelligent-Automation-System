/**
 * Utility functions used in the startup process of IAS. This will
 * initialise all crypographic libraries and start the application
 * requested by the user.
 *
 * @date                    28 04 2016
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
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/main.h>
#include <ias/application/constants.h>
#include <ias/application/client/client_application.h>
#include <ias/application/server/server_application.h>
#include <ias/database/mysql/mysql_database_connection.h>
#include <ias/database/postgresql/postgresql_database_connection.h>
#include <ias/logger/logger.h>
#include <ias/logger/console/console_logger.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

int main(const int argc, const char ** argv) {
    // Initialize dependencies.
    initialize_random_number_generator();
    initialize_ssl();
    // Start and run the desired application.
    run_application(argc, argv);
    // Do some cleanup.
    cleanup_logger();
    cleanup_ssl();
    cleanup_databases();

    return EXIT_SUCCESS;
}

void initialize_random_number_generator(void) {
    srand(static_cast<unsigned int>(time(0)));
}

void initialize_ssl(void) {
    SSL_load_error_strings();
    SSL_library_init();
    OpenSSL_add_all_algorithms();
}

void run_application(const int argc, const char ** argv) {
    if(requested_client(argc, argv))
        start_client(argc, argv);
    else if(requested_controller(argc, argv))
        start_controller(argc, argv);
    else if(requested_eventstream(argc, argv))
        start_eventstream(argc, argv);
    else if(requested_generate_hash(argc, argv))
        start_generate_hash(argc, argv);
    else if(requested_server(argc, argv))
        start_server(argc, argv);
    else if(requested_version(argc, argv))
        show_version();
    else
        usage();
}

bool requested_client(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagClient);
}

bool requested_controller(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagController);
}

bool requested_eventstream(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagEventStream);
}

bool requested_generate_hash(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagGenerateHash);
}

bool requested_server(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagServer);
}

bool requested_version(const int argc, const char ** argv) {
    return ias::flag_specified(argc, argv, kFlagVersion);
}

void start_client(const int argc, const char ** argv) {
    ias::client_application app(argc, argv);

    display_logo();
    std::cout << std::endl << std::flush;
    app.run();
}

void start_controller(const int argc, const char ** argv) {
    // TODO Add controller-startup.
}

void start_eventstream(const int argc, const char ** argv) {
    // TODO Add eventstream-startup.
}

void start_generate_hash(const int argc, const char ** argv) {
    // TODO Add generate hash startup.
}

void start_server(const int argc, const char ** argv) {
    display_logo();
    std::cout << std::endl << std::flush;
    ias::server_application app(argc, argv);
    app.run();
}

void show_version(void) {
    std::cout << ias::get_ias_version() << std::endl;
}

void cleanup_databases(void) {
    #ifdef IAS_DATABASE_DRIVER
    #if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'
    ias::mysql_database_connection::cleanup();
    #endif
    #endif
    #ifdef IAS_DATABASE_DRIVER
    #if IAS_DATABASE_DRIVER == 'P' || IAS_DATABASE_DRIVER == 'A'
    ias::postgresql_database_connection::cleanup();
    #endif
    #endif
}

void cleanup_logger(void) {
    ias::logger::cleanup();
}

void cleanup_ssl(void) {
    CONF_modules_free();
    ERR_remove_state(0);
    ENGINE_cleanup();
    CONF_modules_unload(1);
    ERR_free_strings();
    EVP_cleanup();
    CRYPTO_cleanup_all_ex_data();
}

void display_logo(void) {
    std::cout << std::endl << std::endl;
    std::cout << "    777   7777777777   7777777777" << std::endl;
    std::cout << "    777   777    777   777               Intelligent Automation System" << std::endl;
    std::cout << "    777   7777777777   7777777777" << std::endl;
    std::cout << "    777   777    777          777            ias.joerihermans.com" << std::endl;
    std::cout << "    777   777    777   7777777777" << std::endl;
    std::cout << "                   " << ias::get_ias_version()  << std::endl;
}

void usage(void) {
    display_logo();
    std::cout << std::endl;
    std::cout << "Basic usage: ias [mode] [options]" << std::endl << std::endl;
    std::cout << "  ias --server                         Run IAS in server mode." << std::endl;
    std::cout << "  ias --client --address <server>      Command the remote IAS server." << std::endl;
    std::cout << "  ias --controller --config <path>     Run IAS in controller mode." << std::endl;
    std::cout << "  ias --eventstream --key <API key>    Display an eventstream." << std::endl;
    std::cout << std::endl;
    std::cout << "IAS modes:" << std::endl;
    std::cout << "  --server            Orchestrates the core behaviour." << std::endl;
    std::cout << "  --controller        Handles the devices and relays information between devices and the server." << std::endl;
    std::cout << "  --client            Enables a user to issues commands to IAS." << std::endl;
    std::cout << "  --eventstream       Displays an eventstream of all events, simplifying debugging." << std::endl;
    std::cout << "  --generate-hash     Generates a hash using the salts specified in the configuration file." << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --version           Displays the current version of IAS." << std::endl;
    std::cout << "  --config [path]     Specifies the path of the configuration file to use." << std::endl;
    std::cout << "  --address [addr]    Remote address of the IAS server." << std::endl;
    std::cout << "  --ssl               Enables the usage of SSL when using eventstream or client mode." << std::endl;
    std::cout << "  --key [api key]     Specifies API key to use when in eventstream mode." << std::endl;
}
