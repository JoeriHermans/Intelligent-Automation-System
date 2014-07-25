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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/building/factory/area_factory_database.h>

// END Includes. /////////////////////////////////////////////////////

void AreaDatabaseFactory::setDeviceContainer( const Container<Device *> * 
                                              devices ) {
    // Checking the precondition.
    assert( devices != nullptr );
    
    mDevices = devices;
}

std::vector<Device *> AreaDatabaseFactory::fetchDevices( const std::size_t id ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Device *> devices;
    std::string query;
    std::string strId;
    std::size_t deviceId;
    Device * d;
    
    query = 
        "SELECT device_id "
        "FROM area_devices "
        "WHERE area_id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                strId = row->getColumn(0);
                deviceId = (std::size_t) atol(strId.c_str());
                d = mDevices->get(deviceId);
                if( d != nullptr ) {
                    devices.push_back(d);
                }
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( devices );
}

#include <iostream>

void AreaDatabaseFactory::linkAreas( std::vector<Area *> & areas ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string fromId;
    std::string toId;
    std::size_t idFrom;
    std::size_t idTo;
    Area * areaFrom;
    Area * areaTo;
    
    statement = getDbConnection()->createStatement(
        "SELECT area_from_id, area_to_id "
        "FROM area_links;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                fromId = row->getColumn(0);
                toId = row->getColumn(1);
                idFrom = (std::size_t) atol(fromId.c_str());
                idTo = (std::size_t) atol(toId.c_str());
                areaFrom = getArea(areas,idFrom);
                areaTo = getArea(areas,idTo);
                if( areaFrom != nullptr && areaTo != nullptr ) {
                    areaFrom->addAdjacentArea(areaTo);
                }
                
                delete row;
            }
            delete result;
        }
        delete statement;
    }
}

Area * AreaDatabaseFactory::getArea( const std::vector<Area *> & areas,
                                     const std::size_t id ) {
    Area * result;
    
    result = nullptr;
    for( Area * area : areas ) {
        if( area->getId() == id ) {
            result = area;
            break;
        }
    }
    
    return ( result );
}

AreaDatabaseFactory::AreaDatabaseFactory( DatabaseConnection * dbConnection,
                                          const Container<Device *> * d ) :
    DatabaseFactory<Area *>(dbConnection) {
    setDeviceContainer(d);
}

AreaDatabaseFactory::~AreaDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Area *> AreaDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Area *> areas;
    std::string strId;
    std::size_t id;
    std::string identifier;
    std::string name;
    std::string description;
    
    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM areas "
        "ORDER BY id ASC;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::vector<Device *> devices;
                
                row = result->next();
                strId = row->getColumn(0);
                identifier = row->getColumn(1);
                name = row->getColumn(2);
                description = row->getColumn(3);
                id = (std::size_t) atol(strId.c_str());
                devices = fetchDevices(id);
                areas.push_back(
                    new Area(id,name,identifier,description,devices)
                );
                delete row;
            }
            if( areas.size() > 0 )
                linkAreas(areas);
            delete result;
        }
        delete statement;
    }
    
    return ( areas );
}
