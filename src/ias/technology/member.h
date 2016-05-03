/**
 * A class which describes the properties of a technology member. A
 * member basically describes a property (state), with a default
 * value and type.
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

// Application dependencies.
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MEMBER_H_
#define IAS_MEMBER_H_

namespace ias {

class member {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique identifier of the member.
     */
    std::size_t mId;

    /**
     * Holds the string identifier of the member.
     */
    std::string mIdentifier;

    /**
     * Holds the default value of the member.
     */
    std::string mDefaultValue;

    /**
     * Holds the value type of the member.
     */
    const ias::value_type * mValueType;

    /**
     * Mutexes for synchronization.
     */
    std::mutex mMutexIdentifier;
    std::mutex mMutexDefaultValue;
    std::mutex mMutexValueType;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_id(const std::size_t id);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    member(const std::size_t id, const std::string & identifier,
           const std::string & defaultValue, const ias::value_type * type);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~member(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    const std::size_t get_id(void) const;

    const std::string & get_identifier(void) const;

    void set_identifier(const std::string & identifier);

    const std::string & get_default_value(void) const;

    void set_default_value(const std::string & defaultValue);

    void set_value_type(const ias::value_type * type);

    const ias::value_type * get_value_type(void) const;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
