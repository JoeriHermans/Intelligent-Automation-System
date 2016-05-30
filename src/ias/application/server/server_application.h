/**
 * A class which describes the properties and actions of the server
 * application. This application will handle the main functionality
 * of IAS, applying rules, dispatching commands, setting up the
 * servers.
 *
 * @date                    30 05 2016
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
#include <string>
#include <unordered_map>

// Application dependencies.
#include <ias/application/application.h>
#include <ias/data_access/data_access.h>
#include <ias/user/data_access/user_data_access.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_SERVER_APPLICATION_H_
#define IAS_SERVER_APPLICATION_H_

namespace ias {

class server_application : public application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Holds the default absolute path to the IAS server configuration
     * file.
     */
    static const char kDefaultConfigPath[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Data access members for IAS objects.
     *
     * @note By default, this will be equal to the null reference.
     */
    ias::user_data_access * mStorageUsers;

    /**
     * Holds the properties which have been read from the configuration file.
     *
     * @note By default, this map will be initialized with default values.
     */
    std::unordered_map<std::string, std::string> mConfig;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void analyze_arguments(const int argc, const char ** argv);

    void initialize_default_configuration(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    server_application(const int argc, const char ** argv);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~server_application(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void stop(void);

    virtual void run(void);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif