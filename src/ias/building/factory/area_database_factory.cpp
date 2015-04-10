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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/building/factory/area_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void AreaDatabaseFactory::setStorage( Container<Area *> * areas ) {
    // Checking the precondition.
    assert( areas != nullptr );

    mAreas = areas;
}

void AreaDatabaseFactory::buildAreaNetwork() const {
//    DatabaseStatement * statement;
//    DatabaseResult * result;
//    DatabaseResultRow * row;
//
//    // Checking the precondition.
//    assert( !areas.empty() );
//
//    // TODO Implement.
}

AreaDatabaseFactory::AreaDatabaseFactory( DatabaseConnection * dbConnection,
                                          Container<Area *> * areas ) :
    DatabaseFactory(dbConnection) {
    setStorage(areas);
}

std::vector<Area *> AreaDatabaseFactory::fetchAll( void ) {
    std::vector<Area *> areas;
    Area * area;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::size_t id;
    std::string identifier;
    std::string name;
    std::string description;

    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM areas;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = atol(row->getColumn(0).c_str());
                identifier = row->getColumn(1);
                name = row->getColumn(2);
                description = row->getColumn(3);
                area = new Area(id,identifier,name,description);
                mAreas->add(area);
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    if( !areas.empty() )
        buildAreaNetwork();

    return ( areas );
}
