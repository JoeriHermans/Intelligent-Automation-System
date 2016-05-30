/**
 * A class which represents the properties and actions of a PostgreSQL
 * database connection.
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

#ifdef IAS_DATABASE_DRIVER
#if IAS_DATABASE_DRIVER == 'P' || IAS_DATABASE_DRIVER == 'A'

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/database/postgresql/postgresql_database_connection.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char postgresql_database_connection::kDefaultPort[] = "5432";

    const char postgresql_database_connection::kIdentifier[] = "postgresql";

    // END Constants. ////////////////////////////////////////////////

    inline void postgresql_database_connection::initialize(void) {
        // TODO Implement.
    }

    postgresql_database_connection::postgresql_database_connection(const std::string & host,
                                                                   const std::string & schema,
                                                                   const std::string & username,
                                                                   const std::string & password)
      : database_connection(host, kDefaultPort, schema, username, password) {
        initialize();
    }

    postgresql_database_connection::postgresql_database_connection(const std::string & host,
                                                                   const std::string & port,
                                                                   const std::string & schema,
                                                                   const std::string & username,
                                                                   const std::string & password)
      : database_connection(host, port, schema, username, password) {
        initialize();
    }

    postgresql_database_connection::~postgresql_database_connection(void) {
        close_connection();
    }

    bool postgresql_database_connection::is_connected(void) const {
        // TODO Implement.

        return false;
    }

    bool postgresql_database_connection::open_connection(void) {
        bool connected = false;

        // TODO Implement.

        return connected;
    }

    bool postgresql_database_connection::close_connection(void) {
        bool closed = false;

        // TODO Implement.

        return closed;
    }

    void * postgresql_database_connection::get_link(void) const {
        // TODO Implement.

        return nullptr;
    }

    void postgresql_database_connection::cleanup(void) {
        // TODO Implement.
    }

};

#endif
#endif
