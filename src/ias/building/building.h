/**
 * A class which describes the properties and actions of a building.
 *
 * @date                    Jul 24, 2014
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

#ifndef BUILDING_H_
#define BUILDING_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/building/area.h>
#include <ias/util/identifiable.h>

// END Includes. /////////////////////////////////////////////////////

class Building {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the unique id of a device.
     */
    std::size_t mId;
    
    /**
     * Contains the unique identifier of a device.
     */
    std::string mIdentifier;
    
    /**
     * Contains the name of the device.
     */
    std::string mName;
    
    /**
     * Contains the description of the device.
     */
    std::string mDescription;
    
    /**
     * Contains mutexes for the editing of class members.
     */
    mutable std::mutex mMutexIdentifier;
    mutable std::mutex mMutexName;
    mutable std::mutex mMutexDescription;
    
    /**
     * Contains all areas in a building.
     */
    std::vector<Area *> mAreas;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setId( const std::size_t id );
    
    void setAreas( const std::vector<Area *> & areas );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    Building( const std::size_t id,
              const std::string & identifier,
              const std::string & name,
              const std::string & description,
              const std::vector<Area *> & areas );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Building( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
        
    std::size_t getId( void ) const;
    
    const std::string & getIdentifier( void ) const;
    
    void setIdentifier( const std::string & identifier );
    
    const std::string & getName( void ) const;
    
    void setName( const std::string & name );
    
    const std::string & getDescription( void ) const;
    
    bool hasDescription( void ) const;
    
    void setDescription( const std::string & description );
    
    std::size_t numAreas( void ) const;
    
    const std::vector<Area *> & getAreas( void ) const;
        
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* BUILDING_H_ */
