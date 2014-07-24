/**
 * A class which describes the properties and actions of an area.
 *
 * @date                    Jul 24, 2014
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
#include <ias/building/area.h>

// END Includes. /////////////////////////////////////////////////////

inline void Area::initialize( void ) {
    // Nothing to do here.
}

void Area::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

void Area::setDevices( const std::vector<Device *> & devices ) {
    for( auto d : devices )
        mDevices[d->getIdentifier()] = d;
}

void Area::setAdjacentAreas( const std::vector<Area *> & areas ) {
    for( auto a : areas )
        mAreas[a->getIdentifier()] = a;
}

Area::Area( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
}

Area::Area( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description,
            const std::vector<Device *> & devices ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setDevices(devices);
}

Area::Area( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description,
            const std::vector<Device *> & devices,
            const std::vector<Area *> & areas ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setDevices(devices);
    setAdjacentAreas(areas);
}

Area::~Area( void ) {
    // Nothing to do here.
}

std::size_t Area::getId( void ) const {
    return ( mId );
}

const std::string & Area::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Area::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( identifier.length() > 0 );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Area::getName( void ) const {
    return ( mName );
}

void Area::setName( const std::string & name ) {
    // Checking the precondition.
    assert( name.length() > 0 );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Area::getDescription( void ) const {
    return ( mDescription );
}

bool Area::hasDescription( void ) const {
    return ( mDescription.length() > 0 );
}

void Area::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

bool Area::containsDevice( const std::string & identifier ) const {
    auto it = mDevices.find(identifier);
    
    return ( it != mDevices.end() );
}

bool Area::containsDevice( const std::size_t id ) const {
    bool contains;
    
    contains = false;
    mMutexDevices.lock();
    for( auto it = mDevices.begin() ; it != mDevices.end() ; ++it ) {
        if( it->second->getId() == id ) {
            contains = true;
            break;
        }
    }
    mMutexDevices.unlock();
    
    return ( contains );
}

Device * Area::getDevice( const std::string & identifier ) const {
    Device * device;
    
    mMutexDevices.lock();
    auto it = mDevices.find(identifier);
    if( it != mDevices.end() )
        device = it->second;
    else
        device = nullptr;
    mMutexDevices.unlock();
    
    return ( device );
}

Device * Area::getDevice( const std::size_t id ) const {
    Device * device;
    
    mMutexDevices.lock();
    device = nullptr;
    for( auto it = mDevices.begin() ; it != mDevices.end() ; ++it ) {
        if( it->second->getId() == id ) {
            device = it->second;
            break;
        }
    }
    mMutexDevices.unlock();
    
    return ( device );
}

void Area::removeDevice( const Device * device ) {
    // Checking the precondition.
    assert( device != nullptr );
    
    mMutexDevices.lock();
    mDevices.erase(device->getIdentifier());
    mMutexDevices.unlock();
}

std::vector<Device *> Area::getDevices( void ) const {
    std::vector<Device *> devices;
    
    mMutexDevices.lock();
    for( auto it = mDevices.begin() ; it != mDevices.end() ; ++it ) {
        devices.push_back(it->second);
    }
    mMutexDevices.unlock();
    
    return ( devices );
}

std::size_t Area::numDevices( void ) const {
    std::size_t n;
    
    mMutexDevices.lock();
    n = mDevices.size();
    mMutexDevices.unlock();
    
    return ( n );
}
