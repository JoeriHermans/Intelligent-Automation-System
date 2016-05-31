/**
 * A class which represents the properties and actions of a MySQL
 * database connection.
 *
 * @date                    29 05 2016
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

#ifdef IAS_DATABASE_DRIVER
#if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/database/mysql/mysql_database_connection.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char mysql_database_connection::kDefaultPort[] = "3306";

    const char mysql_database_connection::kIdentifier[] = "mysql";

    // END Constants. ////////////////////////////////////////////////

    inline void mysql_database_connection::initialize(void) {
        initialize_connection_structure();
    }

    inline void mysql_database_connection::initialize_connection_structure(void) {
        mDbConnection = nullptr;
    }

    mysql_database_connection::mysql_database_connection(const std::string & host,
                                                         const std::string & schema,
                                                         const std::string & username,
                                                         const std::string & password)
      : database_connection(host, kDefaultPort, schema, username, password) {
        initialize();
    }

    mysql_database_connection::mysql_database_connection(const std::string & host,
                                                         const std::string & port,
                                                         const std::string & schema,
                                                         const std::string & username,
                                                         const std::string & password)
      : database_connection(host, port, schema, username, password) {
        initialize();
    }

    mysql_database_connection::~mysql_database_connection(void) {
        close_connection();
    }

    bool mysql_database_connection::open_connection(void) {
        const static int argument = 1;
        bool connected = false;

        if(mDbConnection == nullptr) {
            mDbConnection = mysql_init(nullptr);
            if(mDbConnection != nullptr) {
                logi("Connecting to MySQL database at " + get_host() + " on port " + get_port() + ".");
                // Set automatic reconnect.
                mysql_options(mDbConnection, MYSQL_OPT_RECONNECT, &argument);
                // Create a connection with the remote MySQL database.
                connected =
                    (mysql_real_connect(mDbConnection, get_host().c_str(),
                                        get_username().c_str(), get_password().c_str(),
                                        get_schema().c_str(), std::stoi(get_port()),
                                        nullptr, 0) != nullptr);
                // Check if a connection could be established.
                if(!connected) {
                    // Log the error.
                    loge(mysql_error(mDbConnection));
                    mysql_close(mDbConnection);
                    mDbConnection = nullptr;
                }
            } else {
                loge(mysql_error(mDbConnection));
            }
        } else {
            // We are already connected.
            connected = true;
        }

        return connected;
    }

    bool mysql_database_connection::close_connection(void) {
        bool closed = false;

        // Check if a connection is opened.
        if(mDbConnection != nullptr) {
            mysql_close(mDbConnection);
            mDbConnection = nullptr;
            logi("Remote database connection with " + get_host() + " closed.");
        }

        return closed;
    }

    bool mysql_database_connection::is_connected(void) const {
        return mDbConnection != nullptr;
    }

    void * mysql_database_connection::get_link(void) const {
        return static_cast<void *>(mDbConnection);
    }

    void mysql_database_connection::cleanup(void) {
        mysql_library_end();
    }

};

#endif
#endif
