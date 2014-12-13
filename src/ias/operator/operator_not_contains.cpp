/**
 * A class which describes the properties and actions of an operator which
 * is responsible for checking if the right expression is not in the left
 * expression. In other words, it checks whether or not if the left expression
 * is a substring of the right expression.
 *
 * @date                    December 12, 2014
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

// Application dependencies.
#include <ias/operator/operator_not_contains.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char OperatorNotContains::kIdentifier[] = "nin";

// END Constants. ////////////////////////////////////////////////////

OperatorNotContains::OperatorNotContains( void ) :
    Operator(kIdentifier) {
    // Nothing to do here.
}

bool OperatorNotContains::evaluate( const std::string & leftExpression,
                                    const std::string & rightExpression ) const {
    return ( leftExpression.find(rightExpression) == std::string::npos );
}
