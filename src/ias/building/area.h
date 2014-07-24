/**
 * A class which describes the properties and actions of an area.
 *
 * @date					Jul 24, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

#ifndef AREA_H_
#define AREA_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <vector>
#include <map>

// Application dependencies.
#include <ias/device/device.h>
#include <ias/util/identifiable.h>

// END Includes. /////////////////////////////////////////////////////

class Area : public Identifiable {

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
     * A hashmap which hold all devices which are related to this area.
     */
    std::map<std::string,Device *> mDevices;
    
    /**
     * A vector which holds all adjacent areas.
     */
    std::vector<Area *> mAreas;
    
    /**
     * Contains mutexes for the editing of class members.
     */
    mutable std::mutex mMutexIdentifier;
    mutable std::mutex mMutexName;
    mutable std::mutex mMutexDescription;
    mutable std::mutex mMutexDevices;
    mutable std::mutex mMutexAreas;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
        
    inline void intialize( void );
    
    void setId( const std::size_t id );
    
    void setDevices( const std::vector<Device *> & devices );
        
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
        
    Area( const std::size_t id,
          const std::string & identifier,
          const std::string & name,
          const std::string & description );
    
    Area( const std::size_t id,
          const std::string & identifier,
          const std::string & name,
          const std::string & description,
          const std::vector<Device *> & devices );
    
    Area( const std::size_t id,
          const std::string & identifier,
          const std::string & name,
          const std::string & description,
          const std::vector<Device *> & devices,
          const std::vector<Area *> & areas );
        
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
        
    virtual ~Area( void );
        
	// END Destructor. ///////////////////////////////////////////////

	// BEGIN Public methods. /////////////////////////////////////////
        
    virtual std::size_t getId( void ) const;
    
    virtual const std::string & getIdentifier( void ) const;
    
    virtual void setIdentifier( const std::string & identifier );
    
    virtual const std::string & getName( void ) const;
    
    virtual void setName( const std::string & name );
    
    virtual const std::string & getDescription( void ) const;
    
    virtual bool hasDescription( void ) const;
    
    virtual void setDescription( const std::string & description );
    
    bool containsDevice( const std::string & identifier ) const;
    
    bool containsDevice( const std::size_t id ) const;
    
    Device * getDevice( const std::string & identifier ) const;
    
    Device * getDevice( const std::size_t id ) const;
    
    void removeDevice( const Device * device );
    
    std::vector<Device *> getDevices( void ) const;
    
    std::size_t numDevices( void ) const;
    
    bool containsAdjacentArea( const std::string & identifier ) const;
    
    bool containsAdjacentArea( const std::size_t id ) const;
    
    Area * getAdjacentArea( const std::string & identifier ) const;
    
    Area * getAdjacentArea( const std::size_t id ) const;
    
    void removeAdjacentArea( const Area * area );
    
    std::vector<Area *> getAdjacentAreas( void ) const;
    
    std::size_t numAdjacentAreas( void ) const;

	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* AREA_H_ */
