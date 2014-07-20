/**
 * A value type factory which fetches value type instances from
 * a database.
 *
 * @date					Jul 4, 2014
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
#include <ias/technology/factory/value_type_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

ValueTypeDatabaseFactory::ValueTypeDatabaseFactory( DatabaseConnection * c ) :
    DatabaseFactory<ValueType *>(c) {
    // Nothing to do here.
}

ValueTypeDatabaseFactory::~ValueTypeDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<ValueType *> ValueTypeDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<ValueType *> types;
    std::string strId;
    long bufferId;
    std::size_t id;
    std::string identifier;
    std::string name;
    std::string description;
    std::string regex;
    
    statement = getDbConnection()->createStatement(
        "SELECT *"
        "FROM value_types"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                strId = row->getColumn(0);
                identifier = row->getColumn(1);
                regex = row->getColumn(2);
                name = row->getColumn(3);
                description = row->getColumn(4);
                bufferId = atol(strId.c_str());
                id = (std::size_t) bufferId;
                types.push_back(
                    new ValueType(id,identifier,name,description,regex)
                );
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( types );
}
