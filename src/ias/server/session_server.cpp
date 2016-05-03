
/**
 * An abstract server which is based on session-based connections.
 *
 * @date                    03 05 2016
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
#include <cassert>

// Application dependencies.
#include <ias/server/session_server.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void session_server::initialize(void) {
        mMainThread = nullptr;
        mFlagRunning = true;
    }

    void session_server::cleanup_finishing_threads(void) {
        std::thread * t;

        while(mInactiveThreads.size() > 0) {
            t = mInactiveThreads.front();
            if(t != nullptr) {
                t->join();
                delete t;
            }
            mInactiveThreads.erase(mInactiveThreads.begin());
        }
    }

    void session_server::signal_sessions(void) {
        mMutexSessions.lock();
        for(auto it = mSessions.begin(); it != mSessions.end(); ++it)
            it->first->stop();
        mMutexSessions.unlock();
    }

    void session_server::join_main_thread(void) {
        // Check if the main thread is available.
        if(mMainThread != nullptr) {
            mMainThread->join();
            delete mMainThread;
            mMainThread = nullptr;
        }
    }

    session_server::session_server(ias::server_socket * socket) :
        server(socket) {
        initialize();
    }

    session_server::~session_server(void) {
        join_main_thread();
    }

    void session_server::start(void) {
        // Check if a main thread is already allocated.
        if(mMainThread != nullptr)
            return;

        mMainThread = new std::thread([this](){
                ias::server_socket * serverSocket;
                ias::session * session;
                ias::socket * socket;

                serverSocket = get_server_socket();
                while(mFlagRunning) {
                    socket = serverSocket->accept_socket(1);
                    if(socket != nullptr) {
                        session = allocate_session(socket);
                        session->add_observer(this);
                        mSessions[session] = new std::thread([session]{
                                session->run();
                                session->notify_observers(session);
                                delete session;
                        });
                    } else if(!serverSocket->is_bound()) {
                        stop();
                    }
                    cleanup_finishing_threads();
                }
                signal_sessions();
                while(mSessions.size() > 0 || mInactiveThreads.size() > 0) {
                    signal_sessions();
                    cleanup_finishing_threads();
                }
        });
    }

    void session_server::stop(void) {
        mFlagRunning = false;
    }

    void session_server::join(void) {
        if(mMainThread != nullptr) {
            mMainThread->join();
            delete mMainThread;
            mMainThread = nullptr;
        }
    }

    void session_server::update(void) {}

    void session_server::update(void * argument) {
        ias::session * session;

        // Checking the precondition.
        assert(argument != nullptr);

        session = static_cast<ias::session *>(argument);
        mMutexSessions.lock();
        auto it = mSessions.find(session);
        if(it != mSessions.end()) {
            mInactiveThreads.push_back(it->second);
            mMutexSessions.lock();
            mSessions.erase(it);
        }
        mMutexSessions.unlock();
    }

};
