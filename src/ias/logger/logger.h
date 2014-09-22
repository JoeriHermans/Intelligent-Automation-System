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

#ifndef LOGGER_H_
#define LOGGER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/logger/enum_log_level.h>

// END Includes. /////////////////////////////////////////////////////

class Logger {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the singleton instance of the logger.
     */
    static Logger * mLogger;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Logger( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void debug( const std::string & message ) = 0;

    virtual void error( const std::string & message ) = 0;

    virtual void info( const std::string & message ) = 0;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////

    static void setLogger( Logger * logger ) {
        delete mLogger;
        mLogger = logger;
    }

    static Logger * getLogger( void ) {
        return ( mLogger );
    }

    static void cleanup( void ) {
        delete mLogger;
    }

    static void d( const std::string & message ) {
        Logger * logger;

        logger = Logger::getLogger();
        logger->debug(message);
    }

    static void e( const std::string & message ) {
        Logger * logger;

        logger = Logger::getLogger();
        logger->error(message);
    }

    static void i( const std::string & message ) {
        Logger * logger;

        logger = Logger::getLogger();
        logger->info(message);
    }

    // END Static methods. ///////////////////////////////////////////

};

void logd( const std::string & message ) {
    Logger::d(message);
}

void loge( const std::string & message ) {
    Logger::e(message);
}

void logi( const std::string & message ) {
    Logger::i(message);
}

#endif /* LOGGER_H_ */
