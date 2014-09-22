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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/logger/console/console_logger.h>
#include <ias/logger/console/console_log_task.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Class constants. ////////////////////////////////////////////

const char ConsoleLogger::kDebug[] = "debug";
const char ConsoleLogger::kError[] = "error";
const char ConsoleLogger::kInformation[] = "information";

// END Class constants. //////////////////////////////////////////////

inline void ConsoleLogger::initialize( void ) {
    mPool = new ThreadPool(1);
}

ConsoleLogger::ConsoleLogger( void ) {
    initialize();
}

ConsoleLogger::~ConsoleLogger( void ) {
    delete mPool; mPool = nullptr;
}

void ConsoleLogger::debug( const std::string & message ) {
    std::string logMessage;

    // Checking the precondition.
    assert( !message.empty() );

    logMessage = "# [" + std::string(kDebug) + "] " + message + "\n";
    mPool->enqueue(new ConsoleLogTask(logMessage));
}

void ConsoleLogger::error( const std::string & message ) {
    std::string logMessage;

    // Checking the precondition.
    assert( !message.empty() );

    logMessage = "# [" + std::string(kError) + "] " + message + "\n";
    mPool->enqueue(new ConsoleLogTask(logMessage));
}

void ConsoleLogger::info( const std::string & message ) {
    std::string logMessage;

    // Checking the precondition.
    assert( !message.empty() );

    logMessage = "# [" + std::string(kInformation) + "] " + message + "\n";
    mPool->enqueue(new ConsoleLogTask(logMessage));
}
