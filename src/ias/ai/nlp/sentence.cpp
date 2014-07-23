/**
 * A class which describes the properties and actions of a sentence.
 *
 * @date					Jul 23, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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
#include <algorithm>
#include <cassert>
#include <sstream>
#include <iostream>

// Application dependencies.
#include <ias/ai/nlp/sentence.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

void Sentence::addEntity( const std::string & entity ) {
    // Checking the precondition.
    assert( entity.length() > 0 );
    
    mEntities.push_back(entity);
}

void Sentence::parse( const std::string & sentence ) {
    std::istringstream iss(sentence);
    std::string x;
    std::size_t n;
    
    // Checking the precondition.
    assert( sentence.length() > 0 );
    
    while( iss >> x ) {
        std::string cleaned;
        
        n = x.length();
        for( std::size_t i = 0 ; i < n ; ++i ) {
            if( std::ispunct(x[i]) ) {
                addEntity(cleaned);
                cleaned.clear();
                cleaned += x[i];
                break;
            }
            cleaned += x[i];
        }
        if( cleaned.length() > 0 ) {
            addEntity(cleaned);
        }
    }
}

Sentence::Sentence( const std::string & sentence ) {
    parse(sentence);
}

Sentence::~Sentence( void ) {
    // Nothing to do here.
}

std::size_t Sentence::numEntities( void ) const {
    return ( mEntities.size() );
}

const std::string & Sentence::getEntity( const std::size_t index ) const {
    return ( mEntities.at(index) );
}

bool Sentence::isWord( const std::size_t index ) const {
    return ( !std::ispunct(mEntities.at(index)[0]) );
}

bool Sentence::isQuestion( void ) const {
    return ( mEntities.back() == "?" );
}
