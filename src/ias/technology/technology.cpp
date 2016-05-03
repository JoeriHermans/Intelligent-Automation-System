/**
 * A class which represents the properties and actions of a technology.
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
#include <ias/technology/technology.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void technology::initialize(void) {
        mId = 0;
    }

    void technology::set_members(const std::vector<ias::member *> & members) {
        mMembers = members;
    }

    void technology::set_features(const std::vector<ias::feature *> & features) {
        mFeatures = features;
    }

    void technology::set_id(const std::size_t id) {
        // Checking the precondition.
        assert(id > 0);

        mId = id;
    }

    technology::technology(const std::size_t id,
                           const std::vector<ias::member *> & members,
                           const std::vector<ias::feature *> & features) {
        initialize();
        set_id(id);
        set_members(members);
        set_features(features);
    }

    const std::size_t technology::get_id(void) const {
        return mId;
    }

    const std::vector<ias::member *> & technology::get_members(void) const {
        return mMembers;
    }

    const std::size_t technology::num_members(void) const {
        return mMembers.size();
    }

    ias::member * technology::get_member(const std::string & identifier) const {
        ias::member * member;

        member = nullptr;
        mMutexMembers.lock();
        for(auto it = mMembers.begin(); it != mMembers.end(); ++it) {
            if((*it)->get_identifier().compare(identifier) == 0) {
                member = (*it);
                break;
            }
        }
        mMutexMembers.unlock();

        return member;
    }

    ias::member * technology::get_member(const std::size_t index) const {
        ias::member * member;

        member = nullptr;
        mMutexMembers.lock();
        // Check if the specified index is valid.
        if(index < mMembers.size())
            member = mMembers.at(index);
        mMutexMembers.unlock();

        return member;
    }

    void technology::add_member(ias::member * member) {
        mMutexMembers.lock();
        mMembers.push_back(member);
        mMutexMembers.unlock();
    }

    const std::vector<ias::feature *> & technology::get_features(void) const {
        return mFeatures;
    }

    ias::feature * technology::get_feature(const std::string & identifier) const {
        ias::feature * feature;

        feature = nullptr;
        mMutexFeatures.lock();
        for(auto it = mFeatures.begin(); it != mFeatures.end(); ++it) {
            if((*it)->get_identifier().compare(identifier) == 0) {
                feature = (*it);
                break;
            }
        }
        mMutexFeatures.unlock();

        return feature;
    }

    ias::feature * technology::get_feature(const std::size_t index) const {
        ias::feature * feature;

        feature = nullptr;
        mMutexFeatures.lock();
        feature = mFeatures.at(index);
        mMutexFeatures.unlock();

        return feature;
    }

    void technology::add_feature(ias::feature * feature) {
        // Checking the precondition.
        assert(feature != nullptr);

        mMutexFeatures.lock();
        mFeatures.push_back(feature);
        mMutexFeatures.unlock();
    }

};
