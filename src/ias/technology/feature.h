/**
 * Describes the properties of a feature. A feature is an action of
 * a technology which can be executed by the device.
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
#include <string>
#include <mutex>

// Application dependencies.
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_FEATURE_H_
#define IAS_FEATURE_H_

namespace ias {

class feature {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique identifier of the feature.
     */
    std::size_t mId;

    /**
     * Holds the string identifier of the feature.
     */
    std::string mIdentifier;

    /**
     * Holds the type of the parameter, if the this member is equal to the
     * null reference. No, parameter needs to be specified.
     */
    const ias::value_type * mParameterType;

    /**
     * Mutexes for the editing of class members.
     */
    std::mutex mMutexIdentifier;
    std::mutex mMutexParameterType;

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

    feature(const std::size_t id, const std::string & identifier,
            const ias::value_type * parameterType);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~feature(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    const std::size_t get_id(void) const;

    const std::string & get_identifier(void) const;

    void set_identifier(const std::string & identifier);

    bool requires_parameter(void) const;

    const ias::value_type * get_parameter_type(void) const;

    void set_parameter_type(const ias::value_type * type);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
