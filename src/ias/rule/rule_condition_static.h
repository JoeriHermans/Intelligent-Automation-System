/**
 * A class which describes the properties and actions of a static
 * condition rule.
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

#ifndef RULE_CONDITION_STATIC_H_
#define RULE_CONDITION_STATIC_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/operator/operator.h>
#include <ias/rule/rule_condition.h>

// END Includes. /////////////////////////////////////////////////////

class RuleConditionStatic : public RuleCondition {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * Contains the device which needs to be evaluated.
     */
    Device * mDevice;
    
    /**
     * Contains the member which needs to be checked.
     */
    std::string mMemberIdentifier;
    
    /**
     * Contains the value to which the state must be compared to.
     */
    std::string mValue;
    
    /**
     * Contains the operator which must evaluate the expression.
     */
    const Operator * mOperator;
    
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setDevice( Device * device );
    
    void setMember( const std::string & member );
    
    void setValue( const std::string & value );
    
    void setOperator( const Operator * op );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    RuleConditionStatic( Device * device,
                         const std::string & memberIdentifier,
                         const std::string & value,
                         const Operator * op );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleConditionStatic( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual bool evaluate( void ) const;
        
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_CONDITION_STATIC_H_ */
