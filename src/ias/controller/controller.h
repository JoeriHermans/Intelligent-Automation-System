/**
 * A class which describes the abstract properties and actions
 * of a controller. These are the devices which actually drive the
 * devices they are connected to.
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
#include <vector>
#include <string>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/device/device.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CONTROLLER_H_
#define IAS_CONTROLLER_H_

namespace ias {

class controller {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique identifier of the controller.
     */
    std::size_t mId;

    /**
     * Holds the unique string identifier of the controller.
     */
    std::string mIdentifier;

    /**
     * Holds the hashed security code of the controller.
     */
    std::string mHashedSecurityCode;

    /**
     * Holds the socket which is associated with the controller connection.
     *
     * @note If this element is not equal to the null reference, then there
     *       is a connection with this controller available.
     */
    ias::socket * mSocket;

    /**
     * Sets of all devices which are associated with this controller.
     */
    std::vector<ias::device *> mDevices;

    /**
     * Mutexes which are used for data synchronization.
     */
    std::mutex mMutexIdentifier;
    std::mutex mMutexSecurityCode;
    std::mutex mMutexSocket;
    std::mutex mMutexDevices;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_id(const std::size_t id);

    void set_devices(const std::vector<ias::device *> & devices);f

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    controller(const std::size_t id,
               const std::string & identifier,
               const std::string & securityCode,
               const std::vector<ias::device *> & devices);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~controller(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////
    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
