/**
 * Contains a list of all constants being used in IAS.
 *
 * @date                    Jul 2, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2013 Joeri HERMANS
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

#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// BEGIN Includes. ///////////////////////////////////////////////////
// END Includes. /////////////////////////////////////////////////////

extern const char kFlagController[];
extern const char kFlagServer[];
extern const char kFlagConfig[];
extern const char kFlagClient[];
extern const char kFlagAddress[];
extern const char kFlagPort[];
extern const char kFlagSsl[];
extern const char kFlagSocks[];
extern const char kFlagEventStream[];
extern const char kFlagKey[];
extern const char kFlagLogo[];

extern const char kTrimCharacters[];

extern const char kVersion[];
extern const char kOnline[];
extern const char kOffline[];

extern const char kConfigDatabaseDriver[];
extern const char kConfigDatabaseUser[];
extern const char kConfigDatabasePassword[];
extern const char kConfigDatabaseSchema[];
extern const char kConfigDatabaseHost[];
extern const char kConfigHost[];
extern const char kConfigHostPort[];
extern const char kConfigHostSslEnabled[];
extern const char kConfigControllerIdentifier[];
extern const char kConfigControllerSecurityCode[];
extern const char kConfigDeviceList[];
extern const char kConfigPreSalt[];
extern const char kConfigPostSalt[];
extern const char kConfigLoggerType[];
extern const char kConfigLoggerLogfilePath[];

extern const char kConfigNetworkControllerPort[];
extern const char kConfigNetworkControllerSslPort[];
extern const char kConfigNetworkControllerSslCertificiate[];
extern const char kConfigNetworkControllerSslKey[];
extern const char kConfigNetworkUserPort[];
extern const char kConfigNetworkUserSslPort[];
extern const char kConfigNetworkUserSslCertificate[];
extern const char kConfigNetworkUserSslKey[];
extern const char kConfigNetworkDevicePort[];
extern const char kConfigNetworkDeviceSslPort[];
extern const char kConfigNetworkDeviceSslCertificate[];
extern const char kConfigNetworkDeviceSslKey[];
extern const char kConfigNetworkEventPort[];
extern const char kConfigNetworkEventSslPort[];
extern const char kConfigNetworkEventSslCertificate[];
extern const char kConfigNetworkEventSslKey[];

extern const char kConfigSocksAddress[];
extern const char kConfigSocksPort[];

extern const char kProtocolAck[];
extern const char kProtocolNack[];

extern const char kDefaultServerAddress[];
extern const unsigned int kDefaultControllerServerPort;
extern const unsigned int kDefaultDeviceServerPort;
extern const unsigned int kDefaultUserServerPort;
extern const unsigned int kDefaultUserServerPortSsl;
extern const unsigned int kDefaultEventServerPort;
extern const unsigned int kDefaultEventServerSslPort;

#endif /* CONSTANTS_H_ */
