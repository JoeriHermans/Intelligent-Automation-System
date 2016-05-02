/**
 * A class which describes the properties and actions of a console
 * logger. This logger will write the log-messages to the standard
 * output of the terminal.
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

// Application dependencies.
#include <ias/logger/logger.h>
#include <ias/threadpool/threadpool.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CONSOLE_LOGGER_H_
#define IAS_CONSOLE_LOGGER_H_

namespace ias {

class console_logger : public logger {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Constants which hold the unique identifier of each type of log message.
     */
    static const char kDebug[];
    static const char kInfo[];
    static const char kError[];
    static const char kCritical[];

    /**
     * Contains the unique type identifier of the logger.
     */
    static const char kType[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the threadpool which will be responsible for processing the
     * incoming log messages.
     */
    ias::threadpool * mPool;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    inline void spawn_threadpool(const std::size_t numThreads);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    console_logger(void);

    console_logger(const std::size_t numThreads);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~console_logger(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void debug(const std::string & message);

    virtual void info(const std::string & message);

    virtual void error(const std::string & message);

    virtual void critical(const std::string & message);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
