/**
 * A class which describes the properties and actions of an device
 * update event.
 *
 * @date                    14 January, 2015
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

#ifndef DEVICE_UPDATE_EVENT_H_
#define DEVICE_UPDATE_EVENT_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/event/event.h>

// END Includes. /////////////////////////////////////////////////////

class DeviceUpdateEvent : public Event {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    static const char kIdentifier[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A string which represents the state identifier which has been
     * updated.
     *
     * @note    By default, this member will be equal to the empty string.
     */
    std::string mStateIdentifier;

    /**
     * A string which represents the new state value.
     *
     * @note    By default, this member will be equal to the empty string.
     */
    std::string mStateValue;

    /**
     * Contains a pointer to the device which sent the update.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    const Device * mDevice;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setStateIdentifier( const std::string & identifier );

    void setStateValue( const std::string & value );

    void setDevice( const Device * device );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    DeviceUpdateEvent( const Device * device,
                       const std::string & identifier,
                       const std::string & value );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~DeviceUpdateEvent( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::string toString( void ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_UPDATE_EVENT_H_ */
