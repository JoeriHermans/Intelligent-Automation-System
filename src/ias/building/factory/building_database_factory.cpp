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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/building/factory/building_factory_database.h>

// END Includes. /////////////////////////////////////////////////////

void BuildingDatabaseFactory::setAreaContainer( const Container<Area *> * a ) {
    // Checking the precondition.
    assert( a != nullptr );
    
    mAreas = a;
}

std::vector<Area *> BuildingDatabaseFactory::fetchAreas( const std::size_t id )
    const {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Area *> areas;
    std::string query;
    std::string strAreaId;
    std::size_t areaId;
    Area * area;
    
    query =
        "SELECT area_id "
        "FROM building_areas "
        "WHERE building_id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                strAreaId = row->getColumn(0);
                areaId = (std::size_t) atol(strAreaId.c_str());
                area = mAreas->get(areaId);
                if( area != nullptr ) {
                    areas.push_back(area);
                }
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( areas );
}

BuildingDatabaseFactory::BuildingDatabaseFactory( 
    DatabaseConnection * dbConnection,
    Container<Area *> * areas ) :
    DatabaseFactory<Building *>(dbConnection) {
    setAreaContainer(areas);
}

BuildingDatabaseFactory::~BuildingDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Building *> BuildingDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Building *> buildings;
    std::string strId;
    std::size_t id;
    std::string identifier;
    std::string name;
    std::string description;

    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM buildings;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::vector<Area *> areas;
                
                row = result->next();
                strId = row->getColumn(0);
                id = (std::size_t) atol(strId.c_str());
                identifier = row->getColumn(1);
                name = row->getColumn(2);
                description = row->getColumn(3);
                areas = fetchAreas(id);
                buildings.push_back(
                    new Building(id,identifier,name,description,areas)
                );
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( buildings );
}
