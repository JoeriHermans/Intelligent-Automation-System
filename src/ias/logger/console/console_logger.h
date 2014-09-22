/**
 * A class which describes the properties and actions of a console logger. This
 * logger will write the outputs to the terminal.
 *
 * @date                    Sep 23, 2014
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

#ifndef CONSOLE_LOGGER_H_
#define CONSOLE_LOGGER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/logger/logger.h>
#include <ias/threadpool/threadpool.h>

// END Includes. /////////////////////////////////////////////////////

class ConsoleLogger : public Logger {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Static constant members which hold the unique identifier of each
     * type of log message.
     */
    static const char kDebug[];
    static const char kError[];
    static const char kInformation[];

    /**
     * Contains the type of this kind of logger.
     */
    static const char kType[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the threadpool which will be responsible for processing
     * the incoming log messages.
     */
    ThreadPool * mPool;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ConsoleLogger( void );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ConsoleLogger( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void debug( const std::string & message );

    virtual void error( const std::string & message );

    virtual void info( const std::string & message );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONSOLE_LOGGER_H_ */
