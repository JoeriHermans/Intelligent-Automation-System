/**
 * A class which describes the properties and actions of a building.
 *
 * @date                    Jul 24, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
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
#include <ias/building/building.h>

// END Includes. /////////////////////////////////////////////////////

inline void Building::initialize( void ) {
    // Nothing to do here.
}

void Building::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

void Building::setAreas( const std::vector<Area *> & areas ) {
    mAreas = areas;
}

Building::Building( const std::size_t id,
                    const std::string & identifier,
                    const std::string & name,
                    const std::string & description,
                    const std::vector<Area *> & areas ) {
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setAreas(areas);
}

Building::~Building( void ) {
    // Nothing to do here.
}

std::size_t Building::getId( void ) const {
    return ( mId );
}

const std::string & Building::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Building::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( identifier.length() > 0 );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Building::getName( void ) const {
    return ( mName );
}

void Building::setName( const std::string & name ) {
    // Checking the precondition.
    assert( name.length() > 0 );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Building::getDescription( void ) const {
    return ( mDescription );
}

bool Building::hasDescription( void ) const {
    return ( mDescription.length() > 0 );
}

void Building::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

std::size_t Building::numAreas( void ) const {
    return ( mAreas.size() );
}

const std::vector<Area *> & Building::getAreas( void ) const {
    return ( mAreas );
}
