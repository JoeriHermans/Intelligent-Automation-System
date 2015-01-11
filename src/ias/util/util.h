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

#ifndef UTIL_H_
#define UTIL_H_

// BEGIN Includes. ///////////////////////////////////////////////////
// END Includes. /////////////////////////////////////////////////////

bool flagSpecified( const int argc , const char ** argv , const char * flag );

int flagIndex( const int argc , const char ** argv , const char * flag );

std::string sha256( const std::string & str,
                    const std::string & presalt,
                    const std::string & postsalt );

extern std::string gSaltPre;
extern std::string gSaltPost;
std::string sha256GlobalSalts( const std::string & str );

bool isNumber( const std::string & s );

void trim( std::string & s );

std::size_t numWords( const std::string & string );

std::size_t editDistance( const std::string & a , const std::string & b );

#endif /* UTIL_H_ */
