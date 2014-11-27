/**
 * A database factory which is responsible for fetching technology features
 * from a database.
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

// Application dependencies.
#include <ias/technology/factory/feature_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void FeatureDatabaseFactory::setTypesContainer( Container<ValueType *> * types ) {
    // Checking the precondition.
    assert( types != nullptr );

    mTypesContainer = types;
}

Feature * FeatureDatabaseFactory::allocateFeature(
    const std::string & id, const std::string & identifier,
    const std::string & name, const std::string & description,
    const std::string & valueTypeId ) const {
    Feature * f;
    ValueType * type;
    std::size_t featureId;

    featureId = static_cast<std::size_t>(atol(id.c_str()));
    // Check if the value type is null.
    if( valueTypeId.empty() )
        type = nullptr;
    else
        type = mTypesContainer->get(
                static_cast<std::size_t>(atol(valueTypeId.c_str())));
    f = new Feature(featureId,identifier,name,description,type);

    return ( f );
}

FeatureDatabaseFactory::FeatureDatabaseFactory(
    DatabaseConnection * conn, Container<ValueType *> * types ) :
    DatabaseFactory<Feature *>(conn) {
    setTypesContainer(types);
}

FeatureDatabaseFactory::~FeatureDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Feature *> FeatureDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Feature *> features;
    std::string id;
    std::string identifier;
    std::string name;
    std::string description;
    std::string valueTypeId;

    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM technology_features;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = row->getColumn(0);
                identifier = row->getColumn(2);
                valueTypeId = row->getColumn(3);
                name = row->getColumn(4);
                description = row->getColumn(5);
                features.push_back(allocateFeature(id,
                                                   identifier,
                                                   name,
                                                   description,
                                                   valueTypeId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( features );
}
