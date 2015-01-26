/**
 * A command which is responsible for loading a rule into IAS.
 *
 * @date                    Aug 3, 2014
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
#include <cstdlib>
#include <iostream>

// Application dependencies.
#include <ias/rule/factory/rule_database_factory.h>
#include <ias/application/constants.h>
#include <ias/user/command/command_load_rule.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandLoadRule::kIdentifier[] = "lrule";

// END Constants. ////////////////////////////////////////////////////

void CommandLoadRule::setDbConnection( DatabaseConnection * connection ) {
    // Checking the precondition.
    assert( connection != nullptr && connection->isConnected() );

    mDbConnection = connection;
}

void CommandLoadRule::setDeviceContainer( const Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

void CommandLoadRule::setRuleContainer( Container<Rule *> * rules ) {
    // Checking the precondition.
    assert( rules != nullptr );

    mRules = rules;
}

void CommandLoadRule::setOperators( const std::map<std::string,Operator *> * operators ) {
    // Checking the precondition.
    assert( operators != nullptr );

    mOperators = operators;
}

Rule * CommandLoadRule::fetchRule( const std::size_t id ) {
    RuleDatabaseFactory factory(mDbConnection,mDevices,mOperators);
    Rule * rule;

    // Checking the precondition.
    assert( id > 0 );

    rule = factory.fetch(id);

    return ( rule );
}

CommandLoadRule::CommandLoadRule( DatabaseConnection * dbConnection,
                                  const Container<Device *> * devices,
                                  Container<Rule *> * rules,
                                  const std::map<std::string,Operator *> * operators ) :
    Command(kIdentifier) {
    setDbConnection(dbConnection);
    setDeviceContainer(devices);
    setRuleContainer(rules);
    setOperators(operators);
}

CommandLoadRule::~CommandLoadRule( void ) {
    // Nothing to do here.
}

std::string CommandLoadRule::execute( User * user,
                                      const std::string & parameters ) {
    std::string response;
    std::size_t ruleId;
    Rule * rule;
    bool success;

    // Checking the precondition.
    assert( user != nullptr );

    success = false;
    if( parameters.length() > 0 ) {
       ruleId = static_cast<std::size_t>(atol(parameters.c_str()));
       if( ruleId > 0 ) {
           rule = mRules->get(ruleId);
           if( rule == nullptr && (rule = fetchRule(ruleId)) != nullptr ) {
               mRules->add(rule);
               success = true;
           }
       }
    }
    if( success )
        response = kProtocolAck;
    else
        response = kProtocolNack;

    return ( response );
}
