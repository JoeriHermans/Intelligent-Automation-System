/**
 * A class which describes the properties and actions of a file logger. This
 * logger will be responsible for writing all log messages to a specified file.
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

#ifndef FILE_LOGGER_H_
#define FILE_LOGGER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <fstream>
#include <iostream>

// Application dependencies.
#include <ias/threadpool/threadpool.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

class FileLogger : public Logger {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Contain the human-readable flags which can be used to indicated
     * messages in the log file.
     */
    static const char kDebug[];
    static const char kInformation[];
    static const char kError[];

    /**
     * Contains the identifier of this type of logger.
     */
    static const char kType[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A threadpool which handles the incoming statements and writes the
     * messages to the logfile in an async manner.
     */
    ThreadPool * mPool;

    /**
     * A stream which will be responsible for writing to the logfile.
     */
    std::ofstream mLogfile;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setFile( const std::string & filename );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    FileLogger( const std::string & filename );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~FileLogger( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void debug( const std::string & message );

    virtual void error( const std::string & message );

    virtual void info( const std::string & message );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* FILE_LOGGER_H_ */
