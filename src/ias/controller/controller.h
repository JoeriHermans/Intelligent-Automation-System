/**
 * A class which describes the abstract properties and actions of
 * a controller.
 *
 * @date                    Jul 3, 2014
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

#ifndef CONTROLLER_H_
#define CONTROLLER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mutex>
#include <vector>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/util/identifiable.h>

// Forward declaration.
class Device;

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

    /**
     * TODO Write docs.
     */
    Controller( const std::size_t id,
                const std::string & identifier,
                const std::string & name,
                const std::string & description,
                const std::string & securityCode,
                const std::vector<Device *> & devices );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    /**
     * TODO Write docs.
     */
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

    /**
     * Checks if the specified string matches the security code.
     *
     * @param   code
     *          The code we need to evaluate.
     * @return  True, if the security code matches the specified parameter.
     *          False in any other case.
     */
    bool matchesSecurityCode( const std::string & code ) const;

    /**
     * Sets the security code of the controller.
     *
     * @pre     The specified parameter cannot be empty.
     * @param   code
     *          The new security code of the controller.
     * @post    The new security code will be equal to the specified parameter
     *          if and only if all preconditions are met.
     */
    void setSecurityCode( const std::string & code );

    /**
     * Checks if the specified controller is connected to the server.
     *
     * @return  True, if a socket is available (not equal to nullptr). False in
     *          any other case.
     */
    bool isConnected( void ) const;

    /**
     * Sets the socket which is responsible for maintaining the connection with
     * the server.
     *
     * @param   socket
     *          The server connection socket.
     * @post    The socket will be equal to the specified parameter.
     */
    void setConnected( Socket * socket );

    /**
     * Returns the socket of the controller which is connected with the server.
     *
     * @return  The socket. Note that if not socket is available, the result of
     *          this function will be equal to the nullptr.
     */
    Socket * getSocket( void ) const;

    /**
     * Returns the number of devices which are associated with the controller.
     *
     * @return  The number of devices which are associated with the controller.
     */
    std::size_t numDevices( void ) const;

    /**
     * Adds the specified device to the controller.
     *
     * @pre     The specified parameter cannot be equal to the nullptr.
     * @param   device
     *          The device which will be associated with the controller.
     * @post    The specified will be associated with the controller if and
     *          only if the precondition is met.
     */
    void addDevice( Device * device );

    /**
     * Removes the specified device from the set of devices in the controller.
     * The controller of the specified device will be unset after applying this
     * method to the specified parameter.
     *
     * @pre     The specified parameter cannot be equal to the null reference.
     * @param   device
     *          The device which needs does not needs to be associated with the
     *          controller anymore.
     * @post    The specified device won't occur as a device in the controller,
     *          and the controller of the device will be unset.
     */
    void removeDevice( Device * device );

    /**
     * Checks if the specified device is associated with the controller.
     *
     * @param   device
     *          The device we need to check.
     * @return  True, if the device is associated with the controller. False in
     *          any other case.
     */
    bool containsDevice( const Device * device ) const;

    /**
     * Returns the associated device with the specified id.
     *
     * @return  Returns the associated device with the specified id if and only
     *          if a device with the specified id is associated with the
     *          controller. In any other case this method will return the
     *          nullptr.
     */
    Device * getDevice( const std::size_t id ) const;

    /**
     * Returns the associated device with the specified identifier.
     *
     * @return  Returns the associated device with the specified identifier if
     *          and only if a device with the specified identifier is
     *          associated with the controller. In any other case this method
     *          will return the nullptr.
     */
    Device * getDevice( const std::string & identifier ) const;

    /**
     * Returns a list of all associated devices.
     *
     * @return  Returns a list of all associated devices.
     */
    const std::vector<const Device *> getDevices( void ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONTROLLER_H_ */
