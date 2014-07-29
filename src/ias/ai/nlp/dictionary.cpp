/**
 * A class which describes the properties and actions of a dictionary. A
 * dictionary is responsible for storing a large set of words and the associated
 * indices.
 *
 * @date                    Jul 28, 2014
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
#include <ias/ai/nlp/dictionary.h>

// END Includes. /////////////////////////////////////////////////////

inline void Dictionary::initialize( void ) {
    mNextIndex = 0;
    mLock = false;
}

Dictionary::Dictionary( void ) {
    initialize();
}

Dictionary::~Dictionary( void ) {
    // Nothing to do here.
}

void Dictionary::add( const std::string & word ) {
    if( !mLock ) {
        mMutexStorage.lock();
        mWords[word] = mNextIndex;
        ++mNextIndex;
        mMutexStorage.unlock();
    }
}

bool Dictionary::contains( const std::string & word ) const {
    auto it = mWords.find(word);
    
    return ( it != mWords.end() );
}

void Dictionary::lock( void ) {
    mLock = true;
}

void Dictionary::unlock( void ) {
    mLock = false;
}

bool Dictionary::locked( void ) const {
    return ( mLock );
}

std::size_t Dictionary::index( const std::string & word ) const {
    std::size_t index;

    mMutexStorage.lock();
    auto it = mWords.find(word);
    if( it != mWords.end() )
        index = it->second;
    else
        index = mNextIndex;
    mMutexStorage.unlock();

    return ( index );
}

std::size_t Dictionary::size( void ) const {
    return ( mWords.size() );
}
