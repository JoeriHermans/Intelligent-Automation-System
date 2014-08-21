/**
 * A class which describes the properties and actions of a PostgreSQL
 * database result.
 *
 * @date                    August 21, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2014 Joeri HERMANS
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
#include <cstdio>

// Application dependencies.
#include <ias/database/postgresql/postgresql_result.h>
#include <ias/database/postgresql/postgresql_result_row.h>

// END Includes. /////////////////////////////////////////////////////

void PostgresqlResult::setResult( pqxx::result * result ) {
    // Checking the precondition.
    assert( result != nullptr );

    mResult = result;
    mIterator = mResult->begin();
}

PostgresqlResult::PostgresqlResult( pqxx::result * result ) {
    setResult(result);
}

PostgresqlResult::~PostgresqlResult( void ) {
    delete mResult; mResult = nullptr;
}

bool PostgresqlResult::hasNext( void ) {
    return ( mIterator != mResult->end() );
}

DatabaseResultRow * PostgresqlResult::next( void ) {
    DatabaseResultRow * row;

    row = new PostgresqlResultRow(mIterator++);

    return ( row );
}
