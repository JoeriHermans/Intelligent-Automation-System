/**
 * A class represents a persitent set of properties. A property contains a
 * key-value relation.
 *
 * @date					Jun 3, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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
#include <iostream>

// Application dependencies.
#include <ias/util/properties.h>

// END Includes. /////////////////////////////////////////////////////

Properties::Properties( void ) {
    // Nothing to do here.
}

Properties::~Properties( void ) {
    clear();
}

void Properties::add( const std::string & key , const std::string & value ) {
    mProperties[key] = value;
}

bool Properties::contains( const std::string & key ) const {
    std::map<std::string,std::string>::const_iterator it;
    bool contains;
    
    it = mProperties.find(key);
    contains = ( it != mProperties.end() );
    
    return ( contains );
}

const std::string & Properties::get( const std::string & key ) const {
    std::map<std::string,std::string>::const_iterator it;
    
    // Checking the precondition.
    assert( contains(key) );
    
    it = mProperties.find(key);
    
    return ( it->second );
}

void Properties::clear( void ) {
    mProperties.clear();
}
