/**
 * A class describing the properties and actions of a database
 * connection.
 *
 * @date                    Jul 21, 2013
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

#ifndef DATABASE_CONNECTION_H_
#define DATABASE_CONNECTION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <string>

// Application dependencies.
#include <ias/database/interface/database_statement.h>
#include <ias/database/interface/database_prepared_statement.h>

// END Includes. /////////////////////////////////////////////////////

class DatabaseConnection {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the username of the database connection.
     */
    std::string mUsername;

    /**
     * Contains the password of the database connection.
     */
    std::string mPassword;

    /**
     * Contains the name of the database we will be using.
     */
    std::string mSchema;

    /**
     * Contains the address of the database server.
     */
    std::string mHost;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    DatabaseConnection( const std::string & username,
                        const std::string & password,
                        const std::string & schema,
                        const std::string & host ) {
        mUsername = username;
        mPassword = password;
        mSchema = schema;
        mHost = host;
    }

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~DatabaseConnection( void ) {
        // Nothing to do here.
    }

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual const std::string & getUsername( void ) const {
        return ( mUsername );
    }

    virtual const std::string & getPassword( void ) const {
        return ( mPassword );
    }

    virtual const std::string & getSchema( void ) const {
        return ( mSchema );
    }

    virtual const std::string & getHost( void ) const {
        return ( mHost );
    }

    virtual bool isConnected( void ) const = 0;

    virtual bool connect( void ) = 0;

    virtual DatabaseStatement * createStatement( const std::string & sql ) = 0;

    virtual DatabasePreparedStatement * prepareStatement( 
        const std::string & sql ) = 0;

    virtual void * getLink( void ) = 0;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DATABASE_CONNECTION_H_ */
