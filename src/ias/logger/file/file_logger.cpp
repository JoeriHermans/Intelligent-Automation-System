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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <fstream>
#include <iostream>

// Application dependencies.
#include <ias/logger/file/file_logger.h>
#include <ias/logger/file/file_log_task.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Class constants. ////////////////////////////////////////////

const char FileLogger::kDebug[] = "debug";
const char FileLogger::kInformation[] = "information";
const char FileLogger::kError[] = "error";

// END Class constants. //////////////////////////////////////////////

inline void FileLogger::initialize( void ) {
    mPool = new ThreadPool(1);
}

void FileLogger::setFile( const std::string & filename ) {
    // Checking the precondition.
    assert( !filename.empty() );
    mLogfile.open(filename,std::ios::app);
    assert( mLogfile.is_open() );
}

FileLogger::FileLogger( const std::string & filename ) {
    initialize();
    setFile(filename);
}

FileLogger::~FileLogger( void ) {
    delete mPool; mPool = nullptr;
    mLogfile.close();
}

void FileLogger::debug( const std::string & message ) {
    std::string logMessage;

    logMessage = "# [" + std::string(kDebug) + "] " + message + "\n";
    mPool->enqueue(new FileLogTask(logMessage,&mLogfile));
}

void FileLogger::error( const std::string & message ) {
    std::string logMessage;

    logMessage = "# [" + std::string(kError) + "] " + message + '\n';
    mPool->enqueue(new FileLogTask(logMessage,&mLogfile));
}

void FileLogger::info( const std::string & message ) {
    std::string logMessage;

    logMessage = "# [" + std::string(kInformation) + "] " + message + '\n';
    mPool->enqueue(new FileLogTask(logMessage,&mLogfile));
}
