/**
 * A class which is responsible for extracting technology members from a
 * database.
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
#include <ias/technology/factory/member_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void MemberDatabaseFactory::setTypesContainer( Container<ValueType *> * t ) {
    // Checking the precondition.
    assert( t != nullptr );
    
    mTypesContainer = t;
}

Member * MemberDatabaseFactory::allocateMember( const std::string & id,
                                                const std::string & identifier,
                                                const std::string & name,
                                                const std::string & description,
                                                const std::string & defaultValue,
                                                const std::string & valueTypeId ) const {
    Member * member;
    ValueType * type;
    std::size_t memberId;
    std::size_t valueId;
    
    memberId = (std::size_t) atol(id.c_str());
    valueId = (std::size_t) atol(valueTypeId.c_str());
    type = mTypesContainer->get(valueId);
    member = new Member(memberId,identifier,name,description,
                        defaultValue,type);
    
    return ( member );
}

MemberDatabaseFactory::MemberDatabaseFactory( DatabaseConnection * connection,
                                              Container<ValueType *> * types ) :
    DatabaseFactory<Member *>(connection) {
    setTypesContainer(types);
}

MemberDatabaseFactory::~MemberDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Member *> MemberDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Member *> members;
    std::string id;
    std::string valueTypeId;
    std::string identifier;
    std::string name;
    std::string description;
    std::string defaultValue;
    
    statement = getDbConnection()->createStatement(
        "SELECT *"
        "FROM technology_members"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = row->getColumn(0);
                valueTypeId = row->getColumn(2);
                identifier = row->getColumn(3);
                defaultValue = row->getColumn(4);
                name = row->getColumn(5);
                description = row->getColumn(6);
                members.push_back(allocateMember(id,identifier,name,description,
                                                 defaultValue,valueTypeId));
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( members );
}
