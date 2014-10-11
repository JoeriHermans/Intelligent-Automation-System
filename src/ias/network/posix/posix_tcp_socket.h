/**
 * A class which represents the properties and actions of a POSIX TCP socket.
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

#ifndef POSIX_TCP_SOCKET_H_
#define POSIX_TCP_SOCKET_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <mutex>

// Application dependencies.
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class PosixTcpSocket : public Socket {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the file descriptor which is associated with the TCP connection.
     * 
     * @note    A value of -1 means that the socket is not connected.
     */
    mutable int mFileDescriptor;
    
    /**
     * Contains the reader which is associated with the socket.
     * 
     * @note    In the case that the socket is not connected, the value of
     *          the reader will be equal to the null reference.
     */
    Reader * mReader;
    
    /**
     * Contains the writer which is associated with the socket.
     * 
     * @note    In the case that the socket is not connected, the value of
     *          the writer will be equal to the null reference.
     */
    Writer * mWriter;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setFileDescriptor( const int fd );
    
    bool initializeConnection( const std::string & address, 
                               const std::size_t port );
    
    void pollSocket( void ) const;
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    PosixTcpSocket( void );
    
    PosixTcpSocket( const int fd );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~PosixTcpSocket( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void closeConnection( void );
    
    virtual bool createConnection( const std::string & address,
                                   const std::size_t port );
    
    virtual bool isConnected( void ) const;
    
    virtual Reader * getReader( void ) const;
    
    virtual Writer * getWriter( void ) const;
    
    int getFileDescriptor( void ) const;
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* POSIX_TCP_SOCKET_H_ */
