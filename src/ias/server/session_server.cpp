/**
 * An abstract server which is based on session-based connections.
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/server/session_server.h>

// END Includes. /////////////////////////////////////////////////////

inline void SessionServer::initialize( void ) {
    mMainThread = nullptr;
    mFlagRunning = true;
}

void SessionServer::cleanupFinishingThreads( void ) {
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

void SessionServer::signalSessions( void ) {
    std::map<Session *,std::thread *>::iterator it;

    mMutexSessions.lock();
    for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
        it->first->stop();
    mMutexSessions.unlock();
}

void SessionServer::joinMainthread( void ) {
    // Check if a main thread is available.
    if( mMainThread != nullptr ) {
        mMainThread->join();
        delete mMainThread;
        mMainThread = nullptr;
    }
}

SessionServer::SessionServer( ServerSocket * socket ) :
    Server(socket) {
    initialize();
}

SessionServer::~SessionServer( void ) {
    joinMainthread();
}

void SessionServer::start( void ) {
    if( mMainThread == nullptr ) {
        mMainThread = new std::thread([this](){
            ServerSocket * serverSocket;
            Session * session;
            Socket * socket;

            serverSocket = getServerSocket();
            while( mFlagRunning ) {
                socket = serverSocket->acceptSocket(1);
                if( socket != nullptr ) {
                    session = getSession(socket);
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
                   mInactiveThreads.size() > 0 ) {
                signalSessions();
                cleanupFinishingThreads();
            }
        });
    }
}

void SessionServer::stop( void ) {
    mFlagRunning = false;
}

void SessionServer::join( void ) {
    if( mMainThread != nullptr ) {
        mMainThread->join();
        delete mMainThread;
        mMainThread = nullptr;
    }
}

void SessionServer::update( void ) {}

void SessionServer::update( void * argument ) {
    std::map<Session *,std::thread *>::iterator it;
    Session * session;

    // Checking the precondition.
    assert( argument != nullptr );

    session = static_cast<Session *>(argument);
    it = mSessions.find(session);
    if( it != mSessions.end() ) {
        mInactiveThreads.push_back(it->second);
        mMutexSessions.lock();
        mSessions.erase(it);
        mMutexSessions.unlock();
    }
}
