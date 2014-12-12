/**
 * A class which describes the properties and actions of a POSIX SOCKS
 * proxy socket. This socket will connect to a remote SOCKS proxy server.
 *
 * Please note that this class only allows outgoing connections to the proxy
 * server.
 *
 * Implementation according to RFC 1928 (https://www.ietf.org/rfc/rfc1928.txt).
 *
 * @date                    December 12, 2014
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

#ifndef POSIX_SOCKS_SOCKET_H_
#define POSIX_SOCKS_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>

// Application dependencies.
#include <ias/network/socket.h>
#include <ias/network/posix/posix_tcp_socket.h>

// END Includes. /////////////////////////////////////////////////////

class PosixSocksSocket : public Socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * Contains the SOCKS protocol version.
     */
    static const std::uint8_t kProtocolVersion = 0x05;

    /**
     * Contains the method identifier of the "No authentication" method.
     */
    static const std::uint8_t kMethodNoAuthentication = 0x00;

    /**
     * Contains the method identifier of the "Username/password" method.
     */
    static const std::uint8_t kMethodUsernamePassword = 0x02;

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the file descriptor which is associated with the TCP
     * connection towards the SOCKS proxy.
     *
     * @note    A value of -1 is assigned for a disconnected socket.
     */
    mutable int mFileDescriptor;

    /**
     * Contains the SOCKS proxy server address.
     */
    std::string mProxyAddress;
    std::size_t mProxyPort;

    /**
     * Contains the credentials of the SOCKS proxy server.
     */
    std::string mUsername;
    std::string mPassword;

    /**
     * Contains the address of the client.
     */
    std::string mClientAddress;
    std::size_t mClientPort;

    /**
     * A reader which is responsible for writing bytes to the SOCKS proxy.
     *
     * @note    In the case that the socket is not connected, the value of the
     *          reader will be equal to the null reference.
     */
    Reader * mReader;

    /**
     * A writer which is responsible for writing bytes to the SOCKS proxy.
     *
     * @note    In the case that the socket is not connected, the value of
     *          the reader will be equal to the NULL reference.
     */
    Writer * mWriter;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    void setFileDescriptor( const int fd );

    void setClientAddress( const std::string & clientAddress,
                           const std::size_t clientPort );

    void setProxyAddress( const std::string & proxyAddress,
                          const std::size_t proxyPort );

    void setCredentials( const std::string & username,
                         const std::string & password );

    void resetReaderAndWriter( void );

    void pollSocket( void ) const;

    bool initializeConnection( void );

    bool negotiate( void );

    bool authenticate( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    PosixSocksSocket( const std::string & proxyAddress,
                      const std::size_t proxyPort );

    PosixSocksSocket( const std::string & proxyAddress,
                      const std::size_t proxyPort,
                      const std::string & username,
                      const std::string & password );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~PosixSocksSocket( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void closeConnection( void );

    virtual bool createConnection( const std::string & address,
                                   const std::size_t port );

    virtual bool isConnected( void ) const;

    virtual Reader * getReader( void ) const;

    virtual Writer * getWriter( void ) const;

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* POSIX_SOCKS_SOCKET_H_ */
