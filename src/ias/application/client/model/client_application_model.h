/**
 * A class which describes the properties and actions of a client application.
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

#ifndef CLIENT_APPLICATION_MODEL_H_
#define CLIENT_APPLICATION_MODEL_H_

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

class ClientApplicationModel : public Observable {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * A command which tells the application to stop.
     */
    static const char kCommandQuit[];

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the socket which is responsible for maintaining the network
     * connection with the remote IAS host.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    Socket * mSocket;

    /**
     * Contains the SSL context of the client application.
     */
    SSL_CTX * mSslContext;

    /**
     * Service identifier of the remote SOCKS proxy.
     */
    std::string mSocksHost;
    std::size_t mSocksPort;

    /**
     * A flag which checks if a user has been authorized.
     *
     * @note    By default, this flag will be unset.
     */
    bool mLoggedIn;

    /**
     * Contains the threads which will handle the client / server communication.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    std::thread * mCommunicationThreadSend;
    std::thread * mCommunicationThreadReceive;

    /**
     * Contains the queue which contains that need to executed.
     *
     * @note    By default, this queue will be empty.
     */
    std::queue<std::string> mCommandQueue;

    /**
     * Contains the mutex which will be responsible for handling the access
     * to the command queue.
     */
    std::mutex mCommandMutex;

    /**
     * A mutex to lock the send thread.
     */
    std::mutex mSendMutex;

    /**
     * A condition variable which is responsible for locking the sending thread
     * when no data is available.
     */
    std::condition_variable mSendLock;
    std::mutex mMutexThreadSendLock;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setSocketTimeouts( void );

    int connectToSocksProxy( const std::string & host,
                             const std::size_t port ) const;

    void readResponses( void );

    void readResponse( void );

    void sendCommand( const std::string & command );

    void sendHeartbeat( void );

    void stopCommunicationThreads( void );

    void spawnCommunicationThreads( void );

    void handleCommunicationSend( void );

    void handleCommunicationReceive( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ClientApplicationModel( void );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ClientApplicationModel( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void setProxy( const std::string & host,
                   const std::size_t port );

    bool proxySpecified( void ) const;

    void requestSsl( const bool flag );

    bool sslRequested( void ) const;

    void closeConnection( void );

    bool isConnected( void ) const;

    void createConnection( const std::string & host, const std::size_t port );

    void execute( const std::string & command );

    bool isLoggedIn( void ) const;

    void authorize( const std::string & username,
                    const std::string & password );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CLIENT_APPLICATION_MODEL_H_ */
