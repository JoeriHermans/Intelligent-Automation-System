/**
 * An application which is responsible for handling the client/server
 * communications.
 *
 * @date                    Jul 17, 2014
 * @author                  Joeri HERMANS
 * @version                 0.2
 *
 * Copyright 2014 Joeri HERMANS
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

#ifndef CLIENT_APPLICATION_H_
#define CLIENT_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/application/application.h>
#include <ias/application/client/controller/client_application_controller.h>
#include <ias/application/client/model/client_application_model.h>
#include <ias/application/client/view/console_client_application_view.h>

// END Includes. /////////////////////////////////////////////////////

class ClientApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the controller of the client application.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    ClientApplicationController * mController;

    /**
     * Contains the model of the client application.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    ClientApplicationModel * mModel;

    /**
     * Contains the view which this application will run.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    View * mView;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void initializeController( const int argc , const char ** argv );

    void initializeModel( const int argc , const char ** argv );

    void initializeView( const int argc , const char ** argv );

    void registerViews( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ClientApplication( const int argc , const char ** argv );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ClientApplication( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CLIENT_APPLICATION_H_ */
