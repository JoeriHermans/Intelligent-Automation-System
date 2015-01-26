/**
 * A command which is responsible for loading a rule into IAS.
 *
 * @date                    Aug 3, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2013 Joeri HERMANS
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

#ifndef COMMAND_LOAD_RULE_H_
#define COMMAND_LOAD_RULE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/user/command/command.h>
#include <ias/rule/rule.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class CommandLoadRule : public Command {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    static const char kIdentifier[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the database connection which is necessary for loading
     * the rule.
     */
    DatabaseConnection * mDbConnection;

    /**
     * A container which holds all devices in IAS.
     */
    const Container<Device *> * mDevices;

    /**
     * A container which holds all rules in IAS.
     */
    Container<Rule *> * mRules;

    /**
     * A map which holds all operators.
     */
    const std::map<std::string,Operator *> * mOperators;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setDbConnection( DatabaseConnection * connection );

    void setDeviceContainer( const Container<Device *> * devices );

    void setRuleContainer( Container<Rule *> * rules );

    void setOperators( const std::map<std::string,Operator *> * operators );

    Rule * fetchRule( const std::size_t id );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    CommandLoadRule( DatabaseConnection * connection,
                     const Container<Device *> * devices,
                     Container<Rule *> * rules,
                     const std::map<std::string,Operator *> * operators );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~CommandLoadRule( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::string execute( User * user, const std::string & parameters );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* COMMAND_LOAD_RULE_H_ */
