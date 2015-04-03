/**
 * A command which is responsible for changing the password of user.
 *
 * @date                    26 January, 2015
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
#include <ias/application/constants.h>
#include <ias/user/command/command_passwd.h>
#include <ias/util/util.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandPasswd::kIdentifier[] = "passwd";

// END Constants. ////////////////////////////////////////////////////

inline void CommandPasswd::initialize( void ) {
    mDbConnection = nullptr;
}

void CommandPasswd::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr && dbConnection->isConnected() );

    mDbConnection = dbConnection;
}

bool CommandPasswd::updatePassword( User * user, const std::string & passwd ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    std::string hashedPassword;
    std::string sql;
    bool success;

    // Checking the precondition.
    assert( user != nullptr && passwd.length() > 0 && passwd.length() <= 80 );

    success = false;
    hashedPassword = sha256GlobalSalts(passwd);
    sql = "UPDATE users "
          "SET password = " + hashedPassword +
          " WHERE id = " + std::to_string(user->getId());
    statement = mDbConnection->createStatement(sql);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            logi("Changing password of " + user->getUsername());
            user->setPassword(hashedPassword);
            success = true;
            delete result;
        }
    }

    return ( success );
}

CommandPasswd::CommandPasswd( DatabaseConnection * dbConnection ) :
    Command(kIdentifier) {
    initialize();
    setDatabaseConnection(dbConnection);
}

std::string CommandPasswd::execute( User * user,
                                    const std::string & parameters ) {
    std::string response;

    // Checking the precondition.
    assert( user != nullptr );

    if( !parameters.empty() && parameters.length() <= 80 &&
        updatePassword(user,parameters)) {
        response = kProtocolAck;
    } else {
        response = kProtocolNack;
    }

    return ( response );
}
