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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <fstream>
#include <iostream>

// Application dependencies.
#include <ias/logger/file/file_log_task.h>

// END Includes. /////////////////////////////////////////////////////

void FileLogTask::setMessage( const std::string & message ) {
    // Checking the precondition.
    assert( !message.empty() );

    mMessage = message;
}

void FileLogTask::setLogfile( std::ofstream * logfile ) {
    // Checking the precondition.
    assert( logfile != nullptr );

    mLogfile = logfile;
}

FileLogTask::FileLogTask( const std::string & message,
                          std::ofstream * logfile ) {
    setMessage(message);
    setLogfile(logfile);
}

void FileLogTask::execute( void ) {
    (*mLogfile) << mMessage;
}
