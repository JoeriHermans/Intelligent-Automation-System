/**
 * A class which describes the properties of the less than or equals operator.
 *
 * @date                    Aug 17, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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
#include <cstdlib>

// Application dependencies.
#include <ias/operator/operator_less_than_equals.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char OperatorLessThanEquals::kIdentifier[] = "<=";

// END Constants. ////////////////////////////////////////////////////

OperatorLessThanEquals::OperatorLessThanEquals( void ) :
    Operator(kIdentifier) {
    // Nothing to do here.
}

OperatorLessThanEquals::~OperatorLessThanEquals( void ) {
    // Nothing to do here.
}

bool OperatorLessThanEquals::evaluate( const std::string & leftExpression,
                                       const std::string & rightExpression ) const {
    double left;
    double right;
    bool result;

    left = strtod(leftExpression.c_str(),nullptr);
    right = strtod(rightExpression.c_str(),nullptr);
    if( left == 0 && right == 0 )
        result = (leftExpression <= rightExpression);
    else
        result = (left <= right);

    return ( result );
}
