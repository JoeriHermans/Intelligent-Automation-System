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
#include <pqxx/pqxx>

// Application dependencies.
#include <ias/database/postgresql/postgresql_connection.h>
#include <ias/database/postgresql/postgresql_statement.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char PostgresqlConnection::kIdentifierHost[] = "hostaddr";
const char PostgresqlConnection::kIdentifierSchema[] = "dbname";
const char PostgresqlConnection::kIdentifierUsername[] = "user";
const char PostgresqlConnection::kIdentifierPassword[] = "password";
const char PostgresqlConnection::kIdentifierPort[] = "port";

// END Constants. ////////////////////////////////////////////////////

inline void PostgresqlConnection::initialize( void ) {
    mConnection = nullptr;
}

PostgresqlConnection::PostgresqlConnection( const std::string & username,
                                            const std::string & password,
                                            const std::string & schema,
                                            const std::string & host ) :
    DatabaseConnection(username,password,schema,host) {
    initialize();
}

PostgresqlConnection::~PostgresqlConnection( void ) {
    // Free the allocated memory.
    mConnection->disconnect();
    delete mConnection; mConnection = nullptr;
}

bool PostgresqlConnection::isConnected( void ) const {
    return ( mConnection != nullptr && mConnection->is_open() );
}

bool PostgresqlConnection::connect( void ) {
    const std::string & username = getUsername();
    const std::string & password = getPassword();
    const std::string & schema = getSchema();
    const std::string & host = getHost();
    std::string dbString;

    dbString = kIdentifierHost;
    dbString += "=";
    dbString += host + " ";
    dbString += kIdentifierSchema;
    dbString += "=";
    dbString += schema + " ";
    dbString += kIdentifierUsername;
    dbString += "=";
    dbString += username + " ";
    dbString += kIdentifierPassword;
    dbString += "=";
    dbString += password;
    try {
        mConnection = new pqxx::connection(dbString);
    } catch( std::exception & e ) {
        delete mConnection; mConnection = nullptr;
    }

    return ( isConnected() );
}

DatabaseStatement * PostgresqlConnection::createStatement( const std::string & sql ) {
    DatabaseStatement * statement;

    statement = new PostgresqlStatement(this,sql);

    return ( statement );
}

DatabasePreparedStatement * PostgresqlConnection::prepareStatement( const std::string & sql ) {
    return ( nullptr );
}

void * PostgresqlConnection::getLink( void ) {
    return ( (void *) mConnection );
}
