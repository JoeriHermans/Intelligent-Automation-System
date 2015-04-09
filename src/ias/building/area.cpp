/**
 * A class which describes the properties and actions of an area. An area is a
 * representation of a certain room or a collection of rooms, e.g., a living
 * room. An area has a set of associated devices.
 *
 * @date                    1 March, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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
#include <algorithm>

// Application dependencies.
#include <ias/building/area.h>

// END Includes. /////////////////////////////////////////////////////

void Area::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

Area::Area( const std::size_t id,
            const std::string & identifier,
            const std::string & name ) {
    setId(id);
    setIdentifier(identifier);
    setName(name);
}

Area::Area( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description ) {
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
}

Area::~Area( void ) {
    // For all adjacent area's, remove the connection to this area.
    for( auto it = mAdjacentAreas.begin() ; it != mAdjacentAreas.end() ; ++it )
        (*it)->removeAdjacentArea(this);
}

std::size_t Area::getId( void ) const {
    return ( mId );
}

const std::string & Area::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Area::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );

    mIdentifier = identifier;
}

const std::string & Area::getName( void ) const {
    return ( mName );
}

void Area::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );

    mName = name;
}

const std::string & Area::getDescription( void ) const {
    return ( mDescription );
}

bool Area::hasDescription( void ) const {
    return ( !mDescription.empty() );
}

void Area::setDescription( const std::string & description ) {
    mDescription = description;
}

std::size_t Area::numAdjacentAreas( void ) const {
    return ( mAdjacentAreas.size() );
}

bool Area::isAdjacent( const Area * area ) const {
    bool adjacent;

    // Checking the precondition.
    assert( area != nullptr );

    adjacent = (std::find(mAdjacentAreas.begin(),mAdjacentAreas.end(),area)
        != mAdjacentAreas.end());

    return ( adjacent );
}

Area * Area::getAdjacentArea( const std::size_t index ) const {
    Area * area;

    // Checking the precondition.
    assert( index > 0 );

    area = mAdjacentAreas.at(index);

    return ( area );
}

void Area::removeAdjacentArea( const Area * area ) {
    // Checking the precondition.
    assert( area != nullptr );

    auto it = std::find(mAdjacentAreas.begin(),mAdjacentAreas.end(),area);
    if( it != mAdjacentAreas.end() )
        mAdjacentAreas.erase(it);
}

void Area::connectArea( Area * area ) {
    // Checking the precondition.
    assert( area != nullptr );

    if( !isAdjacent(area) )
        mAdjacentAreas.push_back(area);
}

void Area::connectAreaBidirectionally( Area * area ) {
    // Checking the precondition.
    assert( area != nullptr );

    connectArea(area);
    area->connectArea(this);
}
