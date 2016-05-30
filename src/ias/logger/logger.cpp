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
#include <cassert>
#include <unistd.h>

// Application dependencies.
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    // BEGIN Singletons. /////////////////////////////////////////////

    ias::logger * ias::logger::mLogger = nullptr;

    // END Singletons. ///////////////////////////////////////////////

    void logger::set_logger(ias::logger * logger) {
        // Checking the precondition.
        assert(logger != nullptr);

        // Cleanup the old logger.
        cleanup();
        // Set the new logger.
        mLogger = logger;
    }

    ias::logger * logger::get_logger(void) {
        return mLogger;
    }

    void logger::cleanup(void) {
        if(mLogger != nullptr) {
            delete mLogger;
            mLogger = nullptr;
        }
    }

    void logger::d(const std::string & message) {
        ias::logger * logger;

        logger = logger::get_logger();
        if(logger != nullptr)
            logger->debug(message);
    }

    void logger::e(const std::string & message) {
        ias::logger * logger;

        logger = logger::get_logger();
        if(logger != nullptr)
            logger->error(message);
    }

    void logger::i(const std::string & message) {
        ias::logger * logger;

        logger = logger::get_logger();
        if(logger != nullptr)
            logger->info(message);
    }

    void logger::c(const std::string & message) {
        ias::logger * logger;

        logger = logger::get_logger();
        if(logger != nullptr)
            logger->critical(message);
    }

    void logger::flush(void) {
        usleep(1000);
    }

    void logd(const std::string & message) {
        logger::d(message);
    }

    void logi(const std::string & message) {
        logger::i(message);
    }

    void logc(const std::string & message) {
        logger::c(message);
    }

    void loge(const std::string & message) {
        logger::e(message);
    }

};
