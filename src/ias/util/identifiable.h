/**
 * An interface which describes the actions of an identifiable object.
 *
 * @date                    Jul 3, 2014
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

#ifndef IDENTIFIABLE_H_
#define IDENTIFIABLE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// END Includes. /////////////////////////////////////////////////////

class Identifiable {

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

    Identifiable( void ){}

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Identifiable( void ){}

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    /**
     * Returns the unique id of the controller.
     *
     * @return  The unique id of the controller.
     */
    virtual std::size_t getId( void ) const = 0;

    /**
     * Returns the unique human-readable identifier of the controller.
     *
     * @return  The human-readable identifier of the controller.
     */
    virtual const std::string & getIdentifier( void ) const = 0;

    /**
     * Sets the unique human-readable identifier of the controller.
     *
     * @pre     The specified parameter cannot be empty.
     * @param   identifier
     *          The new unique human-readable identifier of the controller.
     * @post    The new human-readable identifier will be equal to the
     *          contents of the specified parameter if and only if all
     *          preconditions are met.
     */
    virtual void setIdentifier( const std::string & identifier ) = 0;

    /**
     * Returns the name of the controller.
     *
     * @return  The name.
     */
    virtual const std::string & getName( void ) const = 0;

    /**
     * Sets the name of the controller.
     *
     * @pre     The specified name cannot be empty.
     * @param   name
     *          The new name of the controller.
     * @post    The specified name will be equal to the contents of the
     *          specified parameter if and only if the preconditions are met.
     */
    virtual void setName( const std::string & name ) = 0;

    /**
     * Returns the description of the controller.
     *
     * @return  The description of the controller.
     */
    virtual const std::string & getDescription( void ) const = 0;

    /**
     * Checks if the controllers has a description.
     *
     * @return  True, if getDescription() doesn't return an empty string. False,
     *          in any other case.
     */
    virtual bool hasDescription( void ) const = 0;

    /**
     * Sets the description of the controller.
     *
     * @param   description
     *          The new description of the controller.
     * @post    The new description of the controller will be equal to the
     *          contents of the specified parameter.
     */
    virtual void setDescription( const std::string & description ) = 0;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* IDENTIFIABLE_H_ */
