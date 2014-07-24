/**
 * A class which is responsible for retrieving controllers from a database.
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

#ifndef CONTROLLER_DATABASE_FACTORY_H_
#define CONTROLLER_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/controller/controller.h>
#include <ias/factory/database_factory.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class ControllerDatabaseFactory : public DatabaseFactory<Controller *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains a set of all devices.
     */
    Container<Device *> * mDeviceContainer;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setDeviceContainer( Container<Device *> * devices );
    
    std::vector<Device *> fetchDevices( const std::size_t id ) const;
    
    Controller * allocateController( const std::string & id,
                                     const std::string & identifier,
                                     const std::string & name,
                                     const std::string & description,
                                     const std::string & securityCode ) const;
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    ControllerDatabaseFactory( DatabaseConnection * connection,
                               Container<Device *> * devices );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ControllerDatabaseFactory( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual std::vector<Controller *> fetchAll( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONTROLLER_DATABASE_FACTORY_H_ */
