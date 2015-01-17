/**
 * A class which describes the actions and properties of an event session. This
 * session will notify the connected endpoint of server events (like device
 * updates, e.d.). This way, we can prevent polling.
 *
 * @date                    17 January, 2015
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

#ifndef EVENT_SESSION_H_
#define EVENT_SESSION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/database/interface/database_connection.h>
#include <ias/event/event_dispatcher.h>
#include <ias/network/socket.h>
#include <ias/server/session/session.h>

// END Includes. /////////////////////////////////////////////////////

class EventSession : public Session {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Database connection which will be used to authenticate API keys.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    DatabaseConnection * mDbConnection;

    /**
     * Event dispatcher, this object will be used in this class to register
     * the an active event channel. And, off course, to unregister the channel
     * when the session is closed.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    EventDispatcher * mEventDispatcher;

    /**
     * Holds the active channel when the remote endpoint has been authenticated.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    EventChannel * mChannel;

    /**
     * A flag which indicates whether the session should continue.
     *
     * @note    By default, this flag is set.
     */
    bool mFlagRunning;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setDatabaseConnection( DatabaseConnection * connection );

    void setEventDispatcher( EventDispatcher * eventDispatcher );

    void setAuthenticationTimeouts( void );

    void setTimeouts( void );

    void authorize( void );

    void authorizeApiKey( void );

    void validateApiKey( const std::string & key );

    bool heartbeat( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    EventSession( Socket * socket, DatabaseConnection * connection,
                  EventDispatcher * eventDispatcher );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~EventSession( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* EVENT_SESSION_H_ */
