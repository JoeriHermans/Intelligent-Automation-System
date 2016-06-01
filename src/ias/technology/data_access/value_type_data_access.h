/**
 * An abstract class which will provide the interface for specific
 * implementations of value type fetching.
 *
 * @date                    01 06 2016
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

// Application dependencies.
#include <ias/data_access/data_access.h>
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_VALUE_TYPE_DATA_ACCESS_H_
#define IAS_VALUE_TYPE_DATA_ACCESS_H_

namespace ias {

class value_type_data_access : public data_access<ias::value_type *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////
    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    value_type_data_access(void) = default;

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~value_type_data_access(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<ias::value_type *> get_all(void) = 0;

    virtual ias::value_type * get(const std::size_t id) = 0;

    virtual void add(ias::value_type * element) = 0;

    virtual void remove(ias::value_type * element) = 0;

    virtual void remove(const std::size_t id) = 0;

    virtual void update(ias::value_type *  element) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
