/**
 * A class which describes the properties of a MySQL database connection.
 *
 * @date                    Jul 21, 2013
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
#include <assert.h>
#include <stdio.h>
#include <syslog.h>

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/database/mysql/mysql_connection.h>
#include <ias/database/mysql/mysql_statement.h>
#include <ias/database/mysql/mysql_driver.h>

// END Includes. /////////////////////////////////////////////////////

inline void MySqlConnection::initialize( void ) {
    // Initialize the members of the class.
    mConnection = mysql_init( nullptr );
}

MySqlConnection::MySqlConnection( const std::string & username,
                                  const std::string & password,
                                  const std::string & schema,
                                  const std::string & host )
    : DatabaseConnection(username,password,schema,host) {
    // Nothing to do here.
    initialize();
}

MySqlConnection::~MySqlConnection( void ) {
    mysql_close( mConnection );
    mysql_library_end();
}

bool MySqlConnection::isConnected( void ) const
{
    return ( mConnection != nullptr );
}

bool MySqlConnection::connect( void ) {
    bool connected;
    my_bool argument;

    // Enable automatic reconnection by default.
    argument = 1;
    // Enable the automatic reconnect option.
    mysql_options(mConnection,MYSQL_OPT_RECONNECT,&argument);
    // Try to connect to the MySQL server.
    connected = ( mysql_real_connect(mConnection,
                                     getHost().c_str(),
                                     getUsername().c_str(),
                                     getPassword().c_str(),
                                     getSchema().c_str(),
                                     3306,nullptr,0) != nullptr );

    return ( connected );
}

DatabaseStatement * MySqlConnection::createStatement( const std::string & sql ) {
    DatabaseStatement * statement;

    // Checking the precondition.
    assert( sql.length() > 0 );

    // Check if the connection with the server is still active.
    if( mysql_ping(mConnection) == 0 )
        // Allocate a new mysql statement.
        statement = new MySqlStatement(this,sql);
    else
        // No statement should be allocated.
        statement = nullptr;

    return ( statement );
}

DatabasePreparedStatement * MySqlConnection::prepareStatement(
    const std::string & sql ) {
    // Checking the precondition.
    assert( sql.length() > 0 );

    // TODO Implement.
    return ( nullptr );
}

void * MySqlConnection::getLink( void )
{
    return ( static_cast<void *>(mConnection) );
}
