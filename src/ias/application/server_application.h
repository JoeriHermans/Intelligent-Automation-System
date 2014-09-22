/**
 * A class which describes the actions and properties of the IAS
 * server applications.
 *
 * @date                    Jul 2, 2014
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

#ifndef SERVER_APPLICATION_H_
#define SERVER_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/ai/nlp/natural_language_processor.h>
#include <ias/application/application.h>
#include <ias/building/area.h>
#include <ias/building/building.h>
#include <ias/controller/controller.h>
#include <ias/device/device.h>
#include <ias/device/device_monitor.h>
#include <ias/database/interface/database_connection.h>
#include <ias/database/interface/database_driver.h>
#include <ias/database/mysql/mysql_driver.h>
#include <ias/database/postgresql/postgresql_driver.h>
#include <ias/technology/technology.h>
#include <ias/technology/feature.h>
#include <ias/technology/member.h>
#include <ias/technology/value_type.h>
#include <ias/server/controller_server.h>
#include <ias/server/user_server.h>
#include <ias/user/user.h>
#include <ias/user/factory/user_database_factory.h>
#include <ias/util/container.h>
#include <ias/util/properties.h>
#include <ias/user/command/command_dispatcher.h>
#include <ias/operator/operator_equals.h>
#include <ias/operator/operator_greater_than.h>
#include <ias/operator/operator_less_than.h>
#include <ias/operator/operator_not_equals.h>
#include <ias/operator/operator_less_than_equals.h>
#include <ias/operator/operator_greater_than_equals.h>
#include <ias/rule/rule.h>

// END Includes. /////////////////////////////////////////////////////

class ServerApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Containers which are responsible for keeping track of the multiple
     * elements in IAS.
     */
    Container<Controller *> mContainerControllers;
    Container<Device *> mContainerDevices;
    Container<Technology *> mContainerTechnologies;
    Container<Feature *> mContainerFeatures;
    Container<Member *> mContainerMembers;
    Container<ValueType *> mContainerValueTypes;
    Container<User *> mContainerUsers;
    Container<Building *> mContainerBuildings;
    Container<Area *> mContainerAreas;
    Container<Rule *> mContainerRules;
    
    /**
     * Contains the IAS natural language processor.
     */
    NaturalLanguageProcessor * mNlp;
    
    /**
     * Contains the set of operators which are available to IAS.
     */
    std::map<std::string,Operator *> mOperators;
    
    /**
     * Contains the database connection.
     */
    DatabaseConnection * mDbConnection;
    
    /**
     * Contains the servers which are responsible for handling controller
     * connections and updates.
     */
    ControllerServer * mServerController;
    ControllerServer * mServerControllerSsl;
    
    /**
     * Contains the servers which are responsible for handling user
     * connections and commands.
     */
    UserServer * mServerUser;
    UserServer * mServerUserSsl;
    
    /**
     * Contains all by-default and key-value relationships which have been
     * read from the configuration file.
     */
    Properties mProperties;
    
    /**
     * Contains the user command dispatcher.
     */
    CommandDispatcher mDispatcher;
    
    /**
     * A flag which can be used to stop the server application.
     */
    bool mFlagRunning;
    
    /**
     * A device monitor which is responsible for reporting state updates to
     * the storage medium.
     */
    DeviceMonitor * mDeviceMonitor;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setup( const int argc , const char ** argv );
    
    void readConfiguration( const std::string & filePath );
    
    void connectToDatabase( void );
    
    void fillUsers( void );
    
    void fillContainers( void );
    
    void fillValueTypes( void );
    
    void fillMembers( void );
    
    void fillFeatures( void );
    
    void fillTechnologies( void );
    
    void fillDevices( void );
    
    void fillControllers( void );
    
    void fillBuildings( void );
    
    void fillAreas( void );
    
    void fillRules( void );
    
    void initializeSalts( void );
    
    void initializeNlp( void );
    
    void initializeControllerServer( void );
    
    void initializeControllerSslServer( void );

    void initializeUserServer( void );
    
    void initializeUserSslServer( void );

    void initializeDispatcher( void );
    
    void registerOperators( void );
    
    void cleanupOperators( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    ServerApplication( const int argc , const char ** argv );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ServerApplication( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void );
    
    virtual void stop( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SERVER_APPLICATION_H_ */
