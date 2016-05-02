/**
 * A class which describes the actions and properties of an
 * observable object. This class is the abstract implementation of
 * the oversable in the observer-observable pattern.
 *
 * @date                    02 05 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

namespace ias {

    bool observable::contains_observer(const ias::observer * observer) const {
        bool contains;

        mMutexObservers.lock();
        contains = (std::find(mObservers.begin(), mObservers.end(),
                              observer) != mObservers.end());
        mMutexObservers.unlock();

        return contains;
    }

    void observable::remove_observer(const ias::observer * observer) {
        ias::observer * current;

        mMutexObservers.lock();
        for(auto it = mObservers.begin(); it != mObservers.end(); ++it) {
            current = (*it);
            if(current == observer) {
                mObservers.erase(it);
                break;
            }
        }
        mMutexObservers.unlock();
    }

    void observable::add_observer(ias::observer * observer) {
        // Checking the precondition.
        assert(observer != nullptr);

        if(!contains_observer(observer)) {
            mMutexObservers.lock();
            mObservers.push_back(observer);
            mMutexObservers.unlock();
        }
    }

    void observable::remove_observers(void) {
        mMutexObservers.lock();
        mObservers.clear();
        mMutexObservers.unlock();
    }

    void observable::notify_observers(void) {
        mMutexObservers.lock();
        for(auto it = mObservers.begin(); it != mObservers.end(); ++it)
            (*it)->update();
        mMutexObservers.unlock();
    }

    void observable::notify_observers(void * argument) {
        mMutexObservers.lock();
        for(auto it = mObservers.begin(); it != mObservers.end(); ++it)
            (*it)->update(argument);
        mMutexObservers.unlock();
    }

};
