/**
 * An area database factory which is responsible for fetching instances of areas
 * from the specified database.
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

#ifndef AREA_FACTORY_DATABASE_H_
#define AREA_FACTORY_DATABASE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/building/area.h>
#include <ias/device/device.h>
#include <ias/factory/database_factory.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class AreaDatabaseFactory : public DatabaseFactory<Area *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * A container which holds all devices which are related to IAS.
     */
    const Container<Device *> * mDevices;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setDeviceContainer( const Container<Device *> * devices );
    
    std::vector<Device *> fetchDevices( const std::size_t id );
    
    void linkAreas( std::vector<Area *> & areas );
    
    static Area * getArea( const std::vector<Area *> & areas,
                           const std::size_t id );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    AreaDatabaseFactory( DatabaseConnection * dbConnection,
                         const Container<Device *> * devices );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
        
    virtual ~AreaDatabaseFactory( void );
        
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
        
    virtual std::vector<Area *> fetchAll( void );
        
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* AREA_FACTORY_DATABASE_H_ */
