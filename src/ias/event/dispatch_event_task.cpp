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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <iostream>

// Application dependencies.
#include <ias/event/dispatch_event_task.h>

// END Includes. /////////////////////////////////////////////////////

void DispatchEventTask::setEvent( Event * event ) {
    // Checking the precondition.
    assert( event != nullptr );

    mEvent = event;
}

void DispatchEventTask::setChannelSplitter(
        ChannelSplitter<const Event *> * splitter ) {
    // Checking the precondition.
    assert( splitter != nullptr );

    mSplitter = splitter;
}

DispatchEventTask::DispatchEventTask(
        ChannelSplitter<const Event *> * splitter, Event * event ) {
    setEvent(event);
    setChannelSplitter(splitter);
}

DispatchEventTask::~DispatchEventTask( void ) {
    // Free the allocated event.
    delete mEvent; mEvent = nullptr;
}

void DispatchEventTask::execute( void ) {
    mSplitter->pipe(mEvent);
}
