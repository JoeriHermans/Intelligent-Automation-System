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
#include <ias/technology/feature.h>
#include <ias/technology/data_access/mysql_member_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Constants. //////////////////////////////////////////////

    const char mysql_member_data_access::kStmtAdd[] =
        "";

    const char mysql_member_data_access::kStmtGetAll[] =
        "SELECT id, value_type_id, identifier, default_value \
         FROM technology_members;";

    const char mysql_member_data_access::kStmtGetId[] =
        "SELECT value_type_id, identifier, default_value \
         FROM technology_members \
         WHERE id = ?;";

    const char mysql_member_data_access::kStmtRemove[] =
        "DELETE FROM technology_members WHERE id = ?;";

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
        mStorageValueTypes = nullptr;
    }

    void mysql_member_data_access::set_database_connection(ias::database_connection * dbConn) {
        // Checking the precondition.
        assert(dbConn != nullptr && dbConn->is_connected());

        mDbConnection = static_cast<MYSQL *>(dbConn->get_link());
    }

    void mysql_member_data_access::initialize_statements(void) {
        // mStmtAdd = mysql_stmt_init(mDbConnection);
        // prepare_statement_add();
        mStmtGetAll = mysql_stmt_init(mDbConnection);
        prepare_statement_get_all();
        mStmtGetId = mysql_stmt_init(mDbConnection);
        prepare_statement_get_id();
        mStmtRemove = mysql_stmt_init(mDbConnection);
        prepare_statement_remove();
        // mStmtUpdate = mysql_stmt_init(mDbConnection);
        // prepare_statement_update();
    }

    void mysql_member_data_access::close_statements(void) {
        // mysql_stmt_close(mStmtAdd);
        // mStmtAdd = nullptr;
        mysql_stmt_close(mStmtGetAll);
        mStmtGetAll = nullptr;
        mysql_stmt_close(mStmtGetId);
        mStmtGetId = nullptr;
        mysql_stmt_close(mStmtRemove);
        mStmtRemove = nullptr;
        // mysql_stmt_close(mStmtUpdate);
        // mStmtUpdate = nullptr;
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

    void mysql_member_data_access::set_value_type_da(ias::value_type_data_access * vtda) {
        // Checking the precondition.
        assert(vtda != nullptr);

        mStorageValueTypes = vtda;
    }

    ias::member * mysql_member_data_access::fetch_member_from_db(const std::size_t id) {
        ias::member * member = nullptr;
        MYSQL_BIND result[3];
        MYSQL_BIND param[1];

        // Buffer variables.
        std::size_t bufferValueTypeId = 0;
        std::size_t copyId = id;
        char bufferIdentifier[kDefaultStringSize + 1];
        char bufferDefaultValue[kDefaultStringSize + 1];

        // Clear the result structure.
        memset(result, 0, sizeof result);
        memset(param, 0, sizeof param);
        // Prepare the result type.
        // value type id
        result[0].buffer_type     = MYSQL_TYPE_LONG;
        result[0].buffer          = static_cast<void *>(&bufferValueTypeId);
        result[0].is_unsigned     = 1;
        // identifier
        result[1].buffer_type     = MYSQL_TYPE_VAR_STRING;
        result[1].buffer          = static_cast<void *>(bufferIdentifier);
        result[1].buffer_length   = kDefaultStringSize;
        // default value
        result[2].buffer_type     = MYSQL_TYPE_VAR_STRING;
        result[2].buffer          = static_cast<void *>(bufferDefaultValue);
        result[2].buffer_length   = kDefaultStringSize;
        // Prepare the parameter type.
        // id
        param[0].buffer_type      = MYSQL_TYPE_LONG;
        param[0].buffer           = static_cast<void *>(&copyId);
        param[0].is_unsigned      = 1;

        // Bind the parameter buffer.
        mysql_stmt_bind_param(mStmtGetId, param);
        mysql_stmt_bind_result(mStmtGetId, result);
        if(mysql_stmt_execute(mStmtGetAll) == 0) {
            if(mysql_stmt_store_result(mStmtGetAll) == 0) {
                // Retrieve all elements.
                if(mysql_stmt_fetch(mStmtGetAll)) {
                    ias::member * member;

                    // Fetch the value type associated with this member.
                    const ias::value_type * vt = mStorageValueTypes->get(bufferValueTypeId);
                    // Type conversions to match class constructor.
                    std::string identifier      = bufferIdentifier;
                    std::string defaultValue    = bufferDefaultValue;
                    // Allocate a new member.
                    member = new ias::member(id, identifier,
                                             defaultValue, vt);
                    // Add the member to the cache.
                    cache_store(member);
                }
            } else {
                loge(mysql_stmt_error(mStmtGetAll));
            }
        } else {
            loge(mysql_stmt_error(mStmtGetAll));
        }

        return member;
    }

    mysql_member_data_access::mysql_member_data_access(ias::database_connection * dbConn,
                                                       ias::value_type_data_access * vtda) {
        initialize();
        set_database_connection(dbConn);
        set_value_type_da(vtda);
        initialize_statements();
    }

    mysql_member_data_access::~mysql_member_data_access(void) {
        close_statements();
        cache_clear();
    }

    std::vector<ias::member *> mysql_member_data_access::get_all(void) {
        std::vector<ias::member *> members;
        MYSQL_BIND result[4];

        // Buffer variables.
        std::size_t bufferId = 0;
        std::size_t bufferValueTypeId = 0;
        char bufferIdentifier[kDefaultStringSize + 1];
        char bufferDefaultValue[kDefaultStringSize + 1];

        // Clear the result structure.
        memset(result, 0, sizeof result);
        // Prepare the result types.
        // id
        result[0].buffer_type     = MYSQL_TYPE_LONG;
        result[0].buffer          = static_cast<void *>(&bufferId);
        result[0].is_unsigned     = 1;
        // value type id
        result[1].buffer_type     = MYSQL_TYPE_LONG;
        result[1].buffer          = static_cast<void *>(&bufferValueTypeId);
        result[1].is_unsigned     = 1;
        // identifier
        result[2].buffer_type     = MYSQL_TYPE_VAR_STRING;
        result[2].buffer          = static_cast<void *>(bufferIdentifier);
        result[2].buffer_length   = kDefaultStringSize;
        // default value
        result[3].buffer_type     = MYSQL_TYPE_VAR_STRING;
        result[3].buffer          = static_cast<void *>(bufferDefaultValue);
        result[3].buffer_length   = kDefaultStringSize;

        // Bind the result buffers.
        mysql_stmt_bind_result(mStmtGetAll, result);
        if(mysql_stmt_execute(mStmtGetAll) == 0) {
            if(mysql_stmt_store_result(mStmtGetAll) == 0) {
                // Retrieve all elements.
                while(!mysql_stmt_fetch(mStmtGetAll)) {
                    ias::member * member;

                    // Fetch the value type associated with this member.
                    const ias::value_type * vt = mStorageValueTypes->get(bufferValueTypeId);
                    // Type conversions to match class constructor.
                    std::string identifier      = bufferIdentifier;
                    std::string defaultValue    = bufferDefaultValue;
                    // Allocate a new member.
                    member = new ias::member(bufferId, identifier,
                                             defaultValue, vt);
                    // Add the members to the storage.
                    members.push_back(member);
                }
                // Add the members to the cache.
                cache_store_fast(members);
            } else {
                loge(mysql_stmt_error(mStmtGetAll));
            }
        } else {
            loge(mysql_stmt_error(mStmtGetAll));
        }

        return members;
    }

    ias::member * mysql_member_data_access::get(const std::size_t id) {
        ias::member * member = cache_get(id);
        // Check if there was a cache hit.
        if(member == nullptr)
            member = fetch_member_from_db(id);

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

        // Preparing the parameter.
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
