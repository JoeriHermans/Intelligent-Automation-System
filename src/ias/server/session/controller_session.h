/**
 * A class which describes the properties and actions of a controller session.
 *
 * @date                    July 6, 2014
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

#ifndef CONTROLLER_SESSION_H_
#define CONTROLLER_SESSION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>

// Application dependencies.
#include <ias/server/session/session.h>
#include <ias/util/container.h>
#include <ias/controller/controller.h>

// END Includes. /////////////////////////////////////////////////////

class ControllerSession : public Session {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the container which holds all controllers in IAS.
     */
    Container<Controller *> * mControllers;
    
    /**
     * Contains the controller which has been associated with this session.
     * 
     * @note    By default, this member will be equal to the null reference.
     */
    Controller * mController;
    
    /**
     * A flag which indicates if the controller session is running.
     */
    bool mFlagRunning;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setContainer( Container<Controller *> * controllers );
    
    void authorize( void );
    
    void controllerUpdate( void );
    
    void controllerDisconnect( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    ControllerSession( Socket * socket,
                       Container<Controller *> * controllers );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ControllerSession( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void run( void );
    
    virtual void stop( void );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONTROLLER_SESSION_H_ */
