/**
 * A class which described the properties and actions of a device.
 *
 * @date					Jul 3, 2014
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

#ifndef DEVICE_H_
#define DEVICE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mutex>
#include <string>
#include <map>
#include <utility>

// Application dependencies.
#include <ias/device/action/action.h>
#include <ias/technology/technology.h>
#include <ias/util/identifiable.h>
#include <ias/util/observable.h>

// Forward declarations.
class Controller;

// END Includes. /////////////////////////////////////////////////////

class Device : public Identifiable, public Observable {

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
    mutable std::mutex mMutexTechnology;
    mutable std::mutex mMutexController;
    
    /**
     * Contains the technology which this device utilizes.
     */
    const Technology * mTechnology;
    
    /**
     * Contains the controller which is associated with this device.
     */
    const Controller * mController;
    
    /**
     * Contains the state of the device.
     */
    std::map<std::string,std::pair<std::string,const ValueType *>> mState;

	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setId( const std::size_t id );
    
    void setUpTechnology( void );
    
    bool controllerConnected( void ) const;
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    Device( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description,
            const Technology * technology );
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Device( void );
    
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
    
    std::size_t set( const std::string & key , const std::string & value );
    
    std::string get( const std::string & key ) const;
    
    void setTechnology( const Technology * technology );
    
    void setController( const Controller * controller );
    
    const Controller * getController( void ) const;
    
    const Technology * getTechnology( void ) const;
    
    void execute( const Action & action );
        
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_H_ */
