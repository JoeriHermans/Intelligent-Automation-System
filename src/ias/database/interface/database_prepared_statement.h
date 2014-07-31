/**
 * A class which describes the properties and actions of a database
 * prepared statement.
 *
 * @date                    Jul 21, 2013
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

#ifndef DATABASE_PREPARED_STATEMENT_H_
#define DATABASE_PREPARED_STATEMENT_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <string>

// Application dependencies.
#include <ias/database/interface/database_result.h>

// Forward declaration.
class DatabaseConnection;

// END Includes. /////////////////////////////////////////////////////

class DatabasePreparedStatement {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the database connection of the prepared statement.
     *
     * @note    By default, this member will be equal
     *          to the NULL reference.
     */
    DatabaseConnection * mConnection;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void ) {
        // Initialize the members of the class.
        mConnection = nullptr;
    }

    inline void setConnection( DatabaseConnection * connection ) {
        // Checking the precondition.
        assert( connection != nullptr );

        mConnection = connection;
    }

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    DatabaseConnection * getConnection( void ) {
        return ( mConnection );
    }

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    DatabasePreparedStatement( DatabaseConnection * connection ) {
        initialize();
        setConnection( connection );
    }

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~DatabasePreparedStatement( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual DatabaseResult * execute( void ) = 0;

    virtual void setParameter( const std::size_t index, 
                               const std::string & value ) = 0;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DATABASE_PREPARED_STATEMENT_H_ */
