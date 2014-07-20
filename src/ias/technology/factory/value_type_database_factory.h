/**
 * A value type factory which fetches value type instances from
 * a database.
 *
 * @date					Jul 4, 2014
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

#ifndef VALUE_TYPE_DATABASE_FACTORY_H_
#define VALUE_TYPE_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/technology/value_type.h>
#include <ias/factory/database_factory.h>
#include <ias/database/interface/database_connection.h>

// END Includes. /////////////////////////////////////////////////////

class ValueTypeDatabaseFactory : public DatabaseFactory<ValueType *> {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
    // END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
	
    ValueTypeDatabaseFactory( DatabaseConnection * connection );
    
    // END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ValueTypeDatabaseFactory( void );
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
	
    virtual std::vector<ValueType *> fetchAll( void );
    
    // END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* VALUE_TYPE_DATABASE_FACTORY_H_ */
