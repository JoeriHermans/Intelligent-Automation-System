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

// Application dependencies.
#include <ias/application/application.h>
#include <ias/application/client/model/client_application_model.h>
#include <ias/application/client/view/console_client_application_view.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CLIENT_APPLICATION_H_
#define IAS_CLIENT_APPLICATION_H_

namespace ias {

class client_application : public application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Model of the client application.
     *
     * @note By default, this member will be equal to the null reference.
     */
    ias::client_application_model * mModel;

    /**
     * View of the client application.
     *
     * @note By default, this member will be equal to the null reference.
     */
    ias::view * mView;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void initialize_model(const int argc, const char ** argv);

    void initialize_view(const int argc, const char ** argv);

    void register_views(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    client_application(const int argc, const char ** argv);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~client_application(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void run(void);

    virtual void stop(void);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
