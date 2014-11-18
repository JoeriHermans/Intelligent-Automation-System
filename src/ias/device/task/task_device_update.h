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

#ifndef TASK_DEVICE_UPDATE_H_
#define TASK_DEVICE_UPDATE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/device/struct_device_update.h>
#include <ias/threadpool/task.h>

// END Includes. /////////////////////////////////////////////////////

class TaskDeviceUpdate : public Task {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the database connection we will be using.
     */
    DatabaseConnection * mDbConnection;

    /**
     * Contains the data which we need to write to the database.
     */
    struct device_update mData;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setDatabaseConnection( DatabaseConnection * connection );

    void setDeviceUpdateData( const struct device_update * data );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    TaskDeviceUpdate( DatabaseConnection * dbConnection,
                      const struct device_update * data );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~TaskDeviceUpdate( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void execute( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* TASK_DEVICE_UPDATE_H_ */
