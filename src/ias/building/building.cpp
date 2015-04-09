/**
 * A class which describes the properties and actions of a building. A building
 * contains interconnected areas, which describe the layout of a building.
 *
 * @date                    28 February, 2015
 * @author                  Joeri HERMANS
 * @version                 0.2
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
#include <algorithm>

// Application dependencies.
#include <ias/building/building.h>

// END Includes. /////////////////////////////////////////////////////

inline void Building::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

Building::Building( const std::size_t id,
                    const std::string & identifier,
                    const std::string & name ) {
    setId(id);
    setIdentifier(identifier);
    setName(name);
}

Building::Building( const std::size_t id,
                    const std::string & identifier,
                    const std::string & name,
                    const std::string & description ) {
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
}

std::size_t Building::getId( void ) const {
    return ( mId );
}

const std::string & Building::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Building::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );

    mIdentifier = identifier;
}

const std::string & Building::getName( void ) const {
    return ( mName );
}

void Building::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );

    mName = name;
}

const std::string & Building::getDescription( void ) const {
    return ( mDescription );
}

bool Building::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Building::setDescription( const std::string & description ) {
    mDescription = description;
}

void Building::addArea( Area * area ) {
    // Checking the precondition.
    assert( area != nullptr );

    mMutexArea.lock();
    mAreas.push_back(area);
    mMutexArea.unlock();
}

bool Building::containsArea( const Area * area ) const {
    bool contains;

    // Checking the precondition.
    assert( area != nullptr );

    mMutexArea.lock();
    auto it = std::find(mAreas.begin(),mAreas.end(),area);
    if( it != mAreas.end() )
        contains = true;
    else
        contains = false;
    mMutexArea.unlock();

    return ( contains );
}

void Building::removeArea( const Area * area ) {
    // Checking the precondition.
    assert( area != nullptr );

    mMutexArea.lock();
    auto it = std::find(mAreas.begin(),mAreas.end(),area);
    if( it != mAreas.end() )
        mAreas.erase(it);
    mMutexArea.unlock();
}
