/**
 * A class which describes the actions and properties of a user session.
 *
 * @date                    Jul 18, 2014
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

#ifndef USER_SESSION_H_
#define USER_SESSION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/server/session/session.h>
#include <ias/user/user.h>
#include <ias/util/container.h>
#include <ias/user/command/command_dispatcher.h>

// END Includes. /////////////////////////////////////////////////////

class UserSession : public Session {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A container which contains all users.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    Container<User *> * mUsers;
    
    /**
     * Contains the user which is associated with this session.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    User * mUser;
    
    /**
     * Contains the user command dispatcher.
     */
    CommandDispatcher * mDispatcher;
        
    /**
     * A flag tells the session to keep running.
     */
    bool mFlagRunning;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setUserContainer( Container<User *> * users );
    
    void setDispatcher( CommandDispatcher * dispatcher );
    
    void authorize( void );
    
    User * authenticateUser( const char * username, 
                             const char * password ) const;
    
    void processCommand( void );
    
    void analyzeCommand( const char * command );
    
    void sendResponse( const char * buffer , const std::size_t n );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    UserSession( Socket * socket, 
                 Container<User *> * users,
                 CommandDispatcher * dispatcher );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~UserSession( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void );
    
    virtual void stop( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* USER_SESSION_H_ */
