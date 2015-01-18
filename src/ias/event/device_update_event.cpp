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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/event/device_update_event.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char DeviceUpdateEvent::kIdentifier[] = "device_update";

// END Constants. ////////////////////////////////////////////////////

void DeviceUpdateEvent::setStateIdentifier( const std::string & identifier ) {
    // Checking the precondition.
    assert( !identifier.empty() );

    mStateIdentifier = identifier;
}

void DeviceUpdateEvent::setStateValue( const std::string & value ) {
    // Checking the precondition.
    assert( !value.empty() );

    mStateValue = value;
}

void DeviceUpdateEvent::setDevice( const Device * device ) {
    // Checking the precondition.
    assert( device != nullptr );

    mDevice = device;
}

DeviceUpdateEvent::DeviceUpdateEvent( const Device * device,
                                      const std::string & identifier,
                                      const std::string & value ) {
    setDevice(device);
    setStateIdentifier(identifier);
    setStateValue(value);
}

std::string DeviceUpdateEvent::toString( void ) const {
    std::string response;

    response = "{\n";
    response += "  \"type\":\"" + std::string(kIdentifier) + "\",\n";
    response += "  \"device_id\":" + std::to_string(mDevice->getId()) + ",\n";
    response += "  \"device_identifier\":\"" + mDevice->getIdentifier() + "\",\n";
    response += "  \"state_identifier\":\"" + mStateIdentifier + "\",\n";
    response += "  \"state_value\":\"" + mStateValue + "\"\n";
    response += "}";

    return ( response );
}
