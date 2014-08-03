/**
 * A database factory which is responsible for extracting rules from a
 * database.
 *
 * @date                    Jul 21, 2014
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
#include <ias/database/interface/database_statement.h>
#include <ias/database/interface/database_result.h>
#include <ias/database/interface/database_result_row.h>
#include <ias/rule/factory/rule_database_factory.h>
#include <ias/rule/rule_condition_static.h>
#include <ias/rule/rule_condition_dynamic.h>

// END Includes. /////////////////////////////////////////////////////

void RuleDatabaseFactory::setDeviceContainer( const Container<Device *> * devices ) {
    // Checking the preconditions.
    assert( devices != nullptr );
    
    mDeviceContainer = devices;
}

void RuleDatabaseFactory::setOperators( const std::map<std::string,Operator *> * op ) {
    // Checking the precondition.
    assert( op != nullptr );
    
    mOperators = op;
}

std::vector<RuleConditionSet *> RuleDatabaseFactory::fetchConditionSets( 
    const std::size_t id ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<RuleConditionSet *> conditionSets;
    std::string query;
    std::size_t conditionSetId;
    
    query =
        "SELECT id "
        "FROM rule_condition_sets "
        "WHERE rule_id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::vector<RuleCondition *> conditions;
                
                row = result->next();
                conditionSetId = (std::size_t) atol(row->getColumn(0).c_str());
                conditions = fetchConditions(conditionSetId);
                conditionSets.push_back(new RuleConditionSet(conditions));
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( conditionSets );
}

bool RuleDatabaseFactory::deviceRegistered( Device * d ) const {
    bool result;
    
    // Checking the precondition.
    assert( d != nullptr );
    
    if( std::find(mRuleDevices.begin(),mRuleDevices.end(),d) 
        != mRuleDevices.end() )
        result = true;
    else
        result = false;
    
    return ( result );
}

std::vector<RuleCondition *> RuleDatabaseFactory::fetchConditions( 
    const std::size_t id ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<RuleCondition *> conditions;
    std::string query;
    
    query =
        "SELECT * "
        "FROM rule_conditions "
        "WHERE rule_condition_set_id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::size_t deviceId;
                std::size_t referencedDeviceId;
                std::string member;
                std::string value;
                std::string referencedMember;
                RuleCondition * condition;
                Operator * op;
                Device * d1;
                Device * d2;
                
                row = result->next();
                deviceId = (std::size_t) atol(row->getColumn(2).c_str());
                op = fetchOperator(row->getColumn(3));
                member = row->getColumn(4);
                value = row->getColumn(5);
                d1 = mDeviceContainer->get(deviceId);
                if( !deviceRegistered(d1) )
                    mRuleDevices.push_back(d1);
                if( value.length() > 0 ) {
                    condition = new RuleConditionStatic(d1,member,value,op);
                } else {
                    referencedDeviceId =
                        (std::size_t) atol(row->getColumn(6).c_str());
                    referencedMember = row->getColumn(7);
                    d2 = mDeviceContainer->get(referencedDeviceId);
                    if( !deviceRegistered(d2) )
                        mRuleDevices.push_back(d2);
                    condition = new RuleConditionDynamic(d1,member,d2,
                                                         referencedMember,op);
                }
                conditions.push_back(condition);
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( conditions );
}

std::vector<RuleAction *> RuleDatabaseFactory::fetchActions( const std::size_t id ) {
    std::vector<RuleAction *> actions;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string query;
    
    query =
        "SELECT * "
        "FROM rule_actions "
        "WHERE rule_id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::size_t deviceId;
                std::string deviceFeature;
                std::string deviceParameter;
                Device * d;
                
                row = result->next();
                deviceId = (std::size_t) atol(row->getColumn(2).c_str());
                deviceFeature = row->getColumn(3);
                deviceParameter = row->getColumn(4);
                d = mDeviceContainer->get(deviceId);
                if( d != nullptr ) {
                    actions.push_back(
                        new RuleAction(d,
                            new Action(deviceFeature,deviceParameter))
                    );
                }
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( actions );
}

Operator * RuleDatabaseFactory::fetchOperator( 
    const std::string & identifier ) const {
    Operator * op;
    
    auto it = mOperators->find(identifier);
    if( it != mOperators->end() ) {
        op = it->second;
    } else {
        op = nullptr;
    }
    
    return ( op );
}

void RuleDatabaseFactory::registerRule( Rule * r ) {
    // Checking the precondition.
    assert( r != nullptr );
    
    for( Device * d : mRuleDevices )
        d->addObserver(r);
    mRuleDevices.clear();
}

RuleDatabaseFactory::RuleDatabaseFactory( 
    DatabaseConnection * dbConnection,
    const Container<Device *> * devices,
    const std::map<std::string,Operator *> * operators ) :
    DatabaseFactory<Rule *>(dbConnection) {
    setDeviceContainer(devices);
    setOperators(operators);
}

RuleDatabaseFactory::~RuleDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Rule *> RuleDatabaseFactory::fetchAll( void ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::vector<Rule *> rules;
    std::size_t id;
    std::string name;
    std::string description;
    Rule * rule;
    
    statement = getDbConnection()->createStatement(
        "SELECT * "
        "FROM rules;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                std::vector<RuleConditionSet *> sets;
                std::vector<RuleAction *> actions;
                
                row = result->next();
                id = (std::size_t) atol(row->getColumn(0).c_str());
                name = row->getColumn(1);
                description = row->getColumn(2);
                sets = fetchConditionSets(id);
                actions = fetchActions(id);
                rule = new Rule(id,name,description,sets,actions);
                registerRule(rule);
                rules.push_back(rule);
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( rules );
}

Rule * RuleDatabaseFactory::fetch( const std::size_t id ) {
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string query;
    Rule * rule;

    // Checking the precondition.
    assert( id > 0 );

    query =
            "SELECT * "
            "FROM rules "
            "WHERE id = " + std::to_string(id);
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            if( result->hasNext() ) {
                std::string name;
                std::string description;
                std::vector<RuleConditionSet *> sets;
                std::vector<RuleAction *> actions;

                row = result->next();
                name = row->getColumn(1);
                description = row->getColumn(2);
                sets = fetchConditionSets(id);
                actions = fetchActions(id);
                rule = new Rule(id,name,description,sets,actions);
                registerRule(rule);
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( rule );
}
