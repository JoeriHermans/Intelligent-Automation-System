/**
 * A class which will act as a data access layer through a
 * PostgreSQL database connection.
 *
 * @date                    31 05 2016
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
#if IAS_DATABASE_DRIVER == 'P' || IAS_DATABASE_DRIVER == 'A'

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/user/data_access/postgresql_user_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void postgresql_user_data_access::initialize(void) {
        // TODO Implement.
    }

    postgresql_user_data_access::postgresql_user_data_access(ias::database_connection * dbConn) {
        initialize();
    }

    postgresql_user_data_access::~postgresql_user_data_access(void) {
        // TODO Implement.
    }

    std::vector<ias::user *> postgresql_user_data_access::get_all(void) const {
        std::vector<ias::user *> users;

        // TODO Implement.

        return users;
    }

    ias::user * postgresql_user_data_access::get(const std::size_t id) const {
        ias::user * user = nullptr;

        // TODO Implement.

        return user;
    }

    void postgresql_user_data_access::add(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        // TODO Implement.
    }

    void postgresql_user_data_access::remove(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        remove(user->get_id());
    }

    void postgresql_user_data_access::remove(const std::size_t id) {
        // TODO Implement.
    }

    void postgresql_user_data_access::update(ias::user * user) {
        // Checking the precondition.
        assert(user != nullptr);

        // TODO Implement.
    }

};

#endif
#endif
