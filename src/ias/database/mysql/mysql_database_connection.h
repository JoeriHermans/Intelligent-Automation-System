/**
 * A class which represents the properties and actions of a MySQL
 * database connection.
 *
 * @date                    29 05 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

#ifdef IAS_DATABASE_DRIVER
#if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mysql/mysql.h>
#include <mysql/my_global.h>

// Application dependencies.
#include <ias/database/database_connection.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MYSQL_DATABASE_CONNECTION_H_
#define IAS_MYSQL_DATABASE_CONNECTION_H_

namespace ias {

class mysql_database_connection : public database_connection {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Holds the default port of a MySQL database connection as a string
     * representation.
     */
    static const char kDefaultPort[];

    /**
     * Holds the driver identifier specific to MySQL.
     */
    static const char kIdentifier[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Structure which is responsible for maintaining the state of the
     * connection with the remote MySQL database.
     */
    MYSQL * mDbConnection;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    inline void initialize_connection_structure(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    mysql_database_connection(const std::string & host,
                              const std::string & schema,
                              const std::string & username,
                              const std::string & password);

    mysql_database_connection(const std::string & host,
                              const std::string & port,
                              const std::string & schema,
                              const std::string & username,
                              const std::string & password);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~mysql_database_connection(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual bool open_connection(void);

    virtual bool close_connection(void);

    virtual bool is_connected(void) const;

    virtual void * get_link(void) const;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////

    static void cleanup(void);

    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
#endif
#endif
