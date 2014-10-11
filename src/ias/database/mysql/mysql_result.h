/**
 * A class which describes the actions and properties of a MySQL result.
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

#ifndef MYSQL_RESULT_H_
#define MYSQL_RESULT_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mysql/mysql.h>

// Forward declarations.
class DatabaseResult;
class MySqlResultRow;

// END Includes. /////////////////////////////////////////////////////

class MySqlResult : public DatabaseResult {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the result set we retrieved.
     *
     * @note    By default, this member will be equal
     *          to the NULL reference.
     */
    MYSQL_RES * mResultSet;

    /**
     * Contains the value of the next row.
     *
     * @note    By default, this member will be equal
     *          to the NULL reference.
     */
    MYSQL_ROW mNextRow;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    inline void setResultSet( MYSQL_RES * resultSet );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    MySqlResult( MYSQL_RES * resultSet );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~MySqlResult( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual bool hasNext( void );

    virtual DatabaseResultRow * next( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* MYSQL_RESULT_H_ */
