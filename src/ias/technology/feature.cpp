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
#include <cassert>

// Application dependencies.
#include <ias/technology/feature.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void feature::initialize(void) {
        mId = 0;
        mParameterType = nullptr;
    }

    void feature::set_id(const std::size_t id) {
        // Checking the precondition.
        assert(id > 0);

        mId = id;
    }

    feature::feature(const std::size_t id, const std::string & identifier,
                     const ias::value_type * parameterType) {
        initialize();
        set_id(id);
        set_identifier(identifier);
        set_parameter_type(parameterType);
    }

    const std::size_t feature::get_id(void) const {
        return mId;
    }

    const std::string & feature::get_identifier(void) const {
        return mIdentifier;
    }

    void feature::set_identifier(const std::string & identifier) {
        // Checking the precondition.
        assert(!identifier.empty());

        mMutexIdentifier.lock();
        mIdentifier = identifier;
        mMutexIdentifier.unlock();
    }

    bool feature::requires_parameter(void) const {
        return mParameterType != nullptr;
    }

    const ias::value_type * feature::get_parameter_type(void) const {
        return mParameterType;
    }

    void feature::set_parameter_type(const ias::value_type * type) {
        mMutexParameterType.lock();
        mParameterType = type;
        mMutexParameterType.unlock();
    }

};
