/**
 * A task which is responsible for dispatching an event to a set of connected
 * channels.
 *
 * Please note that this class we free (delete) the specified event.
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

#ifndef TASK_DISPATCH_EVENT_H_
#define TASK_DISPATCH_EVENT_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/channel/channel_splitter.h>
#include <ias/event/event.h>
#include <ias/threadpool/task.h>

// END Includes. /////////////////////////////////////////////////////

class DispatchEventTask : public Task {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains the event which needs to be dispatched to the channels.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    Event * mEvent;

    /**
     * The channel splitter which holds all channels to which we will need
     * to dispatch the event.
     *
     * @note    By default, this member will be equal to the null reference.
     */
    ChannelSplitter<const Event *> * mSplitter;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setEvent( Event * event );

    void setChannelSplitter( ChannelSplitter<const Event *> * splitter );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    DispatchEventTask( ChannelSplitter<const Event *> * splitter,
                       Event * event );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~DispatchEventTask( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void execute( void );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* TASK_DISPATCH_EVENT_H_ */
