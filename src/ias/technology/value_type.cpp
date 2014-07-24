/**
 * A class which describes the actions and properties of a value type.
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

inline void ValueType::initialize( void ) {
    mId = 0;
}

void ValueType::compilePattern( const std::string & pattern ) {
    mPattern = std::regex(pattern,std::regex_constants::extended);
}

void ValueType::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

ValueType::ValueType( const std::size_t id,
                      const std::string & identifier,
                      const std::string & name,
                      const std::string & description,
                      const std::string & pattern ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    compilePattern(pattern);
}

ValueType::~ValueType( void ) {
    // Nothing to do here.
}

std::size_t ValueType::getId( void ) const {
    return ( mId );
}

const std::string & ValueType::getIdentifier( void ) const {
    return ( mIdentifier );
}

void ValueType::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & ValueType::getName( void ) const {
    return ( mName );
}

void ValueType::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & ValueType::getDescription( void ) const {
    return ( mDescription );
}

bool ValueType::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void ValueType::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

bool ValueType::matches( const std::string & toMatch ) const {
    return ( std::regex_match(toMatch,mPattern) );
}
