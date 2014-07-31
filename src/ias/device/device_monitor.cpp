/**
 * A class which describes the actions and properties of a device monitor. A
 * device monitor is responsible for monitoring changes in the state of
 * registered devices and reporting that with a certain task.
 *
 * @date                    Jul 31, 2014
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
#include <ctime>

// Application dependencies.
#include <ias/database/interface/database_result.h>
#include <ias/database/interface/database_statement.h>
#include <ias/device/device_monitor.h>
#include <ias/device/struct_device_update.h>

// END Includes. /////////////////////////////////////////////////////

void DeviceMonitor::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr && dbConnection->isConnected() );
    
    mDbConnection = dbConnection;
}

DeviceMonitor::DeviceMonitor( DatabaseConnection * dbConnection ) {
    setDatabaseConnection(dbConnection);
}

DeviceMonitor::~DeviceMonitor( void ) {
    // Nothing to do here.
}

void DeviceMonitor::update( void ) {
    // Nothing to do here.
}

void DeviceMonitor::update( void * argument ) {
    struct device_update * dUpdate;
    DatabaseStatement * statement;
    DatabaseResult * result;
    std::string query;
    
    // Checking the precondition.
    assert( argument != nullptr );
    
    dUpdate = (struct device_update *) argument;
    query =
        "INSERT INTO device_history_states "
        "(device_id,technology_member,timestamp,value) "
        "VALUES (" + 
            std::to_string(dUpdate->mDevice->getId()) + "," +
            "\"" + dUpdate->mStateIdentifier + "\"," +
            std::to_string(std::time(nullptr)) + "," +
            "\"" + dUpdate->mValue + "\")";
    statement = mDbConnection->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr )
            delete result;
    }
}
