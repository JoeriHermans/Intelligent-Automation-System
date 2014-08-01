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

#ifndef RULE_DATABASE_FACTORY_H_
#define RULE_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <map>

// Application dependencies.
#include <ias/device/device.h>
#include <ias/factory/database_factory.h>
#include <ias/rule/rule.h>
#include <ias/operator/operator.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class RuleDatabaseFactory : public DatabaseFactory<Rule *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * A container which contains all devices which are known to IAS.
     */
    Container<Device *> * mDeviceContainer;
    
    /**
     * Contains the operator map.
     */
    std::map<std::string,Operator *> * mOperators;
    
    /**
     * Contains the temporary device buffer which contains the devices
     * which we need to observe.
     */
    std::vector<Device *> mRuleDevices;
    
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setDeviceContainer( Container<Device *> * devices );
    
    void setOperators( std::map<std::string,Operator *> * operators );
    
    std::vector<RuleConditionSet *> fetchConditionSets( const std::size_t id );
    
    std::vector<RuleCondition *> fetchConditions( const std::size_t id );
    
    std::vector<RuleAction *> fetchActions( const std::size_t id );
    
    Operator * fetchOperator( const std::string & identifier ) const;
    
    bool deviceRegistered( Device * d ) const;
    
    void registerRule( Rule * r );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    RuleDatabaseFactory( DatabaseConnection * dbConnection,
                         Container<Device *> * devices,
                         std::map<std::string,Operator *> * operators );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~RuleDatabaseFactory( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual std::vector<Rule *> fetchAll( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_DATABASE_FACTORY_H_ */
