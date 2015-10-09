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

#ifndef HASH_GENERATION_HASH_GENERATION_APPLICATION_H_
#define HASH_GENERATION_HASH_GENERATION_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/application/application.h>
#include <ias/util/properties.h>

// END Includes. /////////////////////////////////////////////////////

class HashGenerationApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the string that needs to be hashed.
     *
     * @note    By default, this string will be empty.
     */
    std::string mData;

    /**
     * Properties which  have been read from the specified configuration file.
     *
     * @note    By default, this properties map will be empty.
     */
    Properties mProperties;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void analyzeArguments( const int argc , const char ** argv );

    std::string readConfigurationPath( const int argc,
                                       const char ** argv ) const;

    void readConfiguration( const std::string & path );

    void setData( const int argc , const char ** argv );

    void initializeSalts( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    HashGenerationApplication( const int argc , const char ** argv );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~HashGenerationApplication( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* HASH_GENERATION_HASH_GENERATION_APPLICATION_H_ */
