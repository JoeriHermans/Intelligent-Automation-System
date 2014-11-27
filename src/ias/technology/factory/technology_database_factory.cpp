/**
 * A class which is responsible for extracting technologies from a database.
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
#include <ias/technology/factory/technology_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void TechnologyDatabaseFactory::setContainers( Container<Member *> * members,
                                               Container<Feature *> * features ) {
    // Checking the preconditions.
    assert( features != nullptr && members != nullptr );

    mFeaturesContainer = features;
    mMembersContainer = members;
}

std::vector<Feature *> TechnologyDatabaseFactory::fetchFeatures(
    const std::size_t id ) const {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Feature *> features;
    std::string query;
    std::size_t featureId;

    query = "SELECT id "
            "FROM technology_features "
            "WHERE technology_id = ";
    query = query + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr )
    {
        result = statement->execute();
        if( result != nullptr )
        {
            while( result->hasNext() )
            {
                row = result->next();
                featureId = static_cast<std::size_t>(
                        atol(row->getColumn(0).c_str()));
                features.push_back(mFeaturesContainer->get(featureId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( features );
}

std::vector<Member *> TechnologyDatabaseFactory::fetchMembers(
    const std::size_t id ) const {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Member *> members;
    std::string query;
    std::size_t memberId;

    query = "SELECT id "
            "FROM technology_members "
            "WHERE technology_id = ";
    query = query + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                memberId = static_cast<std::size_t>(
                        atol(row->getColumn(0).c_str()));
                members.push_back(mMembersContainer->get(memberId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( members );
}

Technology * TechnologyDatabaseFactory::allocateTechnology(
    const std::string & id, const std::string & identifier,
    const std::string & name, const std::string & description ) const {
    Technology * technology;
    std::vector<Member *> members;
    std::vector<Feature *> features;
    std::size_t technologyId;

    technologyId = static_cast<std::size_t>(atol(id.c_str()));
    features = fetchFeatures(technologyId);
    members = fetchMembers(technologyId);
    technology = new Technology(technologyId,identifier,name,description,
                                members,features);

    return ( technology );
}

TechnologyDatabaseFactory::TechnologyDatabaseFactory(
    DatabaseConnection * conn, Container<Member *> * members,
    Container<Feature *> * features ) : DatabaseFactory<Technology *>(conn) {
    setContainers(members,features);
}

TechnologyDatabaseFactory::~TechnologyDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Technology *> TechnologyDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Technology *> technologies;
    std::string id;
    std::string identifier;
    std::string name;
    std::string description;

    statement = getDbConnection()->createStatement(
        "SELECT *"
        "FROM technologies"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = row->getColumn(0);
                identifier = row->getColumn(1);
                name = row->getColumn(2);
                description = row->getColumn(3);
                technologies.push_back(allocateTechnology(id,
                                                          identifier,
                                                          name,
                                                          description));
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( technologies );
}
