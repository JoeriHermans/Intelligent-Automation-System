/**
 * A class which describes the properties and actions of a bulding database
 * factory.
 *
 * @date                    Jul 24, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2013 Joeri HERMANS
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

#ifndef BUILDING_FACTORY_DATABASE_H_
#define BUILDING_FACTORY_DATABASE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/building/area.h>
#include <ias/building/building.h>
#include <ias/factory/database_factory.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class BuildingDatabaseFactory : public DatabaseFactory<Building *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * A contains which holds all areas which are registered to IAS.
     */
    const Container<Area *> * mAreas;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setAreaContainer( const Container<Area *> * areas );
    
    std::vector<Area *> fetchAreas( const std::size_t id ) const;
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    BuildingDatabaseFactory( DatabaseConnection * dbConnection,
                             Container<Area *> * areas );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~BuildingDatabaseFactory( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual std::vector<Building *> fetchAll( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* BUILDING_FACTORY_DATABASE_H_ */
