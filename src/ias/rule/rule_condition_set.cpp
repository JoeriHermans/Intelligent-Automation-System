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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/rule/rule_condition_set.h>

// END Includes. /////////////////////////////////////////////////////

void RuleConditionSet::setConditions( 
    const std::vector<RuleCondition *> & conditions ) {
    // Checking the precondition.
    assert( conditions.size() > 0 );
    mConditions = conditions;
}

RuleConditionSet::RuleConditionSet( 
    const std::vector<RuleCondition *> & conditions ) {
    setConditions(conditions);
}

RuleConditionSet::~RuleConditionSet( void ) {
    for( RuleCondition * condition : mConditions ) {
        delete condition;
    }
}

bool RuleConditionSet::evaluate( void ) const {
    bool result;
    
    result = true;
    for( auto it = mConditions.begin(); 
        it != mConditions.end() && result ; ++it ) {
        result &= (*it)->evaluate();
    }
    
    return ( result );
}

const std::vector<RuleCondition *> & RuleConditionSet::getConditions( void ) const {
    return ( mConditions );
}
