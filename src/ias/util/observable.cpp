/**
 * A class which describes the properties and actions of an observable
 * instance.
 *
 * @date                    Jul 2, 2014
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
#include <algorithm>
#include <cassert>

// Application dependencies.
#include <ias/util/observable.h>

// END Includes. /////////////////////////////////////////////////////

Observable::Observable( void ) {
    // Nothing to do here.
}

Observable::~Observable( void ) {
    // Nothing to do here.
}

bool Observable::containsObserver( const Observer * observer ) const {
    bool contains;
    
    contains = ( std::find(mObservers.begin(),mObservers.end(),observer) != 
                 mObservers.end() );
    
    return ( contains );
}

void Observable::addObserver( Observer * observer ) {
    // Checking the precondition.
    assert( observer != nullptr );
    if( !containsObserver(observer) )
        mObservers.push_back(observer);
}

void Observable::removeObservers( void ) {
    mObservers.clear();
}

void Observable::notifyObservers( void ) {
    std::vector<Observer *>::const_iterator it;
    
    for( it = mObservers.begin() ; it != mObservers.end() ; ++it ) {
        (*it)->update();
    }
}

void Observable::notifyObservers( void * argument ) {
    std::vector<Observer *>::const_iterator it;
    
    // Checking the precondition.
    assert( argument != nullptr );
    
    for( it = mObservers.begin() ; it != mObservers.end() ; ++it ) {
        (*it)->update(argument);
    }
}
