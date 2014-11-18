/**
 * A class which describes the properties and actions of an action. An actions
 * is defined as an entity which will trigger a specific feature of a device
 * with a (optional) parameter.
 *
 * @date                    Jul 20, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
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

#ifndef ACTION_H_
#define ACTION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// END Includes. /////////////////////////////////////////////////////

class Action {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the feature identifier of the action.
     */
    std::string mIdentifier;

    /**
     * Contains the parameter of the action.
     */
    std::string mParameter;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setIdentifier( const std::string & identifier );

    void setParameter( const std::string & parameter );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    Action( const std::string & identifier );

    Action( const std::string & identifier,
            const std::string & parameter );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Action( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    /**
     * Returns the unique identifier of the device which is associated with
     * the action.
     *
     * @return  The device identifier.
     */
    const std::string & getIdentifier( void ) const;

    /**
     * Checks if the action has a parameter.
     *
     * @return  True, if the parameter field isn't the empty string. False in
     *          any other case.
     */
    bool containsParameter( void ) const;

    /**
     * Returns the parameter of the action.
     *
     * @return  The action parameter.
     */
    const std::string & getParameter( void ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* ACTION_H_ */
