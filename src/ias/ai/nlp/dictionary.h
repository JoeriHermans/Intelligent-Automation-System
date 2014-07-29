/**
 * A class which describes the properties and actions of a dictionary. A
 * dictionary is responsible for storing a large set of words and the associated
 * indices.
 *
 * @date                    Jul 28, 2014
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

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <mutex>
#include <unordered_map>

// END Includes. /////////////////////////////////////////////////////

class Dictionary {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
    
    /**
     * Contains the normalized words which are available to this dictionary
     * together with their associated index.
     */
    std::unordered_map<std::string,std::size_t> mWords;
    
    /**
     * Contains the value of the next index for the new word.
     */
    std::size_t mNextIndex;
    
    /**
     * A flag which indicates that words can be added to the dictionary.
     */
    bool mLock;
    
    /**
     * Contains the mutex which is responsible for thread-safe operations.
     */
    mutable std::mutex mMutexStorage;
    
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    Dictionary( void );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Dictionary( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    void add( const std::string & word );
    
    bool contains( const std::string & word ) const;
    
    void lock( void );
    
    void unlock( void );
    
    bool locked( void ) const;
    
    std::size_t index( const std::string & word ) const;
    
    std::size_t size( void ) const;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DICTIONARY_H_ */
