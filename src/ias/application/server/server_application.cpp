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
#include <algorithm>
#include <unordered_map>
#include <cassert>
#include <string>
#include <cstring>
#include <iostream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/server/server_application.h>
#include <ias/database/mysql/mysql_database_connection.h>
#include <ias/database/postgresql/postgresql_database_connection.h>
#include <ias/logger/console/console_logger.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char server_application::kDefaultConfigPath[] =
        "/etc/ias/configuration/server.conf";

    const char server_application::kErrorNoDatabaseDriver[] =
        "No database driver has been specified.";

    const char server_application::kErrorUnknowDatabaseDriver[] =
        "An unknown database driver has been specified.";

    const char server_application::kErrorNoDatabasePort[] =
        "No database port has been specified.";

    const char server_application::kMessageDatabaseConnectionSetup[] =
        "Settting up a database connection.";

    // END Constants. ////////////////////////////////////////////////

    inline void server_application::initialize(void) {
        // Reset the default values of the members.
        mStorageUsers = nullptr;
        mDbConnection = nullptr;
        mFlagRunning = true;
        initialize_logger();
    }

    void server_application::allocate_database_connection(void) {
        std::string driver;
        std::string host;
        std::string port;
        std::string schema;
        std::string username;
        std::string password;

        logi(kMessageDatabaseConnectionSetup);
        // Select the driver that has been specified by the user.
        driver = mConfig[kConfigDatabaseDriver];
        // Check if a driver has been specified.
        if(driver.empty()) {
            loge(kErrorNoDatabaseDriver);
            stop();

            return;
        }
        // Check if a known database driver has been specified.
        std::vector<std::string> drivers = ias::get_database_drivers();
        if(std::find(drivers.begin(), drivers.end(), driver) == drivers.end()) {
            loge(kErrorUnknowDatabaseDriver);
            stop();

            return;
        }
        // Fetch the database parameters and credentials from the
        // configuration file.
        host = mConfig[kConfigDatabaseHost];
        port = mConfig[kConfigDatabasePort];
        schema = mConfig[kConfigDatabaseSchema];
        username = mConfig[kConfigDatabaseUser];
        password = mConfig[kConfigDatabasePassword];
        // Check if the default port is specified.
        if(port.empty()) {
            // Check which database driver has been specified.
            // MySQL
            #ifdef IAS_DATABASE_DRIVER
            #if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'
            if(std::find(drivers.begin(), drivers.end(), driver) != drivers.end())
                port = ias::mysql_database_connection::kDefaultPort;
            #endif
            #endif
            // PostgreSQL
            #ifdef IAS_DATABASE_DRIVER
            #if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'
            if(std::find(drivers.begin(), drivers.end(), driver) != drivers.end())
                port = ias::postgresql_database_connection::kDefaultPort;
            #endif
            #endif
            // Check if the port is still empty.
            if(port.empty()) {
                loge(kErrorNoDatabasePort);
                stop();

                return;
            }
        }
    }

    void server_application::allocate_storage(void) {
        // TODO Implement.
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

    void server_application::cleanup_database_connection(void) {
        delete mDbConnection;
        mDbConnection = nullptr;
    }

    void server_application::cleanup_storage(void) {
        // TODO Implement.
    }

    void server_application::initialize_logger(void) {
        ias::logger::set_logger(new ias::console_logger());
    }

    server_application::server_application(const int argc, const char ** argv) {
        initialize();
        analyze_arguments(argc, argv);
    }

    server_application::~server_application(void) {
        cleanup_storage();
        cleanup_database_connection();
    }

    void server_application::stop(void) {
        mFlagRunning = false;
    }

    void server_application::run(void) {
        allocate_database_connection();
        // Check if a database connection could be opened.
        if(mDbConnection != nullptr) {
            // TODO Implement.
        }
    }

};
