/**
 * A class which represents the properties and actions of a command which is
 * responsible for removing a controller (and the associated devices, rules)
 * from the system.
 *
 * @date                    3 April, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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

#ifndef COMMAND_REMOVE_CONTROLLER_H_
#define COMMAND_REMOVE_CONTROLLER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/rule/rule.h>
#include <ias/util/container.h>
#include <ias/controller/controller.h>
#include <ias/user/command/command.h>

// END Includes. /////////////////////////////////////////////////////

class CommandRemoveController : public Command {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    static const char kIdentifier[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains all controllers which are associated with IAS.
     */
    Container<Controller *> * mControllers;

    /**
     * Contains all devices which are associated with IAS.
     */
    Container<Device *> * mDevices;

    /**
     * Contains all rules which are associated with IAS.
     */
    Container<Rule *> * mRules;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void removeDevices( const Controller * controller );

    void removeController( Controller * controller );

    inline void setControllers( Container<Controller *> * controllers );

    inline void setDevices( Container<Device *> * devices );

    inline void setRules( Container<Rule *> * rules );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    CommandRemoveController( Container<Controller *> * controllers,
                             Container<Device *> * devices,
                             Container<Rule *> * rules );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~CommandRemoveController( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::string execute( User * user, const std::string & parameters );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* COMMAND_REMOVE_CONTROLLER_H_ */
