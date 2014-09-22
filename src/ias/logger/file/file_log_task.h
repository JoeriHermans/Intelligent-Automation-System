/**
 * A class which represents the properties and actions of a file log task.
 * This task will be responsible for writing the message to the file.
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

#ifndef FILE_LOG_TASK_H_
#define FILE_LOG_TASK_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/threadpool/task.h>

// END Includes. /////////////////////////////////////////////////////

class FileLogTask : public Task {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the string which needs to be written to the file.
     */
    std::string mMessage;

    /**
     * Contains a reference to the stream which is responsible to
     * the logfile..
     */
    std::ofstream * mLogfile;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setMessage( const std::string & message );

    void setLogfile( std::ofstream * logfile );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    FileLogTask( const std::string & message,
                 std::ofstream * logfile );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~FileLogTask( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void execute( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* FILE_LOG_TASK_H_ */
