/**
 * A set of functions which will prepare a socket to connect with a remote
 * SOCKS proxy.
 *
 * Please note that this class only allows outgoing connections to the proxy
 * server.
 *
 * Implementation according to RFC 1928 (https://www.ietf.org/rfc/rfc1928.txt)
 * and RFC 1929 (http://tools.ietf.org/html/rfc1929).
 *
 * @date                    December 12, 2014
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

#ifndef SOCKS_H_
#define SOCKS_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

/**
 * Contains the unique identifier of the socks proxy.
 */
extern const char kProxyIdentifierSocks[];

/**
 * Contains the supported SOCKS protocol version.
 */
extern const std::uint8_t kSocksProtocolVersion;

/**
 * Contains the method identifier of the "No authentication" method.
 */
extern const std::uint8_t kSocksMethodNoAuthentication;

/**
 * Contains the method identifier of the "username/password" method.
 */
extern const std::uint8_t kSocksMethodUsernamePassword;

/**
 * Contains the version identifier of the authentication protocol.
 */
extern const std::uint8_t kSocksVersionAuthenticateMethod;

// END Constants. ////////////////////////////////////////////////////

bool socksConnect( const std::string & proxyAddress,
                   const std::size_t proxyPort,
                   const std::string & clientAddress,
                   const std::size_t clientPort,
                   const int fd );

bool socksConnect( const std::string & proxyAddress,
                   const std::size_t proxyPort,
                   const std::string & clientAddress,
                   const std::size_t clientPort,
                   const std::string & username,
                   const std::string & password,
                   const int fd );

bool socksNegotiate( const std::string & username,
                     const std::string & password,
                     const int fd );

bool socksAuthenticate( const std::string & username,
                        const std::string & password,
                        const int fd );

bool socksRequest( const std::string & clientAddress,
                   const std::size_t clientPort,
                   const int fd );

#endif /* SOCKS_H_ */
