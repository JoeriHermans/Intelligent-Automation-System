/**
 * A class which describes the actions and properties of a MySQL statement.
 *
 * @date                    Jul 22, 2013
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

#ifndef MYSQL_STATEMENT_H_
#define MYSQL_STATEMENT_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <mysql/mysql.h>

// Application dependencies.
#include <ias/database/interface/database_statement.h>
#include <ias/database/mysql/mysql_connection.h>
#include <ias/database/mysql/mysql_result.h>

// END Includes. /////////////////////////////////////////////////////

class MySqlStatement : public DatabaseStatement {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains a pointer to the mysql connection which will handle
     * this statement.
     *
     * @note    By default, this member will be equal
     *          to the NULL reference.
     */
    MYSQL * mConnection;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void setConnection( MYSQL * connection );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    MySqlStatement( MySqlConnection * connection , const std::string & query );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~MySqlStatement( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual DatabaseResult * execute( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* MYSQL_STATEMENT_H_ */
