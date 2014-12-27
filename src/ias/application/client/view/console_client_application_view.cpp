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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>
#include <sstream>
#include <termios.h>
#include <unistd.h>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/application/client/view/console_client_application_view.h>
#include <ias/user/command/command_stop.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char ConsoleClientApplicationView::kLabelUsername[] = "Username: ";
const char ConsoleClientApplicationView::kLabelPassword[] = "Password: ";

const char ConsoleClientApplicationView::kMessageNoCredentials[] =
        "Please specify a username and a password.";
const char ConsoleClientApplicationView::kMessageLoggingIn[] =
        "Logging in...";
const char ConsoleClientApplicationView::kMessageLoggedIn[] =
        "Authentication successful.";
const char ConsoleClientApplicationView::kMessageLoginFailed[] =
        "Authentication failed.";
const char ConsoleClientApplicationView::kMessageDisconnecting[] =
        "Disconnecting.";
const char ConsoleClientApplicationView::kMessageDisconnected[] =
        "Disconnected.";
const char ConsoleClientApplicationView::kMessageConnecting[] =
        "Connecting...";
const char ConsoleClientApplicationView::kMessageConnected[] =
        "Connected to server.";
const char ConsoleClientApplicationView::kMessageNotConnected[] =
        "Could not connect to server.";
const char ConsoleClientApplicationView::kMessageSpecifyCredentials[] =
        "Please specify your user credentials.";
const char ConsoleClientApplicationView::kMessageShell[] = "IAS > ";

// END Constants. ////////////////////////////////////////////////////

inline void ConsoleClientApplicationView::initialize( void ) {
    mController = nullptr;
    mModel = nullptr;
    mState = 0;
    mHostPort = 0;
}

void ConsoleClientApplicationView::setController(
        ClientApplicationController * controller ) {
    // Checking the precondition.
    assert( controller != nullptr );

    mController = controller;
}

void ConsoleClientApplicationView::setModel( ClientApplicationModel * model ) {
    // Checking the precondition.
    assert( model != nullptr );

    mModel = model;
}

void ConsoleClientApplicationView::printWelcomeMessage( void ) const {
    printLine(kVersion);
}

void ConsoleClientApplicationView::connect( void ) {
    mController->createConnection(mHostAddress,mHostPort);
}

void ConsoleClientApplicationView::login( void ) {
    struct termios tty;
    std::string username;
    std::string password;

    // Checking the precondition.
    assert( mModel->isConnected() );

    while( username.empty() || password.empty() ) {
        printMessage(kMessageSpecifyCredentials);
        // Retrieve the username from the terminal.
        print(kLabelUsername);
        std::cin >> username;
        // Retrieve the password from the terminal.
        print(kLabelPassword);
        tcgetattr(STDIN_FILENO,&tty);
        tty.c_lflag &= ~ECHO;
        tcsetattr(STDIN_FILENO,TCSANOW,&tty);
        std::cin >> password;
        tty.c_lflag |= ECHO;
        tcsetattr(STDIN_FILENO,TCSANOW,&tty);
        printLineEnd();
        // Check if the specified credentials are correct.
        if( username.empty() || password.empty() )
            printMessage(kMessageNoCredentials);
    }
    printMessage(kMessageLoggingIn);
    mController->login(username,password);
}

void ConsoleClientApplicationView::executeCommands( void ) {
    std::string command;
    bool terminate;

    // Checking the precondition.
    assert( mModel->isConnected() );

    terminate = false;
    printLineEnd();
    print(kMessageShell);
    while( mModel->isConnected() && !terminate ) {
        std::cin >> command;
        if( mModel->isConnected() ) {
            mController->execute(command);
            if( command == CommandStop::kIdentifier ||
                command == ClientApplicationModel::kCommandQuit )
                terminate = true;
        }
    }
    printLineEnd();
    stop();
}

void ConsoleClientApplicationView::print( const std::string & str ) const {
    std::cout << str << std::flush;
}

void ConsoleClientApplicationView::printLine( const std::string & str ) const {
    std::cout << str << std::endl;
}

