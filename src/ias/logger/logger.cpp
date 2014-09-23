/**
 * A class which describes the properties and actions of a logger.
 *
 * @date                    Sep 22, 2014
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

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

void Logger::setLogger( Logger * logger ) {
    delete mLogger;
    mLogger = logger;
}

Logger * Logger::getLogger( void ) {
    return ( mLogger );
}

void Logger::cleanup( void ) {
    delete mLogger;
}

void Logger::d( const std::string & message ) {
    Logger * logger;

    logger = Logger::getLogger();
    logger->debug(message);
}

void Logger::e( const std::string & message ) {
    Logger * logger;

    logger = Logger::getLogger();
    logger->error(message);
}

void Logger::i( const std::string & message ) {
    Logger * logger;

    logger = Logger::getLogger();
    logger->info(message);
}

void logd( const std::string & message ) {
    Logger::d(message);
}

void loge( const std::string & message ) {
    Logger::e(message);
}

void logi( const std::string & message ) {
    Logger::i(message);
}
