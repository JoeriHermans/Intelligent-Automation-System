/**
 * A class which describes the properties and actions of a PostgreSQL
 * database driver.
 *
 * @date                    Augustus 20,  2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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

// Application dependencies.
#include <ias/database/interface/database_driver.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char PostgresqlDriver::kPostgresqlIdentifier[] = "postgresql";

// END Constants. ////////////////////////////////////////////////////

PostgresqlDriver::PostgresqlDriver( void ) :
    DatabaseDriver(kPostgresqlIdentifier) {
    // TODO Implement.
}

PostgresqlDriver::~PostgresqlDriver( void ) {
    // TODO Implement.
}

DatabaseConnection * PostgresqlDriver::initializeConnection(
    const std::string & username, const std::string & password,
    const std::string & schema, const std::string & host) {
    DatabaseConnection * dbConnection;

    // TODO Implement.

    return ( dbConnection );

}
