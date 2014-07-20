/**
 * A class represents a persitent set of properties. A property contains a
 * key-value relation.
 *
 * @date					Jun 3, 2014
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

#ifndef PROPERTIES_H_
#define PROPERTIES_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <map>
#include <string>

// END Includes. /////////////////////////////////////////////////////

class Properties
{

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains all key-value properties.
     */
    std::map<std::string,std::string> mProperties;

	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    Properties( void );
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Properties( void );
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    void add( const std::string & key , const std::string & value );
    
    bool contains( const std::string & key ) const;
    
    const std::string & get( const std::string & key ) const;
    
    void clear( void );
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* PROPERTIES_H_ */
