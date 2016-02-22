/**
 * A class which described the properties and actions of a device.
 *
 * @date                    Jul 3, 2014
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
#include <ias/controller/controller.h>

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
    std::map<std::string,std::string> mState;

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

    /**
     * Sets the the value of the specified state identifier (key).
     *
     * @pre     The specified key and value cannot be empty.
     * @param   key
     *          The identifier of a state member.
     * @param   value
     *          The new value of the specified state.
     * @return  0, if the state was set successfully.
     *          1, if the specified state identifier could not be found.
     *          2, if the specified value doesn't match the required value type.
     */
    std::size_t set( const std::string & key , const std::string & value );

    /**
     * Returns the value of the specified state.
     *
     * @param   key
     *          The identifier of the state which needs to be retrieved.
     * @return  The value of the specified state if and only if the specified
     *          state occurs in the device, else this method will return the
     *          empty string.
     */
    std::string get( const std::string & key ) const;

    /**
     * Sets the technology of the device.
     *
     * @pre     The specified parameter cannot be equal to the null pointer.
     * @param   technology
     *          The technology which this device implements.
     * @post    The state of the device will be cleared, and the states (and
     *          the default values of those states) will be loaded from
     *          the specified technology.
     */
    void setTechnology( const Technology * technology );

    /**
     * Sets the controller to which this device is associated with.
     *
     * @pre     The specified parameter cannot be equal to the null pointer.
     * @param   controller
     *          The new associated controller.
     * @post    The associated controller of this device will be equal to the
     *          specified parameter if and only if all preconditions are met.
     */
    void setController( const Controller * controller );

    /**
     * Returns the associated controller.
     *
     * @return  The associated controller.
     */
    const Controller * getController( void ) const;

    /**
     * Returns the technology of this device.
     *
     * @return  The implemented technology.
     */
    const Technology * getTechnology( void ) const;

    /**
     * Executes the specified action.
     * The specified action will only be executed if the technology supports
     * the feature and if the controller is connected to the server.
     */
    void execute( const Action & action );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DEVICE_H_ */
