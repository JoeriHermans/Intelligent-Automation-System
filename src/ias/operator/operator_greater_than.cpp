/**
 * A class which describes the properties and actions of ther greater than
 * operator.
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
#include <string>

// Application dependencies.
#include <ias/operator/operator_greater_than.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Class constants. ////////////////////////////////////////////

const char OperatorGreaterThan::kIdentifier[] = ">";

// END Class constants. //////////////////////////////////////////////

OperatorGreaterThan::OperatorGreaterThan( void ) :
    Operator(kIdentifier) {
    // Nothing to do here.
}

OperatorGreaterThan::~OperatorGreaterThan( void ) {
    // Nothing to do here.
}

bool OperatorGreaterThan::evaluate( const std::string & leftExpression,
                                    const std::string & rightExpression ) const {
    bool result;
    double left;
    double right;
    
    left = strtod(leftExpression.c_str(),nullptr);
    right = strtod(rightExpression.c_str(),nullptr);
    if( left == 0 && right == 0 ) {
        result = (leftExpression > rightExpression);
    } else {
        result = (left > right);
    }
    
    return ( result );
}
