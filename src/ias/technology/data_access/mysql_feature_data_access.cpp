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
#include <ias/technology/data_access/mysql_feature_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Class constants. ////////////////////////////////////////

    const char mysql_feature_data_access::kStmtAdd[] =
        "";

    const char mysql_feature_data_access::kStmtGetAll[] =
        "SELECT id, parameter_value_type_id, identifier \
         FROM technology_members;";

    const char mysql_feature_data_access::kStmtGetId[] =
        "SELECT parameter_value_type_id, identifier \
         FROM technology_members \
         WHERE id = ?;";

    const char mysql_feature_data_access::kStmtRemove[] =
        "REMOVE FROM technology_members \
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
        // TODO Implement.
    }

    void mysql_feature_data_access::close_statements(void) {
        // TODO Implement.
    }

    void mysql_feature_data_access::prepare_statement_get_all(void) {
        // TODO Implement.
    }

    void mysql_feature_data_access::prepare_statement_get_id(void) {
        // TODO Implement.
    }

    void mysql_feature_data_access::prepare_statement_remove(void) {
        // TODO Implement.
    }

    void mysql_feature_data_access::prepare_statement_update(void) {
        // TODO Implement.
    }

    void mysql_feature_data_access::prepare_statement_add(void) {
        // TODO Implement.
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
