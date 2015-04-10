/**
 * A database factory which is responsible for retrieving all areas and
 * connections from a database. This database factory will also create the
 * connections between the individual areas.
 *
 * @date                    9 April, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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

#ifndef AREA_DATABASE_FACTORY_H_
#define AREA_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/building/area.h>
#include <ias/factory/database_factory.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class AreaDatabaseFactory : public DatabaseFactory<Area *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    /**
     * Contains the storage of all areas in the system.
     */
    Container<Area *> * mAreas;

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    void setStorage( Container<Area *> * areas );

    void buildAreaNetwork( void ) const;

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    AreaDatabaseFactory( DatabaseConnection * dbConnection,
                         Container<Area *> * areas );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~AreaDatabaseFactory( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::vector<Area *> fetchAll( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* AREA_DATABASE_FACTORY_H_ */
