/**
 * A class which will act as a data access layer through a MySQL
 * database connection.
 *
 * @date                    27 05 2016
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
#include <ias/user/data_access/user_data_access.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MYSQL_USER_DATA_ACCESS_H_
#define IAS_MYSQL_USER_DATA_ACCESS_H_

namespace ias {

class mysql_user_data_access : public user_data_access {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    static const char kStmtAdd[];
    static const char kStmtGetAll[];
    static const char kStmtGetId[];
    static const char kStmtRemove[];
    static const char kStmtUpdate[];

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
    MYSQL_STMT * mStmtAdd;
    MYSQL_STMT * mStmtGetAll;
    MYSQL_STMT * mStmtGetId;
    MYSQL_STMT * mStmtRemove;
    MYSQL_STMT * mStmtUpdate;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_database_connection(ias::database_connection * dbConn);

    void initialize_statements(void);

    void prepare_statement_add(void);

    void prepare_statement_get_all(void);

    void prepare_statement_get_id(void);

    void prepare_statement_remove(void);

    void prepare_statement_update(void);

    void close_statements(void);

    ias::user * fetch_user_from_db(const std::size_t id);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    mysql_user_data_access(ias::database_connection * dbConn);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~mysql_user_data_access(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<ias::user *> get_all(void);

    virtual ias::user * get(const std::size_t id);

    virtual void add(ias::user * user);

    virtual void remove(ias::user * user);

    virtual void remove(const std::size_t id);

    virtual void update(ias::user * user);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
#endif
#endif
