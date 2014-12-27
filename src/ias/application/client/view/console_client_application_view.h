/**
 * A class which describes the properties of a console (or terminal) client
 * application view.
 *
 * @date                    December 25, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
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

#ifndef CONSOLE_CLIENT_APPLICATION_VIEW_H_
#define CONSOLE_CLIENT_APPLICATION_VIEW_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mutex>

// Application dependencies.
#include <ias/application/client/model/client_application_model.h>
#include <ias/application/client/controller/client_application_controller.h>
#include <ias/util/view.h>

// END Includes. /////////////////////////////////////////////////////

class ConsoleClientApplicationView : public View {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Labels which will be used in the view.
     */
    static const char kLabelUsername[];
    static const char kLabelPassword[];

    /**
     * Messages which will be used in the view.
     */
    static const char kMessageNoCredentials[];
    static const char kMessageLoggingIn[];
    static const char kMessageLoggedIn[];
    static const char kMessageLoginFailed[];
    static const char kMessageDisconnecting[];
    static const char kMessageDisconnected[];
    static const char kMessageConnecting[];
    static const char kMessageConnected[];
    static const char kMessageNotConnected[];
    static const char kMessageSpecifyCredentials[];
    static const char kMessageShell[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the controller of the the client application.
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
     * Contains the current state in the program.
     *
     * @note    By default, this member will be equal to 0.
     */
    unsigned int mState;

    /**
     * Contains the host details of the remote service.
     *
     * @note    By default, the address will be empty and the port
     *          will be equal to 0.
     */
    std::string mHostAddress;
    std::size_t mHostPort;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setController( ClientApplicationController * controller );

    void setModel( ClientApplicationModel * model );

    void printWelcomeMessage( void ) const;

    void connect( void );

    void login( void );

    void executeCommands( void );

    void print( const std::string & str ) const;

    void printLine( const std::string & str ) const;

    void printMessage( const std::string & str ) const;

    void printLineEnd( void ) const;

    void handleConnectionState( void ) const;

    void handleLoginState( void );

    void setProxy( const int argc , const char ** argv );

    void setSsl( const int argc , const char ** argv );

    void setHostDetails( const int argc , const char ** argv );

    void setHost( const int argc , const char ** argv );

    void setPort( const int argc , const char ** argv );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ConsoleClientApplicationView( const int argc , const char ** argv,
                                  ClientApplicationController * controller,
                                  ClientApplicationModel * model );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ConsoleClientApplicationView( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    virtual void update( void );

    virtual void update( void * argument );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONSOLE_CLIENT_APPLICATION_VIEW_H_ */
