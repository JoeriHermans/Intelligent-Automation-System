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

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/application/constants.h>

// END Includes. /////////////////////////////////////////////////////

const char kFlagController[] = "--controller";
const char kFlagServer[] = "--server";
const char kFlagConfig[] = "--config";
const char kFlagClient[] = "--client";
const char kFlagAddress[] = "--address";
const char kFlagPort[] = "--port";
const char kFlagSsl[] = "--ssl";
const char kFlagSocks[] = "--socks";

const char kTrimCharacters[] = " \t\n\r";

const char kVersion[] = "IAS 0.1.0";
const char kOnline[] = "Online";
const char kOffline[] = "Offline";

const char kConfigDatabaseDriver[] = "database_driver";
const char kConfigDatabaseUser[] = "database_username";
const char kConfigDatabasePassword[] = "database_password";
const char kConfigDatabaseSchema[] = "database_schema";
const char kConfigDatabaseHost[] = "database_host";
const char kConfigHost[] = "server_address";
const char kConfigHostPort[] = "server_port";
const char kConfigHostSslEnabled[] = "server_ssl_enabled";
const char kConfigControllerIdentifier[] = "controller_identifier";
const char kConfigControllerSecurityCode[] = "controller_security_code";
const char kConfigDeviceList[] = "devices";
const char kConfigPreSalt[] = "security_presalt";
const char kConfigPostSalt[] = "security_postsalt";
const char kConfigLoggerType[] = "logger_type";
const char kConfigLoggerLogfilePath[] = "logger_filepath";

const char kConfigNetworkControllerPort[] = "network_controller_port";
const char kConfigNetworkControllerSslPort[] = "network_controller_ssl_port";
const char kConfigNetworkControllerSslCertificiate[] = "network_controller_ssl_certificate";
const char kConfigNetworkControllerSslKey[] = "network_controller_ssl_key";
const char kConfigNetworkUserPort[] = "network_user_port";
const char kConfigNetworkUserSslPort[] = "network_user_ssl_port";
const char kConfigNetworkUserSslCertificate[] = "network_user_ssl_certificate";
const char kConfigNetworkUserSslKey[] = "network_user_ssl_key";
const char kConfigNetworkDevicePort[] = "network_device_port";
const char kConfigNetworkDeviceSslPort[] = "network_device_ssl_port";
const char kConfigNetworkDeviceSslCertificate[] = "network_device_ssl_certificate";
const char kConfigNetworkDeviceSslKey[] = "network_device_ssl_key";

const char kConfigSocksAddress[] = "socks_address";
const char kConfigSocksPort[] = "socks_port";

const char kProtocolAck[] = "{\"response\": \"ACK\"}";
const char kProtocolNack[] = "{\"response\": \"NACK\"}";

const char kDefaultServerAddress[] = "127.0.0.1";
const unsigned int kDefaultDeviceServerPort = 5002;
const unsigned int kDefaultControllerServerPort = 5000;
const unsigned int kDefaultUserServerPort = 5001;
const unsigned int kDefaultUserServerPortSsl = 6001;
