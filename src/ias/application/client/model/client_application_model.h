/**
 * A class which decribes the properties and actions of a client
 * application.
 *
 * @date                    24 05 2016
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
#include <openssl/err.h>
#include <openssl/ssl.h>
#include <string>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <condition_variable>
#include <ctime>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/util/observable.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CLIENT_APPLICATION_MODEL_H_
#define IAS_CLIENT_APPLICATION_MODEL_H_

namespace ias {

class client_application_model : public observable {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Command identifier in order to quit the application.
     */
    static const char kCommandQuit[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Holds the socket which is responsible for maintaining the network
     * connection with the remote IAS host.
     *
     * @note By default, this member will be equal to the null reference.
     */
    ias::socket * mSocket;

    /**
     * A flag which checks if a user has been authorized.
     *
     * @note By default, this flag will be initialized to false.
     */
    bool mLoggedIn;

    /**
     * Threads which are responsible for handling the client / server
     * communication. I've chosen for this type of handling because the IAS
     * server software regurally sends heartbeats in order to check if the
     * client is still connected. This architecture will allow to do such
     * a thing.
     *
     * @note By default, these members will be equal to the null reference.
     */
    std::thread * mCommunicationThreadSend;
    std::thread * mCommunicationThreadReceive;

    /**
     * Holds commands which have been issued by the user, these commands need
     * to be sent to the remote IAS host.
     */
    std::queue<std::string> mCommandQueue;

    /**
     * Mutex which is responsible for synchronizing access to the command queue
     * storage.
     */
    std::mutex mMutexCommandQueue;

    /**
     * Conditioning variables which will lock the sending thread when no data
     * in the queue is available, and wake the thread up when new data arrives.
     */
    std::condition_variable mLockSend;
    std::mutex mMutexLockSend;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void initialize(void);

    void set_socket_timeouts(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    client_application_model(void);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~client_application_model(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////
    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
