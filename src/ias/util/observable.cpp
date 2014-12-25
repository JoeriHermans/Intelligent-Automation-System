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

    mMutexObservers.lock();
    contains = ( std::find(mObservers.begin(),mObservers.end(),observer) !=
                 mObservers.end() );
    mMutexObservers.unlock();

    return ( contains );
}

void Observable::removeObserver( const Observer * observer ) {
    Observer * current;

    mMutexObservers.lock();
    for( auto it = mObservers.begin() ; it != mObservers.end() ; ++it ) {
        current = (*it);
        if( current == observer ) {
            mObservers.erase(it);
            break;
        }
    }
	mMutexObservers.unlock();
}

void Observable::addObserver( Observer * observer ) {
    // Checking the precondition.
    assert( observer != nullptr );
    if( !containsObserver(observer) ) {
        mMutexObservers.lock();
        mObservers.push_back(observer);
        mMutexObservers.unlock();
    }
}

void Observable::removeObservers( void ) {
	mMutexObservers.lock();
    mObservers.clear();
    mMutexObservers.unlock();
}

void Observable::notifyObservers( void ) {
    std::vector<Observer *>::const_iterator it;

    mMutexObservers.lock();
    for( it = mObservers.begin() ; it != mObservers.end() ; ++it ) {
        (*it)->update();
    }
    mMutexObservers.unlock();
}

void Observable::notifyObservers( void * argument ) {
    std::vector<Observer *>::const_iterator it;

    // Checking the precondition.
    assert( argument != nullptr );

    mMutexObservers.lock();
    for( it = mObservers.begin() ; it != mObservers.end() ; ++it ) {
        (*it)->update(argument);
    }
    mMutexObservers.unlock();
}
