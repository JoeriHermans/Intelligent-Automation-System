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
#include <cassert>
#include <cstring>
#include <iostream>

// Application dependencies.
#include <ias/user/data_access/mysql_user_data_access.h>
#include <ias/user/user.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char mysql_user_data_access::kStmtAdd[] =
        "";

    const char mysql_user_data_access::kStmtGetAll[] =
        "SELECT id, name, surname, email, username, password, gender, disabled \
         FROM users;";

    const char mysql_user_data_access::kStmtGetId[] =
        "SELECT id, name, surname, email, username, password, gender, disabled \
         FROM users \
         WHERE id = ?;";

    const char mysql_user_data_access::kStmtRemove[] =
        "DELETE FROM users \
         WHERE id = ?;";

    const char mysql_user_data_access::kStmtUpdate[] =
        "";

    // END Constants. ////////////////////////////////////////////////

    inline void mysql_user_data_access::initialize(void) {
        mDbConnection = nullptr;
        mStmtAdd = nullptr;
        mStmtGetAll = nullptr;
        mStmtGetId = nullptr;
        mStmtRemove = nullptr;
        mStmtUpdate = nullptr;
    }

    void mysql_user_data_access::set_database_connection(ias::database_connection * dbConn) {
        // Checking the precondition.
        assert(dbConn != nullptr && dbConn->is_connected());

        mDbConnection = static_cast<MYSQL *>(dbConn->get_link());
    }

    void mysql_user_data_access::initialize_statements(void) {
        mStmtAdd = mysql_stmt_init(mDbConnection);
        prepare_statement_add();
        mStmtGetAll = mysql_stmt_init(mDbConnection);
        prepare_statement_get_all();
        mStmtGetId = mysql_stmt_init(mDbConnection);
        prepare_statement_get_id();
        mStmtRemove = mysql_stmt_init(mDbConnection);
        prepare_statement_remove();
        mStmtUpdate = mysql_stmt_init(mDbConnection);
        prepare_statement_update();
    }

    void mysql_user_data_access::prepare_statement_add(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtAdd != nullptr);

        rc = mysql_stmt_prepare(mStmtAdd, kStmtAdd,
                                strlen(kStmtAdd));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtAdd));
    }

    void mysql_user_data_access::prepare_statement_get_all(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetAll != nullptr);

        rc = mysql_stmt_prepare(mStmtGetAll, kStmtGetAll,
                                strlen(kStmtGetAll));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetAll));
    }

    void mysql_user_data_access::prepare_statement_get_id(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetId != nullptr);

        rc = mysql_stmt_prepare(mStmtGetId, kStmtGetId,
                                strlen(kStmtGetId));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetId));
    }

    void mysql_user_data_access::prepare_statement_remove(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtRemove != nullptr);

        rc = mysql_stmt_prepare(mStmtRemove, kStmtRemove,
                                strlen(kStmtRemove));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtRemove));
    }

    void mysql_user_data_access::prepare_statement_update(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtUpdate != nullptr);

        rc = mysql_stmt_prepare(mStmtUpdate, kStmtUpdate,
                                strlen(kStmtUpdate));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtUpdate));
    }

    void mysql_user_data_access::close_statements(void) {
        mysql_stmt_close(mStmtAdd);
        mysql_stmt_close(mStmtGetAll);
        mysql_stmt_close(mStmtGetId);
        mysql_stmt_close(mStmtRemove);
        mysql_stmt_close(mStmtUpdate);
    }

    ias::user * mysql_user_data_access::fetch_user_from_db(const std::size_t id) {
        ias::user * user = nullptr;
        MYSQL_BIND result[8];
        MYSQL_BIND param[1];
        std::size_t length[5];
        std::size_t copyId = id;

        // Buffer variables.
        int bufferId;
        char bufferName[kDefaultStringSize + 1];
        char bufferSurName[kDefaultStringSize + 1];
        char bufferEmail[kDefaultStringSize + 1];
        char bufferUsername[kDefaultStringSize + 1];
        char bufferPassword[kDefaultStringSize + 1];
        std::size_t bufferGender;
        bool bufferDisabled;

        // Clear the parameter structures.
        memset(result, 0, sizeof result);
        memset(param, 0, sizeof param);
        memset(length, 0, sizeof length);
        // Prepare the bind types;
        param[0].buffer_type      = MYSQL_TYPE_LONG;
        param[0].buffer           = static_cast<void *>(&copyId);
        param[0].is_unsigned      = 1;
        // Prepare the result types.
        // id
        result[0].buffer_type    = MYSQL_TYPE_LONG;
        result[0].buffer         = static_cast<void *>(&bufferId);
        result[0].is_unsigned    = 1;
        // name
        result[1].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[1].buffer         = static_cast<void *>(bufferName);
        result[1].buffer_length  = kDefaultStringSize;
        // surname
        result[2].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[2].buffer         = static_cast<void *>(bufferSurName);
        result[2].buffer_length  = kDefaultStringSize;
        // email
        result[3].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[3].buffer         = static_cast<void *>(bufferEmail);
        result[3].buffer_length  = kDefaultStringSize;
        // username
        result[4].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[4].buffer         = static_cast<void *>(bufferUsername);
        result[4].buffer_length  = kDefaultStringSize;
        // password
        result[5].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[5].buffer         = static_cast<void *>(bufferPassword);
        result[5].buffer_length  = kDefaultStringSize;
        // gender
        result[6].buffer_type    = MYSQL_TYPE_TINY;
        result[6].buffer         = static_cast<void *>(&bufferGender);
        // disabled
        result[7].buffer_type    = MYSQL_TYPE_TINY;
        result[7].buffer         = static_cast<void *>(&bufferDisabled);
        // Bind the result buffers.
        mysql_stmt_bind_param(mStmtGetId, param);
        mysql_stmt_bind_result(mStmtGetId, result);
        if(mysql_stmt_execute(mStmtGetId) == 0) {
            if(mysql_stmt_store_result(mStmtGetId) == 0){
                // Retrieve all elements.
                if(mysql_stmt_fetch(mStmtGetId) == 0) {
                    // Type conversions to match class constructor.
                    std::size_t id           = static_cast<std::size_t>(bufferId);
                    std::string username     = bufferUsername;
                    std::string password     = bufferPassword;
                    std::string email        = bufferEmail;
                    std::string name         = bufferName;
                    std::string surname      = bufferSurName;
                    ias::user_gender gender  = static_cast<ias::user_gender>(bufferGender);
                    bool disabled            = static_cast<bool>(bufferDisabled);

                    // Allocate a new user instance.
                    user = new ias::user(id, username, password, email, name,
                                         surname, gender, disabled);
                }
                // Store all elements in cache.
                cache_store(user);
            } else {
                loge("mysql_stmt_store_result() failed.");
                loge(mysql_stmt_error(mStmtGetId));
            }
        } else {
            loge("mysql_stmt_execute() failed.");
            loge(mysql_stmt_error(mStmtGetId));
        }

        return user;
    }

    mysql_user_data_access::mysql_user_data_access(ias::database_connection * dbConn) {
        initialize();
        set_database_connection(dbConn);
        initialize_statements();
    }

    mysql_user_data_access::~mysql_user_data_access(void) {
        cache_clear();
        close_statements();
    }

    std::vector<ias::user *> mysql_user_data_access::get_all(void) {
        std::vector<ias::user *> users;
        MYSQL_BIND result[8];
        std::size_t length[5];

        // Buffer variables.
        int bufferId;
        char bufferName[kDefaultStringSize + 1];
        char bufferSurName[kDefaultStringSize + 1];
        char bufferEmail[kDefaultStringSize + 1];
        char bufferUsername[kDefaultStringSize + 1];
        char bufferPassword[kDefaultStringSize + 1];
        std::size_t bufferGender;
        bool bufferDisabled;

        // Clear the parameter structures.
        memset(result, 0, sizeof result);
        memset(length, 0, sizeof length);
        // Prepare the result types.
        // id
        result[0].buffer_type    = MYSQL_TYPE_LONG;
        result[0].buffer         = static_cast<void *>(&bufferId);
        result[0].is_unsigned    = 1;
        // name
        result[1].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[1].buffer         = static_cast<void *>(bufferName);
        result[1].buffer_length  = kDefaultStringSize;
        // surname
        result[2].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[2].buffer         = static_cast<void *>(bufferSurName);
        result[2].buffer_length  = kDefaultStringSize;
        // email
        result[3].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[3].buffer         = static_cast<void *>(bufferEmail);
        result[3].buffer_length  = kDefaultStringSize;
        // username
        result[4].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[4].buffer         = static_cast<void *>(bufferUsername);
        result[4].buffer_length  = kDefaultStringSize;
        // password
        result[5].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[5].buffer         = static_cast<void *>(bufferPassword);
        result[5].buffer_length  = kDefaultStringSize;
        // gender
        result[6].buffer_type    = MYSQL_TYPE_TINY;
        result[6].buffer         = static_cast<void *>(&bufferGender);
        // disabled
        result[7].buffer_type    = MYSQL_TYPE_TINY;
        result[7].buffer         = static_cast<void *>(&bufferDisabled);

        // Bind the result buffers.
        mysql_stmt_bind_result(mStmtGetAll, result);
        if(mysql_stmt_execute(mStmtGetAll) == 0) {
            if(mysql_stmt_store_result(mStmtGetAll) == 0){
                // Retrieve all elements.
                while(!mysql_stmt_fetch(mStmtGetAll)) {
                    ias::user * user;

                    // Type conversions to match class constructor.
                    std::size_t id           = static_cast<std::size_t>(bufferId);
                    std::string username     = bufferUsername;
                    std::string password     = bufferPassword;
                    std::string email        = bufferEmail;
                    std::string name         = bufferName;
                    std::string surname      = bufferSurName;
                    ias::user_gender gender  = static_cast<ias::user_gender>(bufferGender);
                    bool disabled            = static_cast<bool>(bufferDisabled);

                    // Allocate a new user instance.
                    user = new ias::user(id, username, password, email, name,
                                         surname, gender, disabled);
                    // Store the users in the vector.
                    users.push_back(user);
                }
                // Store all elements in cache.
                cache_store_fast(users);
            } else {
                loge("mysql_stmt_store_result() failed.");
                loge(mysql_stmt_error(mStmtGetAll));
            }
        } else {
            loge("mysql_stmt_execute() failed.");
            loge(mysql_stmt_error(mStmtGetAll));
        }

        return users;
    }

    ias::user * mysql_user_data_access::get(const std::size_t id) {
        // Check if we can get a cache hit.
        ias::user * user = cache_get(id);
        if(user == nullptr) {
            std::cout << "Fetching from database." << std::endl;
            // No cache hit, fetch user from database.
            user = fetch_user_from_db(id);
        } else {
            std::cout << "Fetching from cache." << std::endl;
        }

        return user;
    }

    void mysql_user_data_access::add(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        // TODO Implement.
    }

    void mysql_user_data_access::remove(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        remove(user->get_id());
    }

    void mysql_user_data_access::remove(const std::size_t id) {
        // TODO Implement.
    }

    void mysql_user_data_access::update(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        // TODO Implement.
    }

};

#endif
#endif
