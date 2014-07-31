/**
 * A class which describes the properties and actions of a rule action.
 *
 * @date                    Jul 31, 2014
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

#ifndef RULE_ACTION_H_
#define RULE_ACTION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/device/action/action.h>

// END Includes. /////////////////////////////////////////////////////

class RuleAction {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the device which will need to execute the action.
     */
    Device * mDevice;
    
    /**
     * Contains the action which needs to be executed.
     */
    Action * mAction;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setDevice( Device * device );
    
    void setAction( Action * action );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    RuleAction( Device * device , Action * action );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleAction( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    void execute( void ) const;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_ACTION_H_ */
