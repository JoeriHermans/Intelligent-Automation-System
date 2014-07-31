/**
 * A class which describes the properties and actions of a rule condition set.
 * A rule conditions evaluates the boolean value of a whole set.
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

#ifndef RULE_CONDITION_SET_H_
#define RULE_CONDITION_SET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>

// Application dependencies.
#include <ias/rule/rule_condition.h>

// END Includes. /////////////////////////////////////////////////////

class RuleConditionSet {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the conditions which need to be evaluated in this set.
     */
    std::vector<RuleCondition *> mConditions;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setConditions( const std::vector<RuleCondition *> & conditions );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    RuleConditionSet( const std::vector<RuleCondition *> & conditions );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleConditionSet( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    bool evaluate( void ) const;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_CONDITION_SET_H_ */
