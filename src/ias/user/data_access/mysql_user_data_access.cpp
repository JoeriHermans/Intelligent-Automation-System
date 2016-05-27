/**
 *
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/user/data_access/mysql_user_data_access.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    mysql_user_data_access::mysql_user_data_access(void) {
        // TODO Implement.
    }

    mysql_user_data_access::~mysql_user_data_access(void) {
        // TODO Implement.
    }

    std::vector<ias::user *> mysql_user_data_access::get_all(void) const {
        std::vector<ias::user *> users;

        // TODO Implement.

        return users;
    }

    ias::user * mysql_user_data_access::get(const std::size_t id) const {
        ias::user * user = nullptr;

        // TODO Implement.

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

        // TODO Implement.
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
