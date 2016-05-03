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
#include <cassert>

// Application dependencies.
#include <ias/technology/member.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void member::initialize(void) {
        mId = 0;
        mValueType = nullptr;
    }

    void member::set_id(const std::size_t id) {
        // Checking the precondition.
        assert(id > 0);

        mId = id;
    }

    member::member(const std::size_t id, const std::string & identifier,
                   const std::string & defaultValue, const ias::value_type * type) {
        initialize();
        set_id(id);
        set_identifier(identifier);
        set_value_type(type);
        set_default_value(defaultValue);
    }

    const std::size_t member::get_id(void) const {
        return mId;
    }

    const std::string & member::get_identifier(void) const {
        return mIdentifier;
    }

    void member::set_identifier(const std::string & identifier) {
        // Checking the precondition.
        assert(!identifier.empty());

        mMutexIdentifier.lock();
        mIdentifier = identifier;
        mMutexIdentifier.unlock();
    }

    const std::string & member::get_default_value(void) const {
        return mDefaultValue;
    }

    void member::set_default_value(const std::string & defaultValue) {
        mMutexValueType.lock();
        // Check if the specified default value is valid.
        if(mValueType->matches(defaultValue)) {
            mMutexDefaultValue.lock();
            mDefaultValue = defaultValue;
            mMutexDefaultValue.unlock();
        }
        mMutexValueType.unlock();
    }

    void member::set_value_type(const ias::value_type * type) {
        // Checking the precondition.
        assert(type != nullptr);

        mMutexValueType.lock();
        mValueType = type;
        mMutexValueType.unlock();
    }

    const ias::value_type * member::get_value_type(void) const {
        return mValueType;
    }

};
