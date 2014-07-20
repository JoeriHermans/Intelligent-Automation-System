/**
 * A class which describes the abstract properties and actions of
 * a controller.
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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mutex>
#include <vector>

// Application dependencies.
#include <ias/device/device.h>
#include <ias/network/socket.h>
#include <ias/util/identifiable.h>

// END Includes. /////////////////////////////////////////////////////

class Controller : public Identifiable {

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
    mutable std::mutex mMutexSecurityCode;
    mutable std::mutex mMutexDevices;
    
    /**
     * Contains the security code of the controller.
     */
    std::string mSecurityCode;
    
    /**
     * A socket which is associated with the controller connection.
     * 
     * @note    If this element is not equal to the null reference, then there
     *          is a connection with this controller available.
     */
    Socket * mSocket;
    
    /**
     * Contains a set of all devices which are associated with this controller.
     */
    std::vector<Device *> mDevices;
        
	// END Private members. //////////////////////////////////////////

	// BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setId( const std::size_t id );
    
    void setDevices( const std::vector<Device *> & devices );
    
	// END Private methods. //////////////////////////////////////////

	protected:

	// BEGIN Protected methods. //////////////////////////////////////
	// END Protected methods. ////////////////////////////////////////

	public:

	// BEGIN Constructors. ///////////////////////////////////////////
    
    Controller( const std::size_t id,
                const std::string & identifier,
                const std::string & name,
                const std::string & description,
                const std::string & securityCode,
                const std::vector<Device *> & devices );
    
	// END Constructors. /////////////////////////////////////////////

	// BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Controller( void );
    
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
    
    bool matchesSecurityCode( const std::string & code ) const;
    
    void setSecurityCode( const std::string & address );
    
    bool isConnected( void ) const;
    
    void setConnected( Socket * socket );
    
    Socket * getSocket( void ) const;
    
    std::size_t numDevices( void ) const;
    
    void addDevice( Device * device );
    
    void removeDevice( const Device * device );
    
    bool containsDevice( const Device * device ) const;
    
    Device * getDevice( const std::size_t id ) const;
    
    Device * getDevice( const std::string & identifier ) const;
    
	// END Public methods. ///////////////////////////////////////////

	// BEGIN Static methods. /////////////////////////////////////////
	// END Static methods. ///////////////////////////////////////////

};

#endif /* CONTROLLER_H_ */
