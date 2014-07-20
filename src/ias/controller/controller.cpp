/**
 * A class which describes the abstract properties and actions of
 * a controller.
 *
 * @date                    Jul 3, 2014
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
#include <utility>

// Application dependencies.
#include <ias/controller/controller.h>

// END Includes. /////////////////////////////////////////////////////

inline void Controller::initialize( void ) {
    mId = 0;
    mSocket = nullptr;
}

void Controller::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

void Controller::setDevices( const std::vector<Device *> & devices ) {
    mDevices = devices;
    for( auto it = mDevices.begin() ;  it != mDevices.end() ; ++it ) {
        (*it)->setController(this);
    }
}

Controller::Controller( const std::size_t id,
                        const std::string & identifier,
                        const std::string & name,
                        const std::string & description,
                        const std::string & securityCode,
                        const std::vector<Device *> & devices ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setSecurityCode(securityCode);
    setDevices(devices);
}

Controller::~Controller( void ) {
    // Nothing to do here.
}

std::size_t Controller::getId( void ) const {
    return ( mId );
}

const std::string & Controller::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Controller::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );
    
    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Controller::getName( void ) const {
    return ( mName );
}

void Controller::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );
    
    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Controller::getDescription( void ) const {
    return ( mDescription );
}

bool Controller::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Controller::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

bool Controller::matchesSecurityCode( const std::string & code ) const {
    return ( mSecurityCode == code );
}

void Controller::setSecurityCode( const std::string & code ) {
    mMutexSecurityCode.lock();
    mSecurityCode = code;
    mMutexSecurityCode.unlock();
}

bool Controller::isConnected( void ) const {
    return ( mSocket != nullptr && mSocket->isConnected() );
}

void Controller::setConnected( Socket * socket ) {
    mSocket = socket;
}

Socket * Controller::getSocket( void ) const {
    return ( mSocket );
}

std::size_t Controller::numDevices( void ) const {
    std::size_t n;
    
    mMutexDevices.lock();
    n = mDevices.size();
    mMutexDevices.unlock();
    
    return ( n );
}

void Controller::addDevice( Device * device ) {
    // Checking the precondition.
    assert( device != nullptr );
    
    if( !containsDevice(device) ) {
        mMutexDevices.lock();
        mDevices.push_back(device);
        device->setController(this);
        mMutexDevices.unlock();
    }
}

bool Controller::containsDevice( const Device * device ) const {
    bool contains;
    
    contains = ( std::find(mDevices.begin(),mDevices.end(),device) != 
                 mDevices.end() );
    
    return ( contains );
}

Device * Controller::getDevice( const std::size_t id ) const {
    Device * device;
    
    device = nullptr;
    for( auto it = mDevices.begin() ; it != mDevices.end() ; ++it ) {
        if( (*it)->getId() == id ) {
            device = (*it);
            break;
        }
    }
    
    return ( device );
}

Device * Controller::getDevice( const std::string & identifier ) const {
    Device * device;
    
    device = nullptr;
    for( auto it = mDevices.begin() ; it != mDevices.end() ; ++it ) {
        if( (*it)->getIdentifier() == identifier ) {
            device = (*it);
            break;
        }
    }
    
    return ( device );
}
