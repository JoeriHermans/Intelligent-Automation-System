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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/device/action/action.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

void Action::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( identifier.length() > 0 );
    
    mIdentifier = identifier;
    trim(mIdentifier);
}

void Action::setParameter( const std::string & parameter ) {
    mParameter = parameter;
    trim(mParameter);
}

Action::Action( const std::string & identifier ) {
    setIdentifier(identifier);
}

Action::Action( const std::string & identifier,
                const std::string & parameter ) {
    setIdentifier(identifier);
    setParameter(parameter);
}

Action::~Action( void ) {
    // Nothing to do here.
}

const std::string & Action::getIdentifier( void ) const {
    return ( mIdentifier );
}

bool Action::containsParameter( void ) const {
    return ( mParameter.length() > 0 );
}

const std::string & Action::getParameter( void ) const {
    return ( mParameter );
}
