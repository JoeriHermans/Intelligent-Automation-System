/**
 * A set of network utility functions which make the life of the
 * developer a little bit more pleasant.
 *
 * @date                    28 04 2016
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

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_NETWORK_UTIL_H_
#define IAS_NETWORK_UTIL_H_

namespace ias {

int connect(const std::string & address, const std::size_t port);

int connect_to_socks(const std::string & proxyAddress,
                     const std::size_t proxyPort,
                     const std::string & address,
                     const std::size_t port);

bool enable_keep_alive(const int fd);

bool disable_nagle(const int fd);

};

#endif
