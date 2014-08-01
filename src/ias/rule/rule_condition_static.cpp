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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/rule/rule_condition_static.h>

// END Includes. /////////////////////////////////////////////////////

void RuleConditionStatic::setDevice( Device * device ) {
    // Checking the precondition.
    assert( device != nullptr );
    
    mDevice = device;
}

void RuleConditionStatic::setMember( const std::string & member ) {
    // Checking the precondition.
    assert( member.length() > 0 );
    
    mMemberIdentifier = member;
}

void RuleConditionStatic::setValue( const std::string & value ) {
    // Checking the precondition.
    assert( value.length() > 0 );
    
    mValue = value;
}

void RuleConditionStatic::setOperator( const Operator * op ) {
    // Checking the precondition.
    assert( op != nullptr );
    
    mOperator = op;
}

RuleConditionStatic::RuleConditionStatic( Device * device,
                                          const std::string & memberIdentifier,
                                          const std::string & value,
                                          const Operator * op ) {
    setDevice(device);
    setMember(memberIdentifier);
    setValue(value);
    setOperator(op);
}

RuleConditionStatic::~RuleConditionStatic( void ) {
    // Nothing to do here.
}

bool RuleConditionStatic::evaluate( void ) const {
    return ( mOperator->evaluate(mDevice->get(mMemberIdentifier),mValue) );
}
