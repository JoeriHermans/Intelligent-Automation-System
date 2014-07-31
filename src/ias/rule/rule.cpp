/**
 * A class which describes the actions and properties of a rule.
 *
 * @date                    Jul 31, 2014
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

// Application dependencies.
#include <ias/rule/rule.h>

// END Includes. /////////////////////////////////////////////////////

void Rule::setId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mId = id;
}

void Rule::setName( const std::string & name ) {
    // Checking the precondition.
    assert( name.length() > 0 );
    
    mName = name;
}

void Rule::setDescription( const std::string & description ) {
    mDescription = description;
}

void Rule::setConditions( const std::vector<RuleConditionSet *> & conditions ) {
    // Checking the precondition.
    assert( conditions.size() > 0 );
    
    mConditions = conditions;
}

void Rule::setActions( const std::vector<RuleAction *> & actions ) {
    // Checking the precondition.
    assert( actions.size() > 0 );
    
    mActions = actions;
}

Rule::Rule( const std::size_t id,
            const std::string & name,
            const std::vector<RuleConditionSet *> & conditions,
            const std::vector<RuleAction *> & actions ) {
    setId(id);
    setName(name);
    setConditions(conditions);
    setActions(actions);
}

Rule::Rule( const std::size_t id,
            const std::string & name,
            const std::string & description,
            const std::vector<RuleConditionSet *> & conditions,
            const std::vector<RuleAction *> & actions ) {
    setId(id);
    setName(name);
    setDescription(description);
    setConditions(conditions);
    setActions(actions);
}

Rule::~Rule( void ) {
    // Free the allocated conditions.
    for( auto conditionSet : mConditions )
        delete conditionSet;
    // Free the allocated actions.
    for( auto action : mActions )
        delete action;
}

std::size_t Rule::getId( void ) const {
    return ( mId );
}

const std::string & Rule::getName( void ) const {
    return ( mName );
}

const std::string & Rule::getDescription( void ) const {
    return ( mDescription );
}

void Rule::enforce( void ) {
    bool conditionMet;

    conditionMet = false;
    for( auto it = mConditions.begin(); 
        it != mConditions.end() && !conditionMet ; ++it ) {
        conditionMet |= (*it)->evaluate();
    }
    if( conditionMet ) {
        for( auto action : mActions )
            action->execute();
    }
}

void Rule::update( void ) {
    enforce();
}

void Rule::update( void * argument ) {
    enforce();
}
