/**
 * A task which is responsible for writing the message to the
 * standard output.
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
#include <ias/logger/console/console_log_task.h>

// END Includes. /////////////////////////////////////////////////////

void ConsoleLogTask::setMessage( const std::string & message ) {
    // Checking the precondition.
    assert( !message.empty() );

    mMessage = message;
}

ConsoleLogTask::ConsoleLogTask( const std::string & message ) {
    setMessage(message);
}

void ConsoleLogTask::execute( void ) {
    std::cout << mMessage;
    std::cout.flush();
}
