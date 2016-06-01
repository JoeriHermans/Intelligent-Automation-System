/**
 * A MySQL data access object for the member type.
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
#include <cassert>
#include <cstring>

// Application dependencies.
#include <ias/database/database_connection.h>
#include <ias/logger/logger.h>
#include <ias/technology/data_access/mysql_member_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char mysql_member_data_access::kStmtAdd[] =
        "";

    const char mysql_member_data_access::kStmtGetAll[] =
        "";

    const char mysql_member_data_access::kStmtGetId[] =
        "";

    const char mysql_member_data_access::kStmtRemove[] =
        "";

    const char mysql_member_data_access::kStmtUpdate[] =
        "";

    // END Constants. ////////////////////////////////////////////////

    inline void mysql_member_data_access::initialize(void) {
        mDbConnection = nullptr;
        mStmtAdd = nullptr;
        mStmtGetAll = nullptr;
        mStmtGetId = nullptr;
        mStmtRemove = nullptr;
        mStmtUpdate = nullptr;
    }

    void mysql_member_data_access::set_database_connection(ias::database_connection * dbConn) {
        // Checking the precondition.
        assert(dbConn != nullptr && dbConn->is_connected());

        mDbConnection = static_cast<MYSQL *>(dbConn->get_link());
    }

    void mysql_member_data_access::initialize_statements(void) {
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

    void mysql_member_data_access::close_statements(void) {
        mysql_stmt_close(mStmtAdd);
        mStmtAdd = nullptr;
        mysql_stmt_close(mStmtGetAll);
        mStmtGetAll = nullptr;
        mysql_stmt_close(mStmtGetId);
        mStmtGetId = nullptr;
        mysql_stmt_close(mStmtRemove);
        mStmtRemove = nullptr;
        mysql_stmt_close(mStmtUpdate);
        mStmtUpdate = nullptr;
    }

    void mysql_member_data_access::prepare_statement_get_all(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetAll != nullptr);

        rc = mysql_stmt_prepare(mStmtGetAll, kStmtGetAll,
                                strlen(kStmtGetAll));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetAll));
    }

    void mysql_member_data_access::prepare_statement_get_id(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetId != nullptr);

        rc = mysql_stmt_prepare(mStmtGetId, kStmtGetId,
                                strlen(kStmtGetId));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetId));
    }

    void mysql_member_data_access::prepare_statement_remove(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtRemove != nullptr);

        rc = mysql_stmt_prepare(mStmtRemove, kStmtRemove,
                                strlen(kStmtRemove));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtRemove));
    }

    void mysql_member_data_access::prepare_statement_update(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtUpdate != nullptr);

        rc = mysql_stmt_prepare(mStmtUpdate, kStmtUpdate,
                                strlen(kStmtUpdate));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtUpdate));
    }

    void mysql_member_data_access::prepare_statement_add(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtAdd != nullptr);

        rc = mysql_stmt_prepare(mStmtAdd, kStmtAdd,
                                strlen(kStmtAdd));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtAdd));
    }

    mysql_member_data_access::mysql_member_data_access(ias::database_connection * dbConn) {
        initialize();
        set_database_connection(dbConn);
        initialize_statements();
    }

    mysql_member_data_access::~mysql_member_data_access(void) {
        close_statements();
        cache_clear();
    }

    std::vector<ias::member *> mysql_member_data_access::get_all(void) {
        std::vector<ias::member *> members;

        // TODO Implement.

        return members;
    }

    ias::member * mysql_member_data_access::get(const std::size_t id) {
        ias::member * member = nullptr;

        // TODO Implement.

        return member;
    }

    void mysql_member_data_access::add(ias::member * member) {
        // Checking the precondition.
        assert(member != nullptr);

        // TODO Implement.
    }

    void mysql_member_data_access::remove(ias::member * member) {
        // Checking the precondition.
        assert(member != nullptr);

        // Check if there is a cache hit.
        if(cache_contains(member))
            // Remove the member.
            remove(member->get_id());
    }

    void mysql_member_data_access::remove(const std::size_t id) {
        std::size_t copyId = id;
        MYSQL_BIND param[1];

        // Preparing the parameters.
        memset(param, 0, sizeof param);
        param[0].buffer_type     = MYSQL_TYPE_LONG;
        param[0].buffer          = static_cast<void *>(&copyId);
        param[0].is_unsigned     = 1;
        mysql_stmt_bind_param(mStmtRemove, param);
        if(mysql_stmt_execute(mStmtRemove) == 0)
            cache_remove(id);
    }

    void mysql_member_data_access::update(ias::member * member) {
        // Checking the precondition.
        assert(member != nullptr);

        // TODO Implement.
    }

};

#endif
#endif
