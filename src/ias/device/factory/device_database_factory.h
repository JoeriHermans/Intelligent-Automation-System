/**
 * A class which is responsible for extracting devices from a database.
 *
 * @date                    Jul 5, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
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

#ifndef DEVICE_DATABASE_FACTORY_H_
#define DEVICE_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/device/device.h>
#include <ias/factory/database_factory.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class DeviceDatabaseFactory : public DatabaseFactory<Device *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * A container which contains all technologies.
     */
    Container<Technology *> * mTechnologiesContainer;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setTechnologyContainer( Container<Technology *> * technologies );
    
    Device * allocateDevice( const std::string & id,
                             const std::string & identifier,
                             const std::string & name,
                             const std::string & description,
                             const std::string & technologyId ) const;
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    DeviceDatabaseFactory( DatabaseConnection * connection,
                           Container<Technology *> * technologies );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual std::vector<Device *> fetchAll( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_DATABASE_FACTORY_H_ */
