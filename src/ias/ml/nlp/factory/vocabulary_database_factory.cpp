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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <vector>

// Application dependencies.
#include <ias/ml/nlp/factory/vocabulary_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void VocabularyDatabaseFactory::buildVocabulary( const std::size_t id,
                                                 Vocabulary * vocabulary ) {
    // Checking the precondition.
    assert( id > 0 && vocabulary != nullptr );

    // TODO Implement.
}

VocabularyDatabaseFactory::VocabularyDatabaseFactory(
    DatabaseConnection * connection ) :
    DatabaseFactory(connection) {
    // Nothing to do here.
}

std::vector<Vocabulary *> VocabularyDatabaseFactory::fetchAll( void ) {
    std::vector<Vocabulary *> vocabularies;
    Vocabulary * vocabulary;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::size_t id;

    statement = getDbConnection()->createStatement(
        "SELECT id "
        "FROM vocabularies;"
    );
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                id = static_cast<std::size_t>(atol(row->getColumn(0).c_str()));
                vocabulary = new Vocabulary();
                buildVocabulary(id,vocabulary);
                delete row;
            }
            delete result;
        }
        delete statement;
    }

    return ( vocabularies );
}
