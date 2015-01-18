/**
 * An application which outputs the raw event stream data from the IAS server to
 * std::cout.
 *
 * @date                    18 January, 2015
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

#ifndef EVENT_STREAM_APPLICATION_H_
#define EVENT_STREAM_APPLICATION_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/application/application.h>
#include <ias/network/socket.h>

// END Includes. /////////////////////////////////////////////////////

class EventStreamApplication : public Application {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Socket which is connected with the remote event stream.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    Socket * mSocket;

    /**
     * A flag which indicates whether the application is allowed to
     * continue.
     *
     * @note    By default, this member will be equal to true.
     */
    bool mFlagRunning;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    inline void initialize( void );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    EventStreamApplication( const int argc , const char ** argv );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~EventStreamApplication( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void run( void );

    virtual void stop( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* EVENT_STREAM_APPLICATION_H_ */
