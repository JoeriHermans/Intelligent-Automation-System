/**
 * A class which will act as a data access layer through a MySQL
 * database connection.
 *
 * @date                    01 06 2016
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
#include <ias/technology/data_access/value_type_data_access.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MYSQL_VALUE_TYPE_DATA_ACCESS_H_
#define IAS_MYSQL_VALUE_TYPE_DATA_ACCESS_H_

namespace ias {

class mysql_value_type_data_access : public value_type_data_access {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    static const char kStmtGetAll[];
    static const char kStmtGetId[];
    static const char kStmtRemove[];

    static const std::size_t kDefaultStringSize = 80;

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the db-link object associated with the MySQL connection.
     *
     * @note By default, this member will be equal to the null reference.
     */
    MYSQL * mDbConnection;

    /**
     * Set of prepared statements in order to access the remote database
     * in an efficient manner.
     *
     * @note By default, these members will be equal to the null reference.
     */
    MYSQL_STMT * mStmtGetAll;
    MYSQL_STMT * mStmtGetId;
    MYSQL_STMT * mStmtRemove;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_database_connection(ias::database_connection * dbConn);

    void initialize_statements(void);

    void prepare_statement_get_all(void);

    void prepare_statement_get_id(void);

    void prepare_statement_remove(void);

    void close_statements(void);

    ias::value_type * fetch_value_type_from_db(const std::size_t id);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    mysql_value_type_data_access(ias::database_connection * dbConn);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~mysql_value_type_data_access(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<ias::value_type *> get_all(void);

    virtual ias::value_type * get(const std::size_t id);

    virtual void add(ias::value_type * element);

    virtual void remove(ias::value_type * element);

    virtual void remove(const std::size_t id);

    virtual void update(ias::value_type *  element);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
#endif
#endif
