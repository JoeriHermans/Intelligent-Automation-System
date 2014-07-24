/**
 * A class which describes the properties of a feature.
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
#include <ias/technology/feature.h>

// END Includes. /////////////////////////////////////////////////////

inline void Feature::initialize( void ) {
    mId = 0;
    mParameterType = nullptr;
}

void Feature::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

Feature::Feature( const std::size_t id,
                  const std::string & identifier,
                  const std::string & name,
                  const std::string & description,
                  const ValueType * parameterType ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
}

Feature::~Feature( void ) {
    // Nothing to do here.
}

std::size_t Feature::getId( void ) const {
    return ( mId );
}

const std::string & Feature::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Feature::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Feature::getName( void ) const {
    return ( mName );
}

void Feature::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Feature::getDescription( void ) const {
    return ( mDescription );
}

bool Feature::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Feature::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

bool Feature::requiresParameter( void ) const {
    return ( mParameterType != nullptr );
}

const ValueType * Feature::getParameterType( void ) const {
    return ( mParameterType );
}

void Feature::setParameterType( const ValueType * parameterType ) {
    mMutexParameterType.lock();
    mParameterType = parameterType;
    mMutexParameterType.unlock();
}
