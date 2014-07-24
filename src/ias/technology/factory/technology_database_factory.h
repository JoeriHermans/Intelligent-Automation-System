/**
 * A class which is responsible for extracting technologies from a database.
 *
 * @date                    Jul 5, 2014
 * @author                    Joeri HERMANS
 * @version                    0.1
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

#ifndef TECHNOLOGY_DATABASE_FACTORY_H_
#define TECHNOLOGY_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/factory/database_factory.h>
#include <ias/technology/technology.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class TechnologyDatabaseFactory : public DatabaseFactory<Technology *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * Containers which hold the value types and members which need to
     * be associated with a certain technology.
     */
    Container<Feature *> * mFeaturesContainer;
    Container<Member *> * mMembersContainer;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setContainers( Container<Member *> * members,
                        Container<Feature *> * features );
    
    std::vector<Feature *> fetchFeatures( const std::size_t id ) const;
    
    std::vector<Member *> fetchMembers( const std::size_t id ) const;
    
    Technology * allocateTechnology( const std::string & id,
                                     const std::string & identifer,
                                     const std::string & name,
                                     const std::string & description ) const;
        
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    TechnologyDatabaseFactory( DatabaseConnection * connection,
                               Container<Member *> * members,
                               Container<Feature *> * features );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~TechnologyDatabaseFactory( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    std::vector<Technology *> fetchAll( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* TECHNOLOGY_DATABASE_FACTORY_H_ */
