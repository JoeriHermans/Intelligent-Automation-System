/**
 * A class which describes the properties and actions of a Postgresql
 * connection.
 *
 * @date                    August 20, 2014
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

// Application dependencies.
#include <ias/database/postgresql/postgresql_connection.h>

// END Includes. /////////////////////////////////////////////////////

PostgresqlConnection::PostgresqlConnection( const std::string & username,
                                            const std::string & password,
                                            const std::string & schema,
                                            const std::string & host ) {
    // TODO Implement.
}

PostgresqlConnection::~PostgresqlConnection( void ) {
    // TODO Implement.
}

bool PostgresqlConnection::isConnected( void ) const {
    // TODO Implement.

    return ( false );
}

bool PostgresqlConnection::connect( void ) {
    // TODO Implement.

    return ( false );
}

DatabaseStatement * PostgresqlConnection::createStatement( const std::string & sql ) {
    // TODO Implement.

    return ( nullptr );
}

DatabasePreparedStatement * PostgresqlConnection::prepareStatement( const std::string & sql ) {
    // TODO Implement.

    return ( nullptr );
}

void * PostgresqlConnection::getLink( void ) {
    // TODO Implement.

    return ( nullptr );
}
