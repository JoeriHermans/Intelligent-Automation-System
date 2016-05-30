/**
 * Set of general utility functions which can be used throughout the
 * application.
 *
 * @date                    02 05 2016
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
#include <string>
#include <unordered_map>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_UTIL_H_
#define IAS_UTIL_H_

namespace ias {

    bool flag_specified(const int argc, const char ** argv, const char * flag);

    int flag_index(const int argc, const char ** argv, const char * flag);

    std::string get_ias_version(void);

    bool read_configuration_file(const std::string & path,
                                 std::unordered_map<std::string, std::string> & c);

    void trim(std::string & str);

    std::string sha256(const std::string & str,
                       const std::string & preSalt,
                       const std::string & postSalt);

    bool file_exists(const std::string & path);

    /**
     * Generates a SHA256 string based on the global salts.
     *
     * @param str The string to hash.
     * @return A SHA256 hashed string.
     */
    std::string sha256(const std::string & str);

    /**
     * Globals defining the global SHA256 pre- and post-salt as defined
     * by the IAS configuration.
     */
    extern std::string gSaltPre;
    extern std::string gSaltPost;

};

#endif
