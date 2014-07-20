/**
 * A class which describes the properties of a MySQL database driver.
 *
 * @date					Jul 23, 2013
 * @author					Joeri HERMANS
 * @version					0.1
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

// Application dependencies.
#include <ias/database/mysql/mysql_driver.h>
#include <ias/database/mysql/mysql_connection.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Class constants. ////////////////////////////////////////////

const char MySqlDriver::kMySqlIdentifier[] = "mysql";

// END Class constants. //////////////////////////////////////////////

MySqlDriver::MySqlDriver( void )
	: DatabaseDriver(kMySqlIdentifier) {
	// Nohting to do here.
}

MySqlDriver::~MySqlDriver( void )
{
	// Nothing to do here.
}

DatabaseConnection * MySqlDriver::initializeConnection( 
    const std::string & username, const std::string & password,
    const std::string & schema, const std::string & host ) {
	DatabaseConnection * connection;

	// Allocate the mysql connection object.
	connection = new MySqlConnection(username,password,schema,host);
	
	return ( connection );
}
