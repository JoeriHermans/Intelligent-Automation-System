/**
 * A class which is responsible for storing words or phrases in a efficient
 * way. These vocabularies can be used for several NLP applications.
 *
 * @date                    1 April, 2015
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
#include <algorithm>
#include <cassert>

// Application dependencies.
#include <ias/ml/nlp/vocabulary.h>

// END Includes. /////////////////////////////////////////////////////

Vocabulary::Vocabulary( const std::size_t id,
                        const std::string & name ) {
    setId(id);
    setName(name);
}

void Vocabulary::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );

    mId = id;
}

std::size_t Vocabulary::getId( void ) const {
    return ( mId );
}

void Vocabulary::setName( const std::string & name ) {
    // Checking the precondition.
    assert( !name.empty() );

    mName = name;
}

const std::string & Vocabulary::getName( void ) const {
    return ( mName );
}

void Vocabulary::add( const std::string & entity ) {
    // Checking the preconditions.
    assert( !entity.empty() && !contains(entity) );

    mStorage.push_back(entity);
}

bool Vocabulary::contains( const std::string & entity ) const {
    return ( std::find(mStorage.begin(),mStorage.end(),entity)
                != mStorage.end() );
}

std::size_t Vocabulary::get( const std::string & entity ) const {
    std::vector<std::string>::const_iterator it;
    std::size_t index;

    it = std::find(mStorage.begin(),mStorage.end(),entity);
    index = std::distance(mStorage.begin(),it);

    return ( index );
}

const std::string Vocabulary::get( const std::size_t index ) const {
    return ( mStorage.at(index) );
}

std::size_t Vocabulary::size( void ) const {
    return ( mStorage.size() );
}
