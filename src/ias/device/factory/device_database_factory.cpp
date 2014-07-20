/**
 * A class which is responsible for extracting devices from a database.
 *
 * @date					Jul 5, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

// Application dependencies.
#include <ias/device/factory/device_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void DeviceDatabaseFactory::setTechnologyContainer( 
    Container<Technology *> * technologies ) {
    // Checking the precondition.
    assert( technologies != nullptr );
    
    mTechnologiesContainer = technologies;
}

Device * DeviceDatabaseFactory::allocateDevice( const std::string & id,
                                                const std::string & identifier,
                                                const std::string & name,
                                                const std::string & description,
                                                const std::string & techId ) 
                                                const {
    Device * d;
    std::size_t deviceId;
    std::size_t technologyId;
    
    deviceId = (std::size_t) atol(id.c_str());
    technologyId = (std::size_t) atol(techId.c_str());
    d = new Device(deviceId,identifier,name,description,
                   mTechnologiesContainer->get(technologyId));
    
    return ( d );
}

DeviceDatabaseFactory::DeviceDatabaseFactory( DatabaseConnection * connection,
                                              Container<Technology *> * tech ) :
   DatabaseFactory<Device *>(connection) {
    setTechnologyContainer(tech);
}

std::vector<Device *> DeviceDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Device *> technologies;
    std::string id;
    std::string identifier;
    std::string description;
    std::string name;
    std::string technologyId;
    
    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM devices;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = row->getColumn(0);
                identifier = row->getColumn(3);
                name = row->getColumn(4);
                description = row->getColumn(5);
                technologyId = row->getColumn(2);
                technologies.push_back(allocateDevice(id,
                                                      identifier,
                                                      name,
                                                      description,
                                                      technologyId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( technologies );
}
