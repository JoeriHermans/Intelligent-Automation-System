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

#ifndef SESSION_SERVER_H_
#define SESSION_SERVER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <thread>
#include <utility>
#include <map>
#include <mutex>

// Application dependencies.
#include <ias/server/server.h>
#include <ias/server/session/session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

class SessionServer : public Server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A map which holds all running controller sessions and the
     * corresponding sessions.
     */
    std::map<Session *,std::thread *> mSessions;

    /**
     * A set of threads which are meant for cleanup.
     */
    std::vector<std::thread *> mInactiveThreads;

    /**
     * Contains a pointer to the main server thread.
     */
    std::thread * mMainThread;

    /**
     * A flag which indicates if the server needs to stop.
     */
    bool mFlagRunning;

    /**
     * A mutex which sync's the access to the sessions map.
     */
    std::mutex mMutexSessions;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void ) {
        mMainThread = nullptr;
        mFlagRunning = true;
    }

    void cleanupFinishingThreads( void ) {
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

    void signalSessions( void ) {
        std::map<Session *,std::thread *>::iterator it;

        mMutexSessions.lock();
        for( it = mSessions.begin() ; it != mSessions.end() ; ++it )
            it->first->stop();
        mMutexSessions.unlock();
    }

    void joinMainthread( void ) {
        // Check if a main thread is available.
        if( mMainThread != nullptr ) {
            mMainThread->join();
            delete mMainThread;
            mMainThread = nullptr;
        }
    }

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////

    virtual Session * getSession( Socket * socket ) const = 0;

    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    SessionServer( ServerSocket * socket ) : Server(socket) {
        initialize();
    }

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~SessionServer( void ) {
        joinMainthread();
    }

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void start( void ) {
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

    virtual void stop( void ) {
        mFlagRunning = false;
    }

    virtual void join( void ) = 0;

    virtual void update( void ) {
        // Nothing to do here.
    }

    virtual void update( void * argument ) {
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

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* SESSION_SERVER_H_ */
