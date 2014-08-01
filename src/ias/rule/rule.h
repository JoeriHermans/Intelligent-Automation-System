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

#ifndef RULE_H_
#define RULE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>

// Application dependencies.
#include <ias/rule/rule_action.h>
#include <ias/rule/rule_condition_set.h>
#include <ias/util/observer.h>

// END Includes. /////////////////////////////////////////////////////

class Rule : public Observer {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the unique identifier of the rule.
     */
    std::size_t mId;
    
    /**
     * Contains the name of the rule.
     */
    std::string mName;
    
    /**
     * Contains the description of the rule.
     */
    std::string mDescription;
    
    /**
     * Contains all condition sets which need to be evaluated before
     * a action set can be executed.
     */
    std::vector<RuleConditionSet *> mConditions;
    
    /**
     * Contains all actions which need to be executed when a condition-set
     * has been positively evaluated.
     */
    std::vector<RuleAction *> mActions;
    
    /**
     * A boolean which indicates whether the rule can be enforced.
     * 
     * @note    By default, this member is true by default.
     */
    bool mEnforcing;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setId( const std::size_t id );
    
    void setName( const std::string & name );
    
    void setDescription( const std::string & description );
    
    void setConditions( const std::vector<RuleConditionSet *> & conditions );
    
    void setActions( const std::vector<RuleAction *> & actions );
    
    void unregister( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
        
    Rule( const std::size_t id, 
          const std::string & name,
          const std::vector<RuleConditionSet *> & conditions,
          const std::vector<RuleAction *> & actions );
    
    Rule( const std::size_t id, 
          const std::string & name, 
          const std::string & description,
          const std::vector<RuleConditionSet *> & conditions,
          const std::vector<RuleAction *> & actions );
        
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Rule( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    std::size_t getId( void ) const;
    
    const std::string & getName( void ) const;
    
    const std::string & getDescription( void ) const;
    
    void enforce( void );
    
    virtual void update( void );
    
    virtual void update( void * argument );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* RULE_H_ */
