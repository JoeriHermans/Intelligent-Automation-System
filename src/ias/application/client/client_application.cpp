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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/application/client/client_application.h>

// END Includes. /////////////////////////////////////////////////////

inline void ClientApplication::initialize( void ) {
    mController = nullptr;
    mModel = nullptr;
    mView = nullptr;
}

void ClientApplication::initializeController( const int argc,
                                              const char ** argv ) {
    // Checking the precondition.
    assert( mController == nullptr && mModel != nullptr
            && argc > 0 && argv != nullptr );

    mController = new ClientApplicationController(mModel);
}

void ClientApplication::initializeModel( const int argc, const char ** argv ) {
    // Checking the precondition.
    assert( mModel == nullptr && argc > 0 && argv != nullptr );

    mModel = new ClientApplicationModel();
}

void ClientApplication::initializeView( const int argc , const char ** argv ) {
    // Checking the precondition.
    assert( mController != nullptr && argc > 0 && argv != nullptr );

    mView = new ConsoleClientApplicationView(argc,argv,mController,mModel);
}

void ClientApplication::registerViews( void ) {
    // Checking the precondition.
    assert( mModel != nullptr && mView != nullptr );

    mModel->addObserver(mView);
}

ClientApplication::ClientApplication( const int argc , const char ** argv ) {
    initialize();
    initializeModel(argc,argv);
    initializeController(argc,argv);
    initializeView(argc,argv);
    registerViews();
}

ClientApplication::~ClientApplication( void ) {
    delete mController; mController = nullptr;
    delete mModel; mModel = nullptr;
    delete mView; mView = nullptr;
}

void ClientApplication::run( void ) {
    mView->run();
}

void ClientApplication::stop( void ) {
    if( mView != nullptr )
        mView->stop();
}
