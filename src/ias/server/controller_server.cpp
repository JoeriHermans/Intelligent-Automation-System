/**
 * A class which will handle incoming connections from controllers and dispatch
 * them accordingly.
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/server/controller_server.h>
#include <ias/server/session/controller_session.h>

// END Includes. /////////////////////////////////////////////////////

inline void ControllerServer::initialize( void ) {
    mControllers = nullptr;
    mMainThread = nullptr;
    mFlagRunning = true;
}

void ControllerServer::setControllerContainer( Container<Controller *> * c ) {
    // Checking the precondition.
    assert( c != nullptr );
    
    mControllers = c;
}

void ControllerServer::cleanupFinishingThreads( void ) {
    std::thread * t;

    while( mInactiveThreads.size() > 0 ) {
        t = mInactiveThreads.front();
        if( t != nullptr ) {
            t->join();
            delete t;
        }
        mInactiveThreads.erase(mInactiveThreads.begin());
    }
}

void ControllerServer::signalSessions( void ) {
    std::map<Session *,std::thread *>::iterator it;
    
    mMutexSessions.lock();
    for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
        it->first->stop();
    mMutexSessions.unlock();
}

ControllerServer::ControllerServer( ServerSocket * socket,
                                    Container<Controller *> * controllers ) :
    Server(socket) {
    initialize();
    setControllerContainer(controllers);
}

ControllerServer::~ControllerServer( void ) {
    join();
}

void ControllerServer::start( void ) {
    if( mMainThread == nullptr ) {
        mMainThread = new std::thread([this](){
            ServerSocket * serverSocket;
            Session * session;
            Socket * socket;

            serverSocket = getServerSocket();
            while( mFlagRunning ) {
                socket = serverSocket->acceptSocket(1);
                if( socket != nullptr ) {
                    session = new ControllerSession(socket,mControllers);
                    session->addObserver(this);
                    mSessions[session] = 
                        new std::thread([session]{
                            session->run();
                            session->notifyObservers(session);
                            delete session;
                        });
                } else if( !serverSocket->isBound() ) {
                    stop();
                }
                cleanupFinishingThreads();
            }
            signalSessions();
            while( mSessions.size() > 0 ||
                   mInactiveThreads.size() > 0 )
                cleanupFinishingThreads();
        });
    }
}

void ControllerServer::stop( void ) {
    mFlagRunning = false;
}

void ControllerServer::join( void ) {
    // Check if a main thread is available.
    if( mMainThread != nullptr ) {
        mMainThread->join();
        delete mMainThread;
        mMainThread = nullptr;
    }
}

void ControllerServer::update( void ) {
    // Do nothing.
}

void ControllerServer::update( void * argument ) {
    std::map<Session *,std::thread *>::iterator it;
    Session * session;
    
    // Checking the precondition.
    assert( argument != nullptr );
    
    session = (Session *) argument;
    it = mSessions.find(session);
    if( it != mSessions.end() ) {
        mInactiveThreads.push_back(it->second);
        mMutexSessions.lock();
        mSessions.erase(it);
        mMutexSessions.unlock();
    }
}
