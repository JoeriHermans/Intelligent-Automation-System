/**
 * A wrapper class for the event dispatching system.
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

#ifndef EVENT_DISPATCHER_H_
#define EVENT_DISPATCHER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/event/event.h>
#include <ias/event/dispatch_event_task.h>
#include <ias/threadpool/threadpool.h>
#include <ias/channel/channel_splitter.h>

// END Includes. /////////////////////////////////////////////////////

class EventDispatcher {

    public:

    // BEGIN Class constants. ////////////////////////////////////////

    /**
     * The default number of workers for the threadpool.
     */
    static const std::size_t kDefaultNumWorkers = 3;

    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Threadpool which is responsible for processing the incoming tasks
     * (event dispatches).
     */
    ThreadPool * mPool;

    /**
     * The channel splitter to which channels can be attached which
     * need to be notified of the event.
     */
    ChannelSplitter<const Event *> mSplitter;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void allocateThreadPool( const std::size_t numWorkers );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    EventDispatcher( void );

    EventDispatcher( const std::size_t numWorkers );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~EventDispatcher( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void dispatch( Event * event );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* EVENT_DISPATCHER_H_ */
