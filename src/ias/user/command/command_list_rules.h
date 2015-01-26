/**
 * A command which is responsible for listing all rules.
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

#ifndef COMMAND_LIST_RULES_H_
#define COMMAND_LIST_RULES_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/user/command/command.h>
#include <ias/rule/rule.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class CommandListRules : public Command {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    static const char kIdentifier[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A container which holds all rules in IAS.
     */
    const Container<Rule *> * mRules;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setRuleContainer( const Container<Rule *> * rules );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    CommandListRules( const Container<Rule *> * rules );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~CommandListRules( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::string execute( User * user, const std::string & parameters );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* COMMAND_LIST_RULES_H_ */
