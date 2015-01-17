/**
 * A class which describes the properties and actions of a user server. A
 * user servers allows for users to connect and execute commands remotely.
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

#ifndef USER_SERVER_H_
#define USER_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <thread>
#include <utility>
#include <map>
#include <mutex>

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/server/session/session.h>
#include <ias/user/user.h>
#include <ias/user/command/command_dispatcher.h>
#include <ias/util/container.h>
#include <ias/server/session_server.h>

// END Includes. /////////////////////////////////////////////////////

class UserServer : public SessionServer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A containers which holds the set of all users available in
     * IAS.
     */
    Container<User *> * mUsers;

    /**
     * Contains the database connection which will be used to check the
     * user credentials of incoming connections.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    DatabaseConnection * mDbConnection;

    /**
     * A class which is responsible for dispatching user commands.
     */
    CommandDispatcher * mDispatcher;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setUserContainer( Container<User *> * users );

    void setDispatcher( CommandDispatcher * dispatcher );

    void setDatabaseConnection( DatabaseConnection * dbConnection );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    virtual Session * getSession( Socket * socket ) const;

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    UserServer( ServerSocket * serverSocket,
                Container<User *> * users,
                CommandDispatcher * dispatcher,
                DatabaseConnection * dbConnection );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~UserServer( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void join( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* USER_SERVER_H_ */
