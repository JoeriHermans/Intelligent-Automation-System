/**
 * A set of functions which will prepare a socket to connect with a
 * remote SOCKS proxy. Please note that this class only allows outgoing
 * connections to the proxy server. Implementation according to
 * RFC 1928 and RFC 1929.
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

#ifndef IAS_SOCKS_H_
#define IAS_SOCKS_H_

namespace ias {

// BEGIN Constants. //////////////////////////////////////////////////

/**
 * Hold the unique identifier of the SOCKS proxy.
 */
extern const char kProxyIdentifierSocks[];

/**
 * Holds the supported SOCKS protocol version.
 */
extern const std::uint8_t kSocksProtocolVersion;

/**
 * Holds the method identifier of the "No authentication" method.
 */
extern const std::uint8_t kSocksMethodNoAuthentication;

/**
 * Contains the method identifier of the "username/password" method.
 */
extern const std::uint8_t kSocksMethodUsernamePassword;

/**
 * Hold the version identifier of the authentication protocol.
 */
extern const std::uint8_t kSocksVersionAuthenticateMethod;

// END Constants. ////////////////////////////////////////////////////

bool socks_connect(const int fd,
                   const std::string & address,
                   const std::size_t port);

bool socks_connect(const int fd,
                   const std::string & address,
                   const std::size_t port,
                   const std::string & username,
                   const std::string & password);

bool socks_negotiate(const int fd,
                     const std::string & username,
                     const std::string & password);

bool socks_authenticate(const int fd,
                        const std::string & username,
                        const std::string & password);

bool socks_request(const int fd,
                   const std::string & address,
                   const std::size_t port);

};

#endif
