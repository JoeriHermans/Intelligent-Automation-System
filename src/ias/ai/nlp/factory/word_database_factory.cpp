/**
 * A class which describes the properties and actions of a word database.
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
#include <ias/ai/nlp/factory/word_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void WordDatabaseFactory::setDictionaryId( const std::size_t id ) {
    // Checking the precondition.
    assert( id > 0 );
    
    mDictionaryId = id;
}

WordDatabaseFactory::WordDatabaseFactory( DatabaseConnection * dbConnection,
                                          const std::size_t dictionaryId ) :
    DatabaseFactory<std::string>(dbConnection) {
    setDictionaryId(dictionaryId);
}

WordDatabaseFactory::~WordDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<std::string> WordDatabaseFactory::fetchAll( void ) {
    std::vector<std::string> words;
    DatabaseStatement * statement;
    DatabaseResult * result;
    DatabaseResultRow * row;
    std::string query;
    
    query =
        "SELECT word "
        "FROM nlp_dictionary_contents "
        "WHERE dictionary_id = " + mDictionaryId;
    statement = getDbConnection()->createStatement(query);
    if( statement != nullptr ) {
        result = statement->execute();
        if( result != nullptr ) {
            while( result->hasNext() ) {
                row = result->next();
                words.push_back(row->getColumn(0));
                delete row;
            }
            delete result;
        }
        delete statement;
    }
    
    return ( words );
}
