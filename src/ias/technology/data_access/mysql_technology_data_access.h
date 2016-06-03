/**
 * A class which represents the MySQL technology data access layer.
 *
 * @date                    03 06 2016
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

// Application dependencies.
#include <ias/technology/data_access/feature_data_access.h>
#include <ias/technology/data_access/member_data_access.h>
#include <ias/technology/data_access/technology_data_access.h>
#include <ias/technology/data_access/value_type_data_access.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_MYSQL_TECHNOLOGY_DATA_ACCESS_H_
#define IAS_MYSQL_TECHNOLOGY_DATA_ACCESS_H_

namespace ias {

class mysql_technology_data_access : public technology_data_access {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    static const char kStmtAdd[];
    static const char kStmtGetAll[];
    static const char kStmtGetId[];
    static const char kStmtRemove[];
    static const char kStmtUpdate[];

    static const std::size_t kDefaultStringSize = 80;

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

    mysql_technology_data_access(ias::database_connection * dbConn);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~mysql_technology_data_access(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<ias::technology *> get_all(void);

    virtual ias::technology * get(const std::size_t id);

    virtual void add(ias::technology * element);

    virtual void remove(ias::technology * element);

    virtual void remove(const std::size_t id);

    virtual void update(ias::technology * element);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
#endif
#endif
