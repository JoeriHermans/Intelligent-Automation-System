/**
 * A class which describes the properties and actions of the server
 * application. This application will handle the main functionality
 * of IAS, applying rules, dispatching commands, setting up the
 * servers.
 *
 * @date                    30 05 2016
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
#include <unordered_map>
#include <cassert>
#include <string>
#include <cstring>
#include <iostream>

// Application dependencies.
#include <ias/application/server/server_application.h>
#include <ias/application/constants.h>
#include <ias/logger/console/console_logger.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char server_application::kDefaultConfigPath[] = "/etc/ias/configuration/server.conf";

    // END Constants. ////////////////////////////////////////////////

    inline void server_application::initialize(void) {
        // Reset the default values of the members.
        mStorageUsers = nullptr;
        mDbConnection = nullptr;
        initialize_logger();
    }

    void server_application::initialize_logger(void) {
        ias::logger::set_logger(new ias::console_logger());
    }

    void server_application::analyze_arguments(const int argc, const char ** argv) {
        std::string configPath;
        int index;

        // Checking the precondition.
        assert(argc >= 1 && argv != nullptr);

        // BEGIN Analyzing arguments. ////////////////////////////////

        // Configuration path flag.
        index = ias::flag_index(argc, argv, kFlagConfig);
        if(index >= 0)
            configPath = argv[index + 1];
        else
            configPath = kDefaultConfigPath;

        // END Analyzing arguments. //////////////////////////////////


        // Read the configuration file with the provided path.
        ias::read_configuration_file(configPath, mConfig);
    }

    void server_application::allocate_storage(void) {
        // TODO Implement.
    }

    void server_application::cleanup_storage(void) {
        // TODO Implement.
    }

    server_application::server_application(const int argc, const char ** argv) {
        initialize();
        analyze_arguments(argc, argv);
    }

    server_application::~server_application(void) {
        cleanup_storage();
    }

    void server_application::stop(void) {
        // TODO Implement.
    }

    void server_application::run(void) {
        // TODO Implement.
    }

};
