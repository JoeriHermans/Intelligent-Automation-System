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
#include <cassert>

// Application dependencies.
#include <ias/user/user.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void user::initialize(void) {
        mDisabled = false;
    }

    void user::set_id(const std::size_t id) {
        // Checking the precondition.
        assert(id > 0);

        mId = id;
    }

    user::user(const std::size_t id,
               const std::string & username,
               const std::string & password,
               const std::string & email,
               const std::string & name,
               const std::string & surname,
               const ias::user_gender & gender) {
        initialize();
        set_id(id);
        set_username(username);
        set_password(password);
        set_email(email);
        set_name(name);
        set_surname(surname);
        set_gender(gender);
    }

    user::user(const std::size_t id,
               const std::string & username,
               const std::string & password,
               const std::string & email,
               const std::string & name,
               const std::string & surname,
               const ias::user_gender & gender,
               const bool disabled) {
        set_id(id);
        set_username(username);
        set_password(password);
        set_email(email);
        set_name(name);
        set_surname(surname);
        set_gender(gender);
        set_disabled(disabled);
    }

    bool user::is_disabled(void) const {
        return mDisabled;
    }

    bool user::is_female(void) const {
        return mGender == ias::user_gender::FEMALE;
    }

    bool user::is_male(void) const {
        return mGender == ias::user_gender::MALE;
    }

    bool user::matches_password(const std::string & password) const {
        std::string hashed = ias::sha256(password, gSaltPre, gSaltPost);

        return mPassword == hashed;
    }

    const ias::user_gender & user::get_gender(void) const {
        return mGender;
    }

    const std::size_t user::get_id(void) const {
        return mId;
    }

    const std::string & user::get_email(void) const {
        return mEmail;
    }

    const std::string & user::get_password(void) const {
        return mPassword;
    }

    const std::string & user::get_username(void) const {
        return mUsername;
    }

    void user::set_disabled(const bool flag) {
        mDisabled = flag;
    }

    void user::set_email(const std::string & email) {
        // Checking the precondition.
        assert(!email.empty());

        mEmail = email;
    }

    void user::set_gender(const ias::user_gender & gender) {
        mGender = gender;
    }

    void user::set_name(const std::string & name) {
        // Checking the precondition.
        assert(!name.empty());

        mName = name;
    }

    void user::set_password(const std::string & password) {
        // Checking the precondition.
        assert(!password.empty());

        mPassword = ias::sha256(password, gSaltPre, gSaltPost);
    }

    void user::set_surname(const std::string & surname) {
        // Checking the precondition.
        assert(!surname.empty());

        mSurname = surname;
    }

    void user::set_username(const std::string & username) {
        // Checking the precondition.
        assert(!username.empty());

        mUsername = username;
    }

};
