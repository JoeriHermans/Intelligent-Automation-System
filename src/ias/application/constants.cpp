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

// System dependencies.
#include <cstdio>

// Application dependencies.
#include <ias/application/constants.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Configuration. //////////////////////////////////////////////

const char kConfigControllerIdentifier[] = "controller_identifier";
const char kConfigControllerSecurityCode[] = "controller_security_code";
const char kConfigDatabaseDriver[] = "database_driver";
const char kConfigDatabaseHost[] = "database_host";
const char kConfigDatabasePassword[] = "database_password";
const char kConfigDatabaseSchema[] = "database_schema";
const char kConfigDatabaseUser[] = "database_user";
const char kConfigDeviceList[] = "devices";
const char kConfigHostPort[] = "server_port";
const char kConfigHostSslEnabled[] = "server_ssl_enabled";
const char kConfigHost[] = "server_address";
const char kConfigLoggerLogfilePath[] = "logger_filepath";
const char kConfigLoggerType[] = "logger_type";
const char kConfigNetworkControllerPort[] = "network_controller_port";
const char kConfigNetworkControllerSslCertificiate[] = "network_controller_ssl_certificate";
const char kConfigNetworkControllerSslKey[] = "network_controller_ssl_key";
const char kConfigNetworkControllerSslPort[] = "network_controller_ssl_port";
const char kConfigNetworkDevicePort[] = "network_device_port";
const char kConfigNetworkDeviceSslCertificate[] = "network_device_ssl_certificate";
const char kConfigNetworkDeviceSslKey[] = "network_device_ssl_key";
const char kConfigNetworkDeviceSslPort[] = "network_device_ssl_port";
const char kConfigNetworkEventPort[] = "network_event_port";
const char kConfigNetworkEventSslCertificate[] = "network_event_ssl_certificate";
const char kConfigNetworkEventSslKey[] = "network_event_ssl_key";
const char kConfigNetworkEventSslPort[] = "network_event_ssl_port";
const char kConfigNetworkUserPort[] = "network_user_port";
const char kConfigNetworkUserSslCertificate[] = "network_user_ssl_certificate";
const char kConfigNetworkUserSslKey[] = "network_user_ssl_key";
const char kConfigNetworkUserSslPort[] = "network_user_ssl_port";
const char kConfigPostSalt[] = "security_postsalt";
const char kConfigPreSalt[] = "security_presalt";
const char kConfigSocksAddress[] = "socks_address";
const char kConfigSocksPort[] = "socks_port";

// END Configuration. ////////////////////////////////////////////////

// BEGIN Default values. /////////////////////////////////////////////

const char kDefaultServerAddress[] = "127.0.0.1";
const std::size_t kDefaultControllerServerPort = 5000;
const std::size_t kDefaultControllerServerSslPort = 6000;
const std::size_t kDefaultDeviceServerPort = 5002;
const std::size_t kDefaultUserServerPort = 5001;
const std::size_t kDefaultUserServerPortSsl = 6001;
const std::size_t kDefaultEventServerPort = 5003;
const std::size_t kDefaultEventServerSslPort = 6003;

// END Default values. ///////////////////////////////////////////////

// BEGIN Flags. //////////////////////////////////////////////////////

const char kFlagAddController[] = "--addc";
const char kFlagAddress[] = "--address";
const char kFlagClient[] = "--client";
const char kFlagConfig[] = "--config";
const char kFlagController[] = "--controller";
const char kFlagEventStream[] = "--eventstream";
const char kFlagGenerateHash[] = "--hash";
const char kFlagKey[] = "--key";
const char kFlagLogo[] = "--logo";
const char kFlagPort[] = "--port";
const char kFlagServer[] = "--server";
const char kFlagSocks[] = "--socks";
const char kFlagSsl[] = "--ssl";
const char kFlagVersion[] = "--version";

// END Flags. ////////////////////////////////////////////////////////

// BEGIN Others. /////////////////////////////////////////////////////

const char kOffline[] = "Offline";
const char kOnline[] = "Online";
const char kVersion[] = "IAS 0.2.0 beta";

// END Others. ///////////////////////////////////////////////////////
