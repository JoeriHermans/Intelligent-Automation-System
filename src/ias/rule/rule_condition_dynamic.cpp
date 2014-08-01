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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/rule/rule_condition_dynamic.h>

// END Includes. /////////////////////////////////////////////////////

void RuleConditionDynamic::setDevices( Device * deviceLeft,
                                       Device * deviceRight ) {
    // Checking the precondition.
    assert( deviceLeft != nullptr && deviceRight != nullptr );
    
    mDeviceLeft = deviceLeft;
    mDeviceRight = deviceRight;
}

void RuleConditionDynamic::setMemberIdentifiers( 
    const std::string & memberLeft,
    const std::string & memberRight ) {
    // Checking the precondition.
    assert( memberLeft.length() > 0 && memberRight.length() > 0 );
    
    mMemberLeft = memberLeft;
    mMemberRight = memberRight;
}

void RuleConditionDynamic::setOperator( const Operator * op ) {
    // Checking the precondition.
    assert( op != nullptr );
    
    mOperator = op;
}

RuleConditionDynamic::RuleConditionDynamic(
    Device * deviceLeft,
    const std::string & memberLeft,
    Device * deviceRight,
    const std::string & memberRight,
    const Operator * op ) {
    setDevices(deviceLeft,deviceRight);
    setMemberIdentifiers(memberLeft,memberRight);
    setOperator(op);
}

RuleConditionDynamic::~RuleConditionDynamic( void ) {
    // Nothing to do here.
}

bool RuleConditionDynamic::evaluate( void ) const {
    return ( mOperator->evaluate(mDeviceLeft->get(mMemberLeft),
                                 mDeviceRight->get(mMemberRight)) );
}
