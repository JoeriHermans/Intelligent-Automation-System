/**
 * A class which describes the actions and properties of a MySQL statement.
 *
 * @date                    Jul 22, 2013
 * @author                    Joeri HERMANS
 * @version                    0.1
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
#include <ias/database/mysql/mysql_statement.h>

// END Includes. /////////////////////////////////////////////////////

inline void MySqlStatement::setConnection( MYSQL * connection ) {
    // Checking the precondition.
    assert( connection != nullptr );

    mConnection = connection;
}

MySqlStatement::MySqlStatement( MySqlConnection * connection , const std::string & query )
    : DatabaseStatement( connection , query ) {
    // Set the connection member.
    setConnection((MYSQL *) connection->getLink());
}

MySqlStatement::~MySqlStatement( void ) {
    // Nothing to do here, yet.
}

DatabaseResult * MySqlStatement::execute( void ) {
    MYSQL_RES * mysqlResult;
    MySqlResult * result;

    // Initialize the result.
    result = nullptr;
    // Try to execute the specified query.
    if( mysql_query(mConnection,getQuery().c_str()) == 0 ) {
        // Retrieve the mysql-result from the connection.
        mysqlResult = mysql_store_result(mConnection);
        // Allocate a new instance.
        result = new MySqlResult(mysqlResult);
    }

    return ( result );
}
