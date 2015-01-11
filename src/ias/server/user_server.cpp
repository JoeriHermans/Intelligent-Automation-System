/**
 * A class which describes the properties and actions of a user server. A
 * user servers allows for users to connect and execute commands remotely.
 *
 * @date                    Jul 18, 2014
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
#include <ias/server/user_server.h>
#include <ias/server/session/user_session.h>
#include <ias/user/command/command_stop.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void UserServer::initialize( void ) {
    mUsers = nullptr;
    mMainThread = nullptr;
    mDbConnection = nullptr;
    mFlagRunning = true;
    mDispatcher = nullptr;
}

void UserServer::setUserContainer( Container<User *> * users ) {
    // Checking the precondition.
    assert( users != nullptr );

    mUsers = users;
}

void UserServer::setDispatcher( CommandDispatcher * dispatcher ) {
    // Checking the precondition.
    assert( dispatcher != nullptr );

    mDispatcher = dispatcher;
}

void UserServer::setDatabaseConnection( DatabaseConnection * dbConnection ) {
    // Checking the precondition.
    assert( dbConnection != nullptr );

    mDbConnection = dbConnection;
}

void UserServer::cleanupFinishingThreads( void ) {
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

void UserServer::signalSessions( void ) {
    std::map<Session *,std::thread *>::iterator it;

    mMutexSessions.lock();
    for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
        it->first->stop();
    mMutexSessions.unlock();
}

UserServer::UserServer( ServerSocket * serverSocket,
                        Container<User *> * users,
                        CommandDispatcher * dispatcher,
                        DatabaseConnection * dbConnection ) :
    Server(serverSocket) {
    initialize();
    setUserContainer(users);
    setDispatcher(dispatcher);
    setDatabaseConnection(dbConnection);
}

UserServer::~UserServer( void ) {
    join();
}

void UserServer::start( void ) {
    if( mMainThread == nullptr ) {
        mMainThread = new std::thread([this](){
            ServerSocket * serverSocket;
            Session * session;
            Socket * socket;

            serverSocket = getServerSocket();
            while( mFlagRunning ) {
                socket = serverSocket->acceptSocket(1);
                if( socket != nullptr ) {
                    logi("Starting new user session.");
                    session = new UserSession(socket,mUsers,mDispatcher,
                                              mDbConnection);
                    session->addObserver(this);
                    mSessions[session] =
                        new std::thread([session]{
                            session->run();
                            session->notifyObservers(session);
                            delete session;
                            logi("User session terminated.");
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

void UserServer::stop( void ) {
    mFlagRunning = false;
}

void UserServer::join( void ) {
    // Check if a main thread is available.
    if( mMainThread != nullptr ) {
        mMainThread->join();
        delete mMainThread;
        mMainThread = nullptr;
    }
}

void UserServer::update( void ) {
    // Do nothing.
}

void UserServer::update( void * argument ) {
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
