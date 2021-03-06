/**
 * A set of utilization methods and functions.
 *
 * @date                    July 4, 2014
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <cstring>
#include <algorithm>
#include <functional>
#include <cctype>
#include <vector>
#include <locale>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <openssl/sha.h>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

bool flagSpecified( const int argc , const char ** argv , const char * flag ) {
    bool specified;

    // Checking the preconditions.
    assert( argc > 0 && argv != nullptr && flag != nullptr );

    specified = false;
    for( int i = 0 ; !specified && i < argc ; ++i ) {
        if( strcmp(argv[i],flag) == 0 )
            specified = true;
    }

    return ( specified );
}

int flagIndex( const int argc , const char ** argv , const char * flag ) {
    int index;

    // Checking the preconditions.
    assert( argc > 0 && argv != nullptr && flag != nullptr );

    index = -1;
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],flag) == 0 ) {
            index = i;
            break;
        }
    }

    return ( index );
}

std::string sha256( const std::string & str,
                    const std::string & presalt,
                    const std::string & postsalt ) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    char nhash[65];

    std::string hashed;
    std::string toHash;

    toHash = presalt + str + postsalt;
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256,toHash.c_str(),toHash.length());
    SHA256_Final(hash,&sha256);
    for( int i = 0 ; i < SHA256_DIGEST_LENGTH ; ++i ) {
        sprintf(nhash + (i * 2),"%02x",hash[i]);
    }
    nhash[64] = 0;
    hashed = nhash;

    return ( hashed );
}

std::string gSaltPre;
std::string gSaltPost;
std::string sha256GlobalSalts( const std::string & str ) {
    return ( sha256(str,gSaltPre,gSaltPost) );
}

bool isNumber( const std::string & s ) {
    return !s.empty() && std::find_if(s.begin(),s.end(),[](char c) {
                return !std::isdigit(c);
            }) == s.end();
}

void trim( std::string & s ) {
    s.erase(0, s.find_first_not_of(kTrimCharacters));
    s.erase(s.find_last_not_of(kTrimCharacters) + 1);
}

std::size_t numWords( const std::string & string ) {
    std::size_t n;

    n = 0;
    for( auto & it : string ) {
        if( it == ' ' )
            ++n;
    }
    if( string.length() > 0 )
        ++n;

    return ( n );
}

std::size_t editDistance( const std::string & a , const std::string & b )
{
    const std::size_t len1 = a.size(), len2 = b.size();
    std::vector<std::vector<std::size_t> > d(len1 + 1,
                            std::vector<std::size_t>(len2 + 1));

    d[0][0] = 0;
    for( std::size_t i = 1 ; i <= len1 ; ++i ) d[i][0] = i;
    for( std::size_t i = 1 ; i <= len2 ; ++i ) d[0][i] = i;
    for( std::size_t i = 1 ; i <= len1 ; ++i )
        for( std::size_t j = 1 ; j <= len2 ; ++j )
            d[i][j] = std::min(std::min(
                d[i - 1][j] + 1,d[i][j - 1] + 1),
                d[i - 1][j - 1] + (a[i - 1] == b[j - 1] ? 0 : 1) );

    return ( d[len1][len2] );
}