void ConsoleClientApplicationView::printLineEnd( void ) const {
    std::cout << std::endl;
}

void ConsoleClientApplicationView::printMessage(
        const std::string & str ) const {
    std::cout << "> " << str << std::endl;
}

void ConsoleClientApplicationView::handleConnectionState( void ) const {
    if( mModel->isConnected() )
        printMessage(kMessageConnected);
    else
        printMessage(kMessageNotConnected);
}

void ConsoleClientApplicationView::handleLoginState( void ) {
    if( mModel->isLoggedIn() ) {
        printMessage(kMessageLoggedIn);
    } else {
        printMessage(kMessageLoginFailed);
        stop();
    }
}

void ConsoleClientApplicationView::setProxy( const int argc,
                                             const char ** argv ) {
    std::string proxy;

    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagSocks) == 0 && argc > (i + 1) ) {
            proxy = argv[i + 1];
            break;
        }
    }
    if( !proxy.empty() ) {
        std::istringstream iss(proxy);
        std::string address;
        std::string strPort;
        std::size_t port;

        std::getline(iss,address,':');
        std::getline(iss,strPort);
        if( !address.empty() && !strPort.empty() ) {
            port = static_cast<std::size_t>(std::stoi(strPort));
            if( port > 0 )
                mController->setProxy(address,port);
        }
    }
}

void ConsoleClientApplicationView::setSsl( const int argc,
                                           const char ** argv ) {
    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagSsl) == 0 ) {
            mController->enableSsl();
            break;
        }
    }
}

void ConsoleClientApplicationView::setHostDetails( const int argc,
                                                   const char ** argv ) {
    // Checking the precondition.
    assert( argc > 0 && argv != nullptr );

    setHost(argc,argv);
    setPort(argc,argv);
}

void ConsoleClientApplicationView::setHost( const int argc,
                                            const char ** argv ) {
    std::string host;

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagAddress) == 0 && argc > (i + 1) ) {
            host = argv[i + 1];
            break;
        }
    }
    if( host.empty() )
        host = kDefaultServerAddress;
    // Set the host.
    mHostAddress = host;
}

void ConsoleClientApplicationView::setPort( const int argc,
                                            const char ** argv ) {
    std::string strPort;
    std::size_t port;

    for( int i = 0 ; i < argc ; ++i ) {
        if( strcmp(argv[i],kFlagPort) == 0 && argc > (i + 1) ) {
            strPort = argv[i + 1];
            break;
        }
    }
    if( !strPort.empty() )
        port = static_cast<std::size_t>(std::stoi(strPort));
    else if( mModel->sslRequested() )
        port = kDefaultUserServerPortSsl;
    else
        port = kDefaultUserServerPort;
    // Set the port.
    mHostPort = port;
}

ConsoleClientApplicationView::ConsoleClientApplicationView(
        const int argc, const char ** argv,
        ClientApplicationController * controller,
        ClientApplicationModel * model ) {
    initialize();
    setController(controller);
    setModel(model);
    setProxy(argc,argv);
    setSsl(argc,argv);
    setHostDetails(argc,argv);
}

void ConsoleClientApplicationView::run( void ) {
    printWelcomeMessage();
    printMessage(kMessageConnecting);
    connect();
    if( mModel->isConnected() ) {
        // Update program state.
        ++mState;
        login();
        if( mModel->isLoggedIn() ) {
            ++mState;
            executeCommands();
        }
    }
}

void ConsoleClientApplicationView::stop( void ) {
    printMessage(kMessageDisconnecting);
    mController->closeConnection();
    printMessage(kMessageDisconnected);
}

void ConsoleClientApplicationView::update( void ) {
    switch(mState) {
    case 0: // Creating connection.
        handleConnectionState();
        break;
    case 1: // Logging in.
        handleLoginState();
        break;
    }
}

void ConsoleClientApplicationView::update( void * argument ) {
    char * buffer;

    buffer = static_cast<char *>(argument);
    printLine(buffer);
    printLineEnd();
    print(kMessageShell);
}
