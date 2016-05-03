/**
 * A class which describes the properties and actions of a device.
 * A device is an abstraction of a physical device, and is mostly
 * intended the process the state and trigger events on state
 * changes.
 *
 * @date                    03 05 2016
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
#include <mutex>
#include <string>
#include <map>
#include <utility>

// Application dependencies.
#include <ias/technology/technology.h>
#include <ias/util/observable.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_DEVICE_H_
#define IAS_DEVICE_H_

namespace ias {

class device {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique identifier of a device.
     */
    std::size_t mId;

    /**
     * Holds the unique, human-readable, string identifier of a device.
     */
    std::string mIdentifier;

    /**
     * Holds the technology which this device implements.
     */
    const ias::technology * mTechnology;

    /**
     * Holds the controller which is associated with this device.
     */
    const ias::controller * mController;

    /**
     * Mutexes used for data member synchronization.
     */
    std::mutex mMutexIdentifier;
    std::mutex mMutexTechnology;
    std::mutex mMutexController;
    std::mutex mMutexState;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    device(void);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~device(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////
    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
