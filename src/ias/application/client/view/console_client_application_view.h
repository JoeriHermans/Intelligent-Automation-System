/**
 * A class which describes the properties and actions of a console
 * or terminal IAS client application.
 *
 * @date                    25 05 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <mutex>
#include <string>

// Application dependencies.
#include <ias/application/client/model/client_application_model.h>
#include <ias/util/observer.h>
#include <ias/util/view.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CONSOLE_CLIENT_APPLICATION_VIEW_H_
#define IAS_CONSOLE_CLIENT_APPLICATION_VIEW_H_

namespace ias {

class console_client_application_view : public view {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Labels to be used in the view.
     */
    static const char kLabelPassword[];
    static const char kLabelUsername[];

    /**
     * Messages which will be used in the view.
     */
    static const char kMessageConnected[];
    static const char kMessageConnecting[];
    static const char kMessageDisconnected[];
    static const char kMessageDisconnecting[];
    static const char kMessageLoggedIn[];
    static const char kMessageLoggingIn[];
    static const char kMessageLoginFailed[];
    static const char kMessageNoCredentials[];
    static const char kMessageNotConnected[];
    static const char kMessageShell[];
    static const char kMessageSpecifyCredentials[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the application model this view represents.
     *
     * @note By default, this member will be equal to the null reference.
     */
    ias::client_application_model * mModel;

    /**
     * Address parameters of the remote server.
     *
     * @note By default, these will be initialized to their default
     *       values.
     */
    std::string mHost;
    std::size_t mPort;

    /**
     * Holds the SOCKS proxy server address and port.
     *
     * @note By default, the server address will be empty and the
     *       port will be initialized to 0.
     */
    std::string mSocksHost;
    std::size_t mSocksPort;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    inline void set_model(ias::client_application_model * model);

    inline void stopping(void);

    void connect(void);

    void execute_commands(void);

    void login(void);

    void disable_terminal_echo(void) const;

    void enable_terminal_echo(void) const;

    void print_message(const std::string & message) const;

    void set_host(const int argc, const char ** argv);

    void set_port(const int argc, const char ** argv);

    void set_proxy(const int argc, const char ** argv);

    void set_ssl(const int argc, const char ** argv);

    void print(const std::string & message) const;

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    console_client_application_view(const int argc, const char ** argv,
                                    ias::client_application_model * model);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~console_client_application_view(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void paint(void);

    virtual void update(void);

    virtual void update(void * argument);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
