/**
 * A class which describes the actions and properties of a value type.
 * A value type indicates the type (e.g., integer) of a specific
 * parameter and can be used to validate it.
 *
 * @date                    03 05 2016
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
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void value_type::initialize(void) {
        mId = 0;
    }

    void value_type::compile_pattern(const std::string & regex) {
        mPattern = std::regex(regex, std::regex_constants::extended);
    }

    void value_type::set_id(const std::size_t id) {
        // Checking the precondition.
        assert(id > 0);

        mId = id;
    }

    value_type::value_type(const std::size_t id,
                           const std::string & pattern) {
        initialize();
        set_id(id);
        compile_pattern(pattern);
    }

    const std::size_t value_type::get_id(void) const {
        return mId;
    }

    bool value_type::matches(const std::string & argument) const {
        return std::regex_match(argument, mPattern);
    }

};
