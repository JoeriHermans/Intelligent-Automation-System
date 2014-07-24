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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/controller/factory/controller_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void ControllerDatabaseFactory::setDeviceContainer( Container<Device *> * c ) {
    // Checking the precondition.
    assert( c != nullptr );
    
    mDeviceContainer = c;
}

std::vector<Device *> ControllerDatabaseFactory::fetchDevices( 
    const std::size_t id ) const {
    std::vector<Device *> devices;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string query;
    std::size_t deviceId;
    
    query =
        "SELECT id "
        "FROM devices "
        "WHERE controller_id = ";
    query = query + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                deviceId = (std::size_t) atol(row->getColumn(0).c_str());
                devices.push_back(mDeviceContainer->get(deviceId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( devices );
}

Controller * ControllerDatabaseFactory::allocateController( 
    const std::string & id, const std::string & identifier,
    const std::string & name, const std::string & description,
    const std::string & securityCode ) const {
    std::vector<Device *> devices;
    Controller * controller;
    std::size_t controllerId;
    
    controllerId = (std::size_t) atol(id.c_str());
    devices = fetchDevices(controllerId);
    controller = new Controller(controllerId,identifier,name,description,
                                securityCode,devices);
    
    return ( controller );
}

ControllerDatabaseFactory::ControllerDatabaseFactory(
    DatabaseConnection * conn, Container<Device *> * devices ) :
    DatabaseFactory<Controller *>(conn) {
    setDeviceContainer(devices);
}

ControllerDatabaseFactory::~ControllerDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Controller *> ControllerDatabaseFactory::fetchAll( void ) {
    std::vector<Controller *> controllers;
    Controller * controller;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string id;
    std::string identifier;
    std::string description;
    std::string name;
    std::string securityCode;
    
    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM controllers;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = row->getColumn(0);
                identifier = row->getColumn(1);
                securityCode = row->getColumn(2);
                name = row->getColumn(3);
                description = row->getColumn(4);
                controller = allocateController(id,identifier,name,
                                                description,securityCode);
                controllers.push_back(controller);
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( controllers );
}
