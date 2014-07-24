/**
 * A class which describes the properties and actions of a say command.
 * IAS's NLP engine will process the string and execute a set of actions
 * based on the probability distributions which have been derrived from
 * the specified string.
 *
 * @date					Jul 20, 2014
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

#ifndef COMMAND_SAY_H_
#define COMMAND_SAY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/ai/nlp/natural_language_processor.h>
#include <ias/user/command/command.h>

// END Includes. /////////////////////////////////////////////////////

class CommandSay : public Command {

	public:

	// BEGIN Class constants. ////////////////////////////////////////
        
    static const char kIdentifier[];
        
	// END Class constants. //////////////////////////////////////////

	private:

	// BEGIN Private members. ////////////////////////////////////////
	
    /**
     * A pointer to the IAS natural language processor.
     */
    NaturalLanguageProcessor * mProcessor;
    
    // END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    CommandSay( NaturalLanguageProcessor * p );
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~CommandSay( void );
    
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
    
    virtual std::string execute( const std::string & parameters );
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* COMMAND_SAY_H_ */
