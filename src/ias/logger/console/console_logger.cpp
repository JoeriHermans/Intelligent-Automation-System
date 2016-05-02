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

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/logger/console/console_logger.h>
#include <ias/logger/console/console_log_task.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Class constants. ////////////////////////////////////////

    const char ias::console_logger::kDebug[] = "debug";
    const char ias::console_logger::kInfo[] = "information";
    const char ias::console_logger::kError[] = "error";
    const char ias::console_logger::kCritical[] = "critical";
    const char ias::console_logger::kType[] = "console";

    // END Class constants. //////////////////////////////////////////

    inline void console_logger::initialize(void) {
        mPool = nullptr;
    }

    inline void console_logger::spawn_threadpool(const std::size_t numThreads) {
        // Checking the precondition.
        assert(numThreads > 0);

        mPool = new ias::threadpool(numThreads);
    }

    console_logger::console_logger(void) {
        initialize();
        spawn_threadpool(1);
    }

    console_logger::console_logger(const std::size_t numThreads) {
        initialize();
        spawn_threadpool(numThreads);
    }

    console_logger::~console_logger(void) {
        delete mPool; mPool = nullptr;
    }

    void console_logger::debug(const std::string & message) {
        // Checking the precondition.
        assert(!message.empty());

        std::string logMessage = "# [" + std::string(kDebug) + "] " + message + "\n";
        mPool->enqueue(new ias::console_log_task(logMessage));
    }

    void console_logger::info(const std::string & message) {
        // Checking the precondition.
        assert(!message.empty());

        std::string logMessage = "# [" + std::string(kInfo) + "] " + message + "\n";
        mPool->enqueue(new ias::console_log_task(logMessage));
    }

    void console_logger::error(const std::string & message) {
        // Checking the precondition.
        assert(!message.empty());

        std::string logMessage = "# [" + std::string(kError) + "] " + message + "\n";
        mPool->enqueue(new ias::console_log_task(logMessage));
    }

    void console_logger::critical(const std::string & message) {
        // Checking the precondition.
        assert(!message.empty());

        std::string logMessage = "# [" + std::string(kCritical) + "] " + message + "\n";
        mPool->enqueue(new ias::console_log_task(logMessage));
    }

};
