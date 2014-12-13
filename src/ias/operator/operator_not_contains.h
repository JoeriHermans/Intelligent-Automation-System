/**
 * A class which describes the properties and actions of an operator which
 * is responsible for checking if the left expression is not in the right
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

#ifndef OPERATOR_NOT_CONTAINS_H_
#define OPERATOR_NOT_CONTAINS_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/operator/operator.h>

// END Includes. /////////////////////////////////////////////////////

class OperatorNotContains : public Operator {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Contains the unique identifier of the not contains operator.
     */
    static const char kIdentifier[];

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

    OperatorNotContains( void );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~OperatorNotContains( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual bool evaluate( const std::string & leftExpression,
                           const std::string & rightExpression ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* OPERATOR_NOT_CONTAINS_H_ */
