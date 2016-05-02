/**
 * An abstract class for the IAS logger interface.
 *
 * @date                    02 05 2016
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

// Application dependencies.
#include <ias/logger/enum_log_level.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_LOGGER_H_
#define IAS_LOGGER_H_

namespace ias {

class logger {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Static members. /////////////////////////////////////////////////

    /**
     * Holds the singleton instance of the logger.
     */
    static ias::logger * mLogger;

    // END Static members. ///////////////////////////////////////////////////

    // BEGIN Private members. ////////////////////////////////////////////////
    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    logger(void) = default;

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~logger(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void error(const std::string & message) = 0;

    virtual void info(const std::string & message) = 0;

    virtual void debug(const std::string & message) = 0;

    virtual void critical(const std::string & message) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////

    static void set_logger(ias::logger * logger);

    static ias::logger * get_logger(void);

    static void cleanup(void);

    static void e(const std::string & message);

    static void i(const std::string & message);

    static void d(const std::string & message);

    static void c(const std::string & message);

    // END Public static methods. ////////////////////////////////////////////

};

void logc(const std::string & message);

void logd(const std::string & message);

void logi(const std::string & message);

void loge(const std::string & message);

};

#endif
