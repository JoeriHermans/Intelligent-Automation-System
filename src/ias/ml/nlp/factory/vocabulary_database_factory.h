/**
 * A class which describes the properties and actions of a vocabulary database
 * factory. This factory is responsible for fetching the vocabulary of a
 * particular language from the database.
 *
 * @date                    5 April, 2015
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2015 Joeri HERMANS
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

#ifndef VOCABULARY_DATABASE_FACTORY_H_
#define VOCABULARY_DATABASE_FACTORY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/factory/database_factory.h>
#include <ias/ml/nlp/vocabulary.h>

// END Includes. /////////////////////////////////////////////////////

class VocabularyDatabaseFactory : public DatabaseFactory<Vocabulary *> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void buildVocabulary( const std::size_t id, Vocabulary * vocabulary );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    VocabularyDatabaseFactory( DatabaseConnection * connection );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~VocabularyDatabaseFactory( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::vector<Vocabulary *> fetchAll( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* VOCABULARY_DATABASE_FACTORY_H_ */
