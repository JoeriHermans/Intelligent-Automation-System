/**
 * An enumeration which describes the gender of a person or other
 * entity. This enumeration is implemented according to
 * ISO/IEC 5218.
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
#include <cstdio>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    enum class user_gender : std::uint8_t {
        NOT_KNOWN = 0,
        MALE = 1,
        FEMALE = 2,
        NOT_APPLICABLE = 9
    };

};
