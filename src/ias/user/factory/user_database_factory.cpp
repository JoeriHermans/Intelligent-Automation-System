/**
 * A class which represents the properties and actions of a user database
 * factory.
 *
 * @date                    Jul 18, 2014
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
#include <vector>

// Application dependencies.
#include <ias/factory/database_factory.h>
#include <ias/user/user.h>
#include <ias/user/factory/user_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

UserDatabaseFactory::UserDatabaseFactory( DatabaseConnection * conn ) :
    DatabaseFactory<User *>( conn ) {
    // Nothing to do here.
}

UserDatabaseFactory::~UserDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<User *> UserDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string strId;
    std::size_t id;
    std::string username;
    std::string password;
    std::vector<User *> users;

    statement = getDbConnection()->createStatement(
        "SELECT id, username, password "
        "FROM users;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                strId = row->getColumn(0);
                username = row->getColumn(1);
                password = row->getColumn(2);
                id = static_cast<std::uint8_t>(atol(strId.c_str()));
                users.push_back(new User(id,username,password));
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( users );
}
