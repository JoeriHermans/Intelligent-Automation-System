/**
 * A class which acts as a data access layer for technology
 * features.
 *
 * @date                    03 06 2016
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
#include <ias/logger/logger.h>
#include <ias/technology/data_access/mysql_feature_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Class constants. ////////////////////////////////////////

    const char mysql_feature_data_access::kStmtAdd[] =
        "";

    const char mysql_feature_data_access::kStmtGetAll[] =
        "SELECT id, parameter_value_type_id, identifier \
         FROM technology_features;";

    const char mysql_feature_data_access::kStmtGetId[] =
        "SELECT parameter_value_type_id, identifier \
         FROM technology_features \
         WHERE id = ?;";

    const char mysql_feature_data_access::kStmtRemove[] =
        "DELETE FROM technology_features \
         WHERE id = ?;";

    const char mysql_feature_data_access::kStmtUpdate[] =
        "";

    // END Class constants. //////////////////////////////////////////

    inline void mysql_feature_data_access::initialize(void) {
        mDbConnection = nullptr;
        mStmtAdd = nullptr;
        mStmtGetId = nullptr;
        mStmtRemove = nullptr;
        mStmtUpdate = nullptr;
    }

    void mysql_feature_data_access::set_database_connection(ias::database_connection * dbConn) {
        // Checking the precondition.
        assert(dbConn != nullptr);

        mDbConnection = static_cast<MYSQL *>(dbConn->get_link());
    }

    void mysql_feature_data_access::set_value_type_da(ias::value_type_data_access * vtda) {
        // Checking the precondition.
        assert(vtda != nullptr);

        mStorageValueTypes = vtda;
    }

    void mysql_feature_data_access::initialize_statements(void) {
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

    void mysql_feature_data_access::close_statements(void) {
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

    void mysql_feature_data_access::prepare_statement_get_all(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetAll != nullptr);

        rc = mysql_stmt_prepare(mStmtGetAll, kStmtGetAll,
                                strlen(kStmtGetAll));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetAll));
    }

    void mysql_feature_data_access::prepare_statement_get_id(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtGetId != nullptr);

        rc = mysql_stmt_prepare(mStmtGetId, kStmtGetId,
                                strlen(kStmtGetId));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtGetId));
    }

    void mysql_feature_data_access::prepare_statement_remove(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtRemove != nullptr);

        rc = mysql_stmt_prepare(mStmtRemove, kStmtRemove,
                                strlen(kStmtRemove));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtRemove));
    }

    void mysql_feature_data_access::prepare_statement_update(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtUpdate != nullptr);

        rc = mysql_stmt_prepare(mStmtUpdate, kStmtUpdate,
                                strlen(kStmtUpdate));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtUpdate));
    }

    void mysql_feature_data_access::prepare_statement_add(void) {
        int rc;

        // Checking the precondition.
        assert(mStmtAdd != nullptr);

        rc = mysql_stmt_prepare(mStmtAdd, kStmtAdd,
                                strlen(kStmtAdd));
        // Check if the statement could be prepared.
        if(rc != 0)
            loge(mysql_stmt_error(mStmtAdd));
    }

    ias::feature * mysql_feature_data_access::fetch_feature_from_db(const std::size_t id) {
        ias::feature * feature = nullptr;

        // TODO Implement.

        return feature;
    }

    mysql_feature_data_access::mysql_feature_data_access(ias::database_connection * dbConn,
                                                         ias::value_type_data_access * vtda) {
        initialize();
        set_database_connection(dbConn);
        set_value_type_da(vtda);
        initialize_statements();
    }

    mysql_feature_data_access::~mysql_feature_data_access(void) {
        close_statements();
        cache_clear();
    }

    std::vector<ias::feature *> mysql_feature_data_access::get_all(void) {
        std::vector<ias::feature *> features;
        MYSQL_BIND result[3];

        // Buffer variables.
        std::size_t bufferId = 0;
        std::size_t bufferValueTypeId = 0;
        char bufferIdentifier[kDefaultStringSize + 1];

        // Clear the result structure.
        memset(result, 0, sizeof result);
        // Prepare the result types.
        // id
        result[0].buffer_type    = MYSQL_TYPE_LONG;
        result[0].buffer         = static_cast<void *>(&bufferId);
        result[0].is_unsigned    = 1;
        // value type id
        result[1].buffer_type    = MYSQL_TYPE_LONG;
        result[1].buffer         = static_cast<void *>(&bufferValueTypeId);
        result[1].is_unsigned    = 1;
        // identifier
        result[2].buffer_type    = MYSQL_TYPE_VAR_STRING;
        result[2].buffer         = static_cast<void *>(&bufferIdentifier);
        result[2].buffer_length  = kDefaultStringSize;

        mysql_stmt_bind_result(mStmtGetAll, result);
        if(mysql_stmt_execute(mStmtGetAll) == 0) {
            if(mysql_stmt_store_result(mStmtGetAll) == 0) {
                // Retrieve all elements.
                while(!mysql_stmt_fetch(mStmtGetAll)) {
                    ias::feature * feature;

                    // Fetch the value type associated with this feature.
                    const ias::value_type * vt = mStorageValueTypes->get(bufferValueTypeId);
                    // Type conversions to match class constructor.
                    std::string identifier = bufferIdentifier;
                    feature = new ias::feature(bufferId, identifier, vt);
                    features.push_back(feature);
                }
                // Store all the retrieve elements in the cache.
                cache_store_fast(features);
            }
        }

        // TODO Implement.

        return features;
    }

    ias::feature * mysql_feature_data_access::get(const std::size_t id) {
        ias::feature * feature = cache_get(id);
        // Check if there is a cache hit.
        if(feature == nullptr)
            // Try to fetch the feature from the database.
            feature = fetch_feature_from_db(id);

        return feature;
    }

    void mysql_feature_data_access::add(ias::feature * element) {
        // Checking the precondition.
        assert(element != nullptr);

        // TODO Implement.
    }

    void mysql_feature_data_access::remove(ias::feature * feature) {
        // Checking the precondition.
        assert(feature != nullptr);

        remove(feature->get_id());
    }

    void mysql_feature_data_access::remove(const std::size_t id) {
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

    void mysql_feature_data_access::update(ias::feature * element) {
        // Checking the precondition.
        assert(element != nullptr);

        // TODO Implement.
    }

};

#endif
#endif
