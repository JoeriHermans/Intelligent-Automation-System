/**
 * A class which describes the properties and actions of the event server. This
 * server will be responsible for reporting events to the client. This service
 * can be used to enable Server Sent Events, which removes the need for polling.
 *
 * @date                    14 January, 2014
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
#include <ias/server/event_server.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventServer::initialize( void ) {
    mDbConnection = nullptr;
    mMainThread = nullptr;
    mFlagRunning = true;
}

void EventServer::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr && dbConnection->isConnected() );

    mDbConnection = dbConnection;
}

void EventServer::cleanupFinishingThreads( void ) {
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

void EventServer::signalSessions( void ) {
    std::map<Session *,std::thread *>::iterator it;

    mMutexSessions.lock();
    for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
        it->first->stop();
    mMutexSessions.unlock();
}

EventServer::EventServer( ServerSocket * serverSocket,
                          DatabaseConnection * dbConnection ) :
    Server(serverSocket) {
    initialize();
    setDatabaseConnection(dbConnection);
}

EventServer::~EventServer( void ) {
    join();
}

void EventServer::start( void ) {
// TODO Implement.
//    if( mMainThread == nullptr ) {
//        mMainThread = new std::thread([this](){
//            ServerSocket * serverSocket;
//            Session * session;
//            Socket * socket;
//
//            serverSocket = getServerSocket();
//            while( mFlagRunning ) {
//                socket = serverSocket->acceptSocket(1);
//                if( socket != nullptr ) {
//                    logi("Starting new events session.");
//                    // TODO Add session.
//                    //session = new ControllerSession(socket,mControllers);
//                    session->addObserver(this);
//                    mSessions[session] =
//                        new std::thread([session]{
//                            session->run();
//                            session->notifyObservers(session);
//                            delete session;
//                            logi("Terminating events session.");
//                        });
//                } else if( !serverSocket->isBound() ) {
//                    stop();
//                }
//                cleanupFinishingThreads();
//            }
//            signalSessions();
//            while( mSessions.size() > 0 ||
//                   mInactiveThreads.size() > 0 ) {
//                signalSessions();
//                cleanupFinishingThreads();
//            }
//        });
//    }
}

void EventServer::stop( void ) {
    mFlagRunning = false;
}

void EventServer::join( void ) {
    // Check if a main thread is available.
    if( mMainThread != nullptr ) {
        mMainThread->join();
        delete mMainThread;
        mMainThread = nullptr;
    }
}

void EventServer::update( void ) {
    // Do nothing.
}

void EventServer::update( void * argument ) {
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
