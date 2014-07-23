/**
 * A class which describes the properties and actions of a sentence.
 *
 * @date					Jul 23, 2014
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

#ifndef SENTENCE_H_
#define SENTENCE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <vector>

// END Includes. /////////////////////////////////////////////////////

class Sentence {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
        
    std::vector<std::string> mEntities;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    void addEntity( const std::string & entity );
    
    void parse( const std::string & sentence );
        
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
        
    Sentence( const std::string & sentence );
        
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Sentence( void );
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    std::size_t numEntities( void ) const;
    
    const std::string & getEntity( const std::size_t index ) const;
    
    bool isWord( const std::size_t index ) const;
    
    bool isQuestion( void ) const;
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* SENTENCE_H_ */
