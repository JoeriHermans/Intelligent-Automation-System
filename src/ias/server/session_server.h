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

#ifndef IAS_SESSION_SERVER_H_
#define IAS_SESSION_SERVER_H_

namespace ias {

class session_server : public server {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * A map which holds all active sessions.
     */
    std::map<ias::session *, std::thread *> mSessions;

    /**
     * A set of threads which are meant for cleanup.
     */
    std::vector<std::thread *> mInactiveThreads;

    /**
     * Holds the main server thread.
     *
     * @note By default, this member is equal to the null reference.
     */
    std::thread * mMainThread;

    /**
     * A flag which indicates if the server is allowed to continue.
     *
     * @note By default, this member will be equal to true.
     */
    bool mFlagRunning;

    /**
     * A mutex which synchronizes the access to the sessions map.
     */
    std::mutex mMutexSessions;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void cleanup_finishing_threads(void);

    void signal_sessions(void);

    void join_main_thread(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////

    virtual ias::session * allocate_session(ias::socket * socket) const = 0;

    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    session_server(ias::server_socket * socket);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~session_server(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void start(void);

    virtual void stop(void);

    virtual void join(void);

    virtual void update(void);

    virtual void update(void * argument);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
