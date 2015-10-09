/**
 * An application which is responsible for generating hashes according to
 * the specifications in the configuration file.
 *
 * @date                    9 September, 2015
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
#include <cstring>
#include <iostream>
#include <fstream>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/hash_generation/hash_generation_application.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

void HashGenerationApplication::analyzeArguments( const int argc,
                                                  const char ** argv ) {
    std::string configurationPath;

    // Checking the preconditions.
    assert( argc > 0 && argv != nullptr );

    setData(argc,argv);
    configurationPath = readConfigurationPath(argc,argv);
    if( !configurationPath.empty() )
        readConfiguration(configurationPath);
}

void HashGenerationApplication::setData( const int argc , const char ** argv ) {
    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagGenerateHash) == 0 &&
            (i - 1) < argc ) {
            mData = argv[i + 1];
            break;
        }
    }
}

std::string HashGenerationApplication::readConfigurationPath( const int argc,
                                                              const char ** argv ) const {
    std::string path;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    // Retrieve the path from the configuration file.
    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagConfig) == 0 &&
            (i - 1) < argc) {
            path = argv[i + 1];
        }
    }

    return path;
}

void HashGenerationApplication::readConfiguration( const std::string & path ) {
    std::ifstream file(path);
    std::string line;
    std::string key;
    std::string value;
    std::size_t i;

    // Checking the precondition.
    assert( !path.empty() );

    while( std::getline(file,line) ) {
        trim(line);
        if( line.empty() || line.at(0) == '#' )
            continue;
        i = line.find('=');
        key = line.substr(0,i);
        value = line.substr(i + 1,line.length());
        trim(key); trim(value);
        if( !key.empty() && !value.empty() )
            mProperties.add(key,value);
    }
    file.close();
}

void HashGenerationApplication::initializeSalts( void ) {
    std::string preSalt;
    std::string postSalt;

    if( mProperties.contains(kConfigPreSalt) )
        preSalt = mProperties.get(kConfigPreSalt);
    if( mProperties.contains(kConfigPostSalt) )
        postSalt = mProperties.get(kConfigPostSalt);
    gSaltPre = preSalt;
    gSaltPost = postSalt;
}

HashGenerationApplication::HashGenerationApplication( const int argc,
                                                      const char ** argv ) {
    analyzeArguments(argc,argv);
    initializeSalts();
}

HashGenerationApplication::~HashGenerationApplication( void ) {
    // Nothing to do here.
}

void HashGenerationApplication::run( void ) {
    std::string hashed;

    // Check if data is available.
    if( !mData.empty() ) {
        hashed = sha256GlobalSalts(mData);
        std::cout << hashed << std::endl;
    }
}

void HashGenerationApplication::stop( void ) {
    // Nothing to do here.
}
