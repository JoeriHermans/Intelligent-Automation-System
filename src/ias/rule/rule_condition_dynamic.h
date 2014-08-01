/**
 * A class which describes the properties and actions of a dynamic rule
 * condition, i.e., the rule condition can depend on the current state of other
 * devices.
 *
 * @date                    Aug 1, 2014
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

#ifndef RULE_CONDITION_DYNAMIC_H_
#define RULE_CONDITION_DYNAMIC_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/device/device.h>
#include <ias/operator/operator.h>
#include <ias/rule/rule_condition.h>

// END Includes. /////////////////////////////////////////////////////

class RuleConditionDynamic : public RuleCondition {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * Contains the devices which need to be evaluated.
     */
    Device * mDeviceLeft;
    Device * mDeviceRight;
    
    /**
     * Contains the member identifiers of the devices which need to be compared.
     */
    std::string mMemberLeft;
    std::string mMemberRight;
    
    /**
     * contains the operator of the condition.
     */
    const Operator * mOperator;
    
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
   
    void setDevices( Device * deviceLeft,
                     Device * deviceRight );
    
    void setMemberIdentifiers( const std::string & memberLeft,
                               const std::string & memberRight );
    
    void setOperator( const Operator * op );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    RuleConditionDynamic( Device * deviceLeft,
                          const std::string & memberLeft,
                          Device * deviceRight,
                          const std::string & memberRight,
                          const Operator * op );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleConditionDynamic( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual bool evaluate( void ) const;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_CONDITION_DYNAMIC_H_ */
