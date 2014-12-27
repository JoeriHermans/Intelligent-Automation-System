/**
 * A class which describes the properties and actions of a client application
 * controller. This controller will be responsible for handling/relaying view
 * triggers from the view.
 *
 * @date                    December 15, 2014
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

#ifndef CLIENT_APPLICATION_CONTROLLER_H_
#define CLIENT_APPLICATION_CONTROLLER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/application/client/model/client_application_model.h>

// END Includes. /////////////////////////////////////////////////////

class ClientApplicationController {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the client application model.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    ClientApplicationModel * mModel;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setModel( ClientApplicationModel * model );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ClientApplicationController( ClientApplicationModel * model );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ClientApplicationController( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void login( const std::string & username,
                const std::string & password );

    void createConnection( const std::string & address,
                           const std::size_t port );

    void execute( const std::string & command );

    void closeConnection( void );

    void setProxy( const std::string & address,
                   const std::size_t port );

    void setSsl( const bool flag );

    void enableSsl( void );

    void disableSsl( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CLIENT_APPLICATION_CONTROLLER_H_ */
