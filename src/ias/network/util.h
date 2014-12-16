/**
 * A set of network utility functions.
 *
 * @date                    December 13, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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

#ifndef NETWORK_UTIL_H_
#define NETWORK_UTIL_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// END Includes. /////////////////////////////////////////////////////

/**
 * A function which connect tries to connect to the specified address and port.
 *
 * @pre     The specified address cannot be equal to the empty string, and the
 *          specified port has to be larger than 0.
 * @param   address
 *          The address of the remote host, this can be an IP address or a FQDN.
 * @param   port
 *          A 16-bit port identifier, which is larger than 0.
 * @return  >= 0: A file descriptor associated with the connection.
 *          -1: Could not connect to the remote host.
 */
int connect( const std::string & address, const std::size_t port );

/**
 *
 */
bool enableKeepAlive( const int fd );

#endif /* NETWORK_UTIL_H_ */
