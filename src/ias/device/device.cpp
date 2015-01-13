/**
 * A class which described the properties and actions of a device.
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
#include <cstring>
#include <iostream>
#include <ctime>

// Application dependencies.
#include <ias/controller/controller.h>
#include <ias/device/device.h>
#include <ias/device/struct_device_update.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void Device::initialize( void ) {
    mId = 0;
    mController = nullptr;
}

void Device::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

void Device::setUpTechnology( void ) {
    std::vector<Member *>::const_iterator it;
    Member * member;

    mState.clear();
    const std::vector<Member *> & members = mTechnology->getMembers();
    for( it = members.begin() ; it != members.end() ; ++it ) {
        member = (*it);
        mState[member->getIdentifier()] =
            std::pair<std::string,const ValueType *>(member->getDefaultValue(),
                                                     member->getValueType());
    }
}

bool Device::controllerConnected( void ) const {
    return ( mController != nullptr && mController->isConnected() );
}

Device::Device( const std::size_t id,
                const std::string & identifier,
                const std::string & name,
                const std::string & description,
                const Technology * technology ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    setTechnology(technology);
}

Device::~Device( void ) {
    // Nothing to do here.
}

std::size_t Device::getId( void ) const {
    return ( mId );
}

const std::string & Device::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Device::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() && identifier.length() <= 255 );

    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Device::getName( void ) const {
    return ( mName );
}

void Device::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );

    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Device::getDescription( void ) const {
    return ( mDescription );
}

bool Device::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Device::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

std::size_t Device::set( const std::string & key , const std::string & value ) {
    std::map<std::string,std::pair<std::string,const ValueType *>>::iterator it;
    struct device_update dUpdate;
    const ValueType * type;
    std::size_t result;

    // Checking the preconditions.
    assert( !key.empty() && !value.empty() );

    result = 1;
    mMutexTechnology.lock();
    it = mState.find(key);
    if( it != mState.end() ) {
        type = it->second.second;
        result = 2;
        if( type->matches(value) ) {
            logi("Updating state of " + mIdentifier + " => " + key + " = " + value);
            mState[key] = std::pair<std::string,const ValueType *>(value,type);
            dUpdate.mDevice = this;
            dUpdate.mStateIdentifier = key;
            dUpdate.mValue = value;
            dUpdate.mTimestamp = std::time(nullptr);
            result = 0;
        }
    }
    mMutexTechnology.unlock();
    if( result == 0 )
        notifyObservers(static_cast<void *>(&dUpdate));

    return ( result );
}

std::string Device::get( const std::string & key ) const {
    std::string result;

    mMutexTechnology.lock();
    auto it = mState.find(key);
    if( it != mState.end() )
        result = it->second.first;
    mMutexTechnology.unlock();

    return ( result );
}

void Device::setTechnology( const Technology * technology ) {
    // Checking the precondition.
    assert( technology != nullptr );

    mMutexTechnology.lock();
    mTechnology = technology;
    setUpTechnology();
    mMutexTechnology.unlock();
}

const Technology * Device::getTechnology( void ) const {
    return ( mTechnology );
}

void Device::setController( const Controller * controller ) {
    // Checking the precondition.
    assert( controller != nullptr );

    mMutexController.lock();
    mController = controller;
    mMutexController.unlock();
}

const Controller * Device::getController( void ) const {
    return ( mController );
}

void Device::execute( const Action & action ) {
    std::uint8_t header[4];
    std::size_t nBytes;
    Writer * writer;

    if( mTechnology->containsFeature(action.getIdentifier()) &&
        controllerConnected() ) {
        writer = mController->getSocket()->getWriter();
        const std::string & identifier = action.getIdentifier();
        const std::string & param = action.getParameter();
        header[0] = 0x01;
        header[1] = static_cast<std::uint8_t>(mIdentifier.length());
        header[2] = static_cast<std::uint8_t>(identifier.length());
        header[3] = static_cast<std::uint8_t>(param.length());
        nBytes = header[1] + header[2] + header[3];
        writer->lock();
        writer->writeBytes(reinterpret_cast<const char *>(&header),4);
        char buffer[nBytes];
        memcpy(buffer,mIdentifier.c_str(),header[1]);
        memcpy(buffer + header[1],identifier.c_str(),header[2]);
        memcpy(buffer + header[1] + header[2],param.c_str(),header[3]);
        writer->writeBytes(buffer,nBytes);
        writer->unlock();
    }
}
