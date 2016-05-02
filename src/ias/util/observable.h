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
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/util/observer.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_OBSERVABLE_H_
#define IAS_OBSERVABLE_H_

namespace ias {

class observable {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Vector which holds all observers subscribed to this observer.
     */
    std::vector<ias::observer *> mObservers;

    /**
     * Mutex for synchronizing the observers.
     */
    mutable std::mutex mMutexObservers;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    observable(void) = default;

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~observable(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    bool contains_observer(const ias::observer * observer) const;

    void add_observer(ias::observer * observer);

    void remove_observers(void);

    void remove_observer(const ias::observer * observer);

    void notify_observers(void);

    void notify_observers(void * argument);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
