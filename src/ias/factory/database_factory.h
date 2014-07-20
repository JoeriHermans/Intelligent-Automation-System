/**
 * An abstract factory which is responsible for fetching instances from a
 * database.
 *
 * @date					Jul 5, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

#ifndef DATABASE_FACTORY_H_
#define DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/factory/factory.h>

// END Includes. /////////////////////////////////////////////////////

template<class T>
class DatabaseFactory : public Factory<T> {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the connection with the database.
     */
    DatabaseConnection * mDbConnection;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void setDbConnection( DatabaseConnection * connection ) {
        // Checking the precondition.
        assert( connection != nullptr && connection->isConnected() );
        
        mDbConnection = connection;
    }
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
    
    DatabaseConnection * getDbConnection( void ) const {
        return ( mDbConnection );
    }
    
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    DatabaseFactory( DatabaseConnection * connection ) {
        setDbConnection( connection );
    }
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~DatabaseFactory( void ) {
        // Nothing to do here.
    }
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* DATABASE_FACTORY_H_ */
