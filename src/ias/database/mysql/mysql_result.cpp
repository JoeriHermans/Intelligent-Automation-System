/**
 * A class which describes the actions and properties of a MySQL result.
 *
 * @date                    Jul 22, 2013
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
#include <assert.h>
#include <stdio.h>
#include <string.h>

// Application dependencies.
#include <ias/database/interface/database_result.h>
#include <ias/database/mysql/mysql_result.h>
#include <ias/database/mysql/mysql_result_row.h>

// END Includes. /////////////////////////////////////////////////////

inline void MySqlResult::initialize( void ) {
    mResultSet = nullptr;
    mNextRow = nullptr;
}

inline void MySqlResult::setResultSet( MYSQL_RES * resultSet ) {
    mResultSet = resultSet;
}

MySqlResult::MySqlResult( MYSQL_RES * resultSet ) {
    initialize();
    setResultSet( resultSet );
}

MySqlResult::~MySqlResult( void ) {
    if( mResultSet != nullptr )
        mysql_free_result( mResultSet );
}

bool MySqlResult::hasNext( void ) {
    bool hasNext;

    hasNext = false;
    if( mResultSet != nullptr )
    {
        if( mNextRow != nullptr )
        {
            hasNext = true;
        }
        else
        {
            mNextRow = mysql_fetch_row( mResultSet );
            if( mNextRow != nullptr )
                hasNext = true;
        }
    }


    return ( hasNext );
}

DatabaseResultRow * MySqlResult::next( void ) {
    MySqlResultRow * row;
    std::size_t numColumns;

    row = nullptr;
    // Check if a result is available.
    if( hasNext() )
    {
        // Count the number of columns.
        numColumns = mysql_num_fields(mResultSet);
        // Allocate an instance.
        row = new MySqlResultRow(numColumns,mNextRow);
        // Reset the local row.
        memset(&mNextRow,0,sizeof mNextRow);
    }

    return ( row );
}
