/**
 *
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

#ifdef IAS_DATABASE_DRIVER
#if IAS_DATABASE_DRIVER == 'M' || IAS_DATABASE_DRIVER == 'A'

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mysql/mysql.h>
#include <mysql/my_global.h>
#include <mutex>

// Application dependencies.
#include <ias/data_access/data_access.h>
#include <ias/user/user.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MYSQL_USER_DATA_ACCESS_H_
#define IAS_MYSQL_USER_DATA_ACCESS_H_

namespace ias {

class user_data_access : public data_access<ias::user *> {

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

    user_data_access(void);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual user_data_access(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<ias::user *> get_all(void) const = 0;

    virtual ias::user * get(const std::size_t id) const = 0;

    virtual void add(ias::user * user) = 0;

    virtual void remove(ias::user * user) = 0;

    virtual void remove(const std::size_t id) = 0;

    virtual void update(ias::user * user) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
#endif
#endif
