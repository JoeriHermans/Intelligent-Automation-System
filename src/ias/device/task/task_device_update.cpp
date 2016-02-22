/**
 * A task which is responsible for updating the state of a device in a
 * database.
 *
 * @date                    Aug 1, 2014
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
#include <string>

// Application dependencies.
#include <ias/device/task/task_device_update.h>

// END Includes. /////////////////////////////////////////////////////

void TaskDeviceUpdate::setDatabaseConnection( DatabaseConnection * dbConn ) {
    // Checking the precondition.
    assert( dbConn != nullptr && dbConn->isConnected() );

    mDbConnection = dbConn;
}

void TaskDeviceUpdate::setDeviceUpdateData( const struct device_update * d ) {
    // Checking the precondition.
    assert( d != nullptr );

    mData.mDevice = d->mDevice;
    mData.mStateIdentifier = d->mStateIdentifier;
    mData.mValue = d->mValue;
    mData.mTimestamp = d->mTimestamp;
}

TaskDeviceUpdate::TaskDeviceUpdate( DatabaseConnection * dbConnection,
                                    const struct device_update * data ) {
    setDatabaseConnection(dbConnection);
    setDeviceUpdateData(data);
}

TaskDeviceUpdate::~TaskDeviceUpdate( void ) {
    // Nothing to do here.
}

void TaskDeviceUpdate::execute( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    std::string query;

    query =
        "INSERT INTO device_history_states "
        "(device_id,technology_member_id,timestamp,value) "
        "VALUES (" +
            std::to_string(mData.mDevice->getId()) + "," +
            "" + std::to_string(mData.mMemberId) + "," +
            std::to_string(mData.mTimestamp) + "," +
            "\"" + mData.mValue + "\")";
    statement = mDbConnection->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr )
            delete result;
        delete statement;
    }
}
