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

// Application dependencies.
#include <ias/database/mysql/mysql_database_connection.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char mysql_database_connection::kDefaultPort[] = "3306";

    // END Constants. ////////////////////////////////////////////////

    inline void mysql_database_connection::initialize(void) {
        // TODO Implement.
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
        bool opened = false;

        // TODO Implement.

        return opened;
    }

    bool mysql_database_connection::close_connection(void) {
        bool closed = false;

        // TODO Implement.

        return closed;
    }

};

#endif
#endif
