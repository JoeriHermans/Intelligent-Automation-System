/**
 * A class which describes the actions and properties of a natural language
 * processor. The processor will take a raw string and analyze it for actions,
 * queries, ...
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/ai/nlp/natural_language_processor.h>

// END Includes. /////////////////////////////////////////////////////

inline void NaturalLanguageProcessor::initialize( void ) {
    mDevices = nullptr;
    mUsers = nullptr;
}

void NaturalLanguageProcessor::setDeviceContainer( Container<Device *> * devs ) {
    // Checking the precondition.
    assert( devs != nullptr );
    
    mDevices = devs;
}

void NaturalLanguageProcessor::setUserContainer( Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );
    
    mUsers = users;
}

NaturalLanguageProcessor::NaturalLanguageProcessor( 
    Container<Device *> * devices,
    Container<User *> * users ) {
    initialize();
    setDeviceContainer(devices);
    setUserContainer(users);
}

NaturalLanguageProcessor::~NaturalLanguageProcessor( void ) {
    // Nothing to do here.
}

void NaturalLanguageProcessor::process( const std::string & raw ) {
    Sentence sentence(raw);
    
    // TODO Implement.
}
