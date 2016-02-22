/**
 * A class which describes the properties of a technology member.
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
#include <string>
#include <iostream>

// Application dependencies.
#include <ias/technology/member.h>

// END Includes. /////////////////////////////////////////////////////

inline void Member::initialize( void ) {
    mId = 0;
    mValueType = nullptr;
}

void Member::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

Member::Member( const std::size_t id,
                const std::string & identifier,
                const std::string & name,
                const std::string & description,
                const std::string & defaultValue,
                const ValueType * valueType ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setDefaultValue(defaultValue);
    setValueType(valueType);
}

Member::~Member( void ) {
    // Nothing to do here.
}

std::size_t Member::getId( void ) const {
    return ( mId );
}

const std::string & Member::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Member::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Member::getName( void ) const {
    return ( mName );
}

void Member::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Member::getDescription( void ) const {
    return ( mDescription );
}

bool Member::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Member::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

void Member::setDefaultValue( const std::string & defaultValue ) {
    // Checking the precondition.
    assert( !defaultValue.empty() );
    
    mMutexDefaultValue.lock();
    mDefaultValue = defaultValue;
    mMutexDefaultValue.unlock();
}

const std::string & Member::getDefaultValue( void ) const {
    return ( mDefaultValue );
}

void Member::setValueType( const ValueType * valueType ) {
    // Checking the precondition.
    assert( valueType != nullptr );
    
    mMutexValueType.lock();
    mValueType = valueType;
    mMutexValueType.unlock();
}

const ValueType * Member::getValueType( void ) const {
    return ( mValueType );
}
