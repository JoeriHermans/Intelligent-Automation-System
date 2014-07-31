/**
 * A structure which is passed to a device monitor when a device is updated.
 *
 * @date                    Jul 31, 2014
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

#ifndef STRUCT_DEVICE_UPDATE_H_
#define STRUCT_DEVICE_UPDATE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/device/device.h>

// END Includes. /////////////////////////////////////////////////////

struct device_update {

    Device * mDevice;
    
    std::string mStateIdentifier;
    
    std::string mValue;

};

#endif /* STRUCT_DEVICE_UPDATE_H_ */
