/**
 * A class which describes the abstract properties and actions of a rule
 * condition.
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

#ifndef RULE_CONDITION_H_
#define RULE_CONDITION_H_

// BEGIN Includes. ///////////////////////////////////////////////////
// END Includes. /////////////////////////////////////////////////////

class RuleCondition {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    RuleCondition( void ) = default;
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleCondition( void ) = default;
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual bool evaluate( void ) const = 0;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_CONDITION_H_ */
