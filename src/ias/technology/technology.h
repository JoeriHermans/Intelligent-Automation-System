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
#include <vector>
#include <string>
#include <mutex>

// Application dependencies.
#include <ias/technology/feature.h>
#include <ias/technology/member.h>
#include <ias/technology/value_type.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_TECHNOLOGY_H_
#define IAS_TECHNOLOGY_H_

namespace ias {

class technology {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique id of the technology.
     */
    std::size_t mId;

    /**
     * Holds the set of members associated with this technology.
     */
    std::vector<ias::member *> mMembers;

    /**
     * Holds the set of features associated with this technology.
     */
    std::vector<ias::feature *> mFeatures;

    /**
     * Mutexes for synchronizing data access to the members.
     */
    mutable std::mutex mMutexMembers;
    mutable std::mutex mMutexFeatures;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_id(const std::size_t id);

    void set_members(const std::vector<ias::member *> & members);

    void set_features(const std::vector<ias::feature *> & features);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    technology(const std::size_t id,
               const std::vector<ias::member *> & members,
               const std::vector<ias::feature *> & features);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~technology(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    const std::size_t get_id(void) const;

    const std::vector<ias::member *> & get_members(void) const;

    const std::size_t num_members(void) const;

    ias::member * get_member(const std::string & identifier) const;

    ias::member * get_member(const std::size_t index) const;

    void add_member(ias::member * member);

    const std::vector<ias::feature *> & get_features(void) const;

    const std::size_t num_features(void) const;

    ias::feature * get_feature(const std::string & identifier) const;

    ias::feature * get_feature(const std::size_t index) const;

    void add_feature(ias::feature * feature);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
