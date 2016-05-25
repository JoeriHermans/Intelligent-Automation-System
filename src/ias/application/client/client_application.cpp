/**
 * An application which is responsible for handling the client / server
 * communications.
 *
 * @date                    25 05 2016
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
#include <ias/application/client/client_application.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void client_application::initialize(void) {
        mModel = nullptr;
        mView = nullptr;
    }

    void client_application::initialize_model(const int argc, const char ** argv) {
        // Checking the precondition.
        assert(argc > 0 && argv != nullptr);

        mModel = new ias::client_application_model();
    }

    void client_application::initialize_view(const int argc, const char ** argv) {
        // Checking the precondition.
        assert(argc > 0 && argv != nullptr);

        mView = new ias::console_client_application_view(argc, argv, mModel);
    }

    void client_application::register_views(void) {
        mModel->add_observer(mView);
    }

    client_application::client_application(const int argc, const char ** argv) {
        initialize();
        initialize_model(argc, argv);
        initialize_view(argc, argv);
        register_views();
    }

    client_application::~client_application(void) {
        delete mModel; mModel = nullptr;
        delete mView; mView = nullptr;
    }

    void client_application::run(void) {
        mView->paint();
    }

    void client_application::stop(void) {
        // Nothing to do here.
    }

};
