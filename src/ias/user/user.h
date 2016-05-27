/**
 * A class which describes the actions and properties of a user.
 *
 * @date                    27 05 2016
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

// Application dependencies.
#include <ias/user/user_gender.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_USER_H_
#define IAS_USER_H_

namespace ias {

class user {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the unique ID identifier of a user.
     */
    std::size_t mId;

    /**
     * Holds the unique username (string) of a user.
     */
    std::string mUsername;

    /**
     * Other user properties which do not need additional documentation.
     */
    std::string mPassword;
    std::string mEmail;
    std::string mName;
    std::string mSurname;
    ias::user_gender mGender;
    bool mDisabled;

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

    user(const std::size_t id,
         const std::string & username,
         const std::string & password,
         const std::string & email,
         const std::string & name,
         const std::string & surname,
         const ias::user_gender & gender);

    user(const std::size_t id,
         const std::string & username,
         const std::string & password,
         const std::string & email,
         const std::string & name,
         const std::string & surname,
         const ias::user_gender & gender,
         const bool diabled);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~user(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    bool is_disabled(void) const;

    bool is_female(void) const;

    bool is_male(void) const;

    bool matches_password(const std::string & password) const;

    const ias::user_gender & get_gender(void) const;

    const std::size_t get_id(void) const;

    const std::string & get_email(void) const;

    const std::string & get_password(void) const;

    const std::string & get_username(void) const;

    void set_disabled(const bool flag);

    void set_email(const std::string & email);

    void set_gender(const ias::user_gender & gender);

    void set_name(const std::string & name);

    void set_password(const std::string & password);

    void set_surname(const std::string & surname);

    void set_username(const std::string & username);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
