/**
 * A list of all global constants in IAS.
 *
 * @date                    24 05 2016
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
// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CONSTANTS_H_
#define IAS_CONSTANTS_H_

// BEGIN Configuration. //////////////////////////////////////////////

extern const char kConfigControllerIdentifier[];
extern const char kConfigControllerSecurityCode[];
extern const char kConfigDatabaseDriver[];
extern const char kConfigDatabaseHost[];
extern const char kConfigDatabasePassword[];
extern const char kConfigDatabaseSchema[];
extern const char kConfigDatabaseUser[];
extern const char kConfigDeviceList[];
extern const char kConfigHostPort[];
extern const char kConfigHostSslEnabled[];
extern const char kConfigHost[];
extern const char kConfigLoggerLogfilePath[];
extern const char kConfigLoggerType[];
extern const char kConfigNetworkControllerPort[];
extern const char kConfigNetworkControllerSslCertificiate[];
extern const char kConfigNetworkControllerSslKey[];
extern const char kConfigNetworkControllerSslPort[];
extern const char kConfigNetworkDevicePort[];
extern const char kConfigNetworkDeviceSslCertificate[];
extern const char kConfigNetworkDeviceSslKey[];
extern const char kConfigNetworkDeviceSslPort[];
extern const char kConfigNetworkEventPort[];
extern const char kConfigNetworkEventSslCertificate[];
extern const char kConfigNetworkEventSslKey[];
extern const char kConfigNetworkEventSslPort[];
extern const char kConfigNetworkUserPort[];
extern const char kConfigNetworkUserSslCertificate[];
extern const char kConfigNetworkUserSslKey[];
extern const char kConfigNetworkUserSslPort[];
extern const char kConfigPostSalt[];
extern const char kConfigPreSalt[];
extern const char kConfigSocksAddress[];
extern const char kConfigSocksPort[];

// END Configuration. ////////////////////////////////////////////////

// BEGIN Default values. /////////////////////////////////////////////

extern const char kDefaultServerAddress[];
extern const std::size_t kDefaultControllerServerPort;
extern const std::size_t kDefaultControllerServerSslPort;
extern const std::size_t kDefaultDeviceServerPort;
extern const std::size_t kDefaultUserServerPort;
extern const std::size_t kDefaultUserServerPortSsl;
extern const std::size_t kDefaultEventServerPort;
extern const std::size_t kDefaultEventServerSslPort;

// END Default values. ///////////////////////////////////////////////

// BEGIN Flags. //////////////////////////////////////////////////////

extern const char kFlagAddController[];
extern const char kFlagAddress[];
extern const char kFlagClient[];
extern const char kFlagConfig[];
extern const char kFlagController[];
extern const char kFlagEventStream[];
extern const char kFlagGenerateHash[];
extern const char kFlagKey[];
extern const char kFlagLogo[];
extern const char kFlagPort[];
extern const char kFlagServer[];
extern const char kFlagSocks[];
extern const char kFlagSsl[];
extern const char kFlagVersion[];

// END Flags. ////////////////////////////////////////////////////////

// BEGIN Others. /////////////////////////////////////////////////////

extern const char kOffline[];
extern const char kOnline[];
extern const char kTrimCharacters[];
extern const char kVersion[];

// END Others. ///////////////////////////////////////////////////////

#endif
