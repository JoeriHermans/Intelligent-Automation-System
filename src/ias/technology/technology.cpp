/**
 * A class which represents the properties and actions of a technology.
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
#include <ias/technology/technology.h>

// END Includes. /////////////////////////////////////////////////////

inline void Technology::initialize( void ) {
    mId = 0;
}

void Technology::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

Technology::Technology( const std::size_t id,
                        const std::string & identifier,
                        const std::string & name,
                        const std::string & description,
                        const std::vector<Member *> & members,
                        const std::vector<Feature *> & features ) {
    initialize();
    setId(id);
    setIdentifier(identifier);
    setName(name);
    setDescription(description);
    mMembers = members;
    mFeatures = features;
}

Technology::~Technology( void ) {
    // Nothing to do here.
}

std::size_t Technology::getId( void ) const {
    return ( mId );
}

const std::string & Technology::getIdentifier( void ) const {
    return ( mIdentifier );
}

void Technology::setIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );

    mMutexIdentifier.lock();
    mIdentifier = identifier;
    mMutexIdentifier.unlock();
}

const std::string & Technology::getName( void ) const {
    return ( mName );
}

void Technology::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );

    mMutexName.lock();
    mName = name;
    mMutexName.unlock();
}

const std::string & Technology::getDescription( void ) const {
    return ( mDescription );
}

bool Technology::hasDescription( void ) const {
    return ( mDescription.empty() );
}

void Technology::setDescription( const std::string & description ) {
    mMutexDescription.lock();
    mDescription = description;
    mMutexDescription.unlock();
}

const std::vector<Member *> & Technology::getMembers( void ) const {
    return ( mMembers );
}

std::size_t Technology::numMembers( void ) const {
    return ( mMembers.size() );
}

const std::vector<Feature *> & Technology::getFeatures( void ) const {
    return ( mFeatures );
}

const Feature * Technology::getFeature( const std::string & identifier ) const {
    const Feature * f;
    Feature * feature;

    f = nullptr;
    for( auto it = mFeatures.begin() ; it != mFeatures.end() ; ++it ) {
        feature = (*it);
        if( feature->getIdentifier() == identifier ) {
            f = feature;
            break;
        }
    }

    return ( f );
}

bool Technology::containsFeature( const std::string & identifier ) const {
    Feature * feature;
    bool contains;

    contains = false;
    for( auto it = mFeatures.begin() ; it != mFeatures.end() ; ++it ) {
        feature = (*it);
        if( feature->getIdentifier() == identifier ) {
            contains = true;
            break;
        }
    }

    return ( contains );
}

std::size_t Technology::numFeatures( void ) const {
    return ( mFeatures.size() );
}
