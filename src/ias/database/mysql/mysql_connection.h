/**
 * A class which describes the properties of a MySQL database connection.
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

#ifndef MYSQL_CONNECTION_H_
#define MYSQL_CONNECTION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mysql/mysql.h>
#include <mysql/my_global.h>

// Application dependencies.
#include <ias/database/interface/database_connection.h>

// END Includes. /////////////////////////////////////////////////////

class MySqlConnection : public DatabaseConnection {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the MySQL connection structure.
     *
     * @note    By default, this member will be equal to
     *          the NULL reference.
     */
    MYSQL * mConnection;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    MySqlConnection( const std::string & username,
                     const std::string & password,
                     const std::string & schema,
                     const std::string & host );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~MySqlConnection( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual bool isConnected( void ) const;

    virtual bool connect( void );

    virtual DatabaseStatement * createStatement( const std::string & sql );

    virtual DatabasePreparedStatement * prepareStatement( const std::string & sql );

    virtual void * getLink( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* MYSQL_DATABASE_CONNECTION_H_ */
