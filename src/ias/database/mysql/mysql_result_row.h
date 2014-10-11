/**
 * A class which describes the properties and actions of a MySQL
 * result row.
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

#ifndef MYSQL_RESULT_ROW_H_
#define MYSQL_RESULT_ROW_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <cstddef>
#include <vector>
#include <mysql/mysql.h>

// Application dependencies.
#include <ias/database/interface/database_result_row.h>

// END Includes. /////////////////////////////////////////////////////

class MySqlResultRow : public DatabaseResultRow {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains a pointer to the resulting MySQL row which has been retrieved
     * from the MySQL result set.
     *
     * @note    By default, this member will be equal to 0.
     */
    MYSQL_ROW mResultRow;
    
    /**
     * Contains a vector of all columns.
     */
    std::vector<std::string> mColumns;

    /**
     * Contains the number of columns this row has.
     *
     * @note    By default, this member will be equal to 0.
     */
    std::size_t mNumColumns;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    inline void setNumColumns( const std::size_t numColumns );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    MySqlResultRow( const std::size_t numColumns , MYSQL_ROW resultRow );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~MySqlResultRow( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::size_t numColumns( void ) const;
    
    virtual const std::string & getColumn( const std::size_t columnIndex ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* MYSQL_RESULT_ROW_H_ */
