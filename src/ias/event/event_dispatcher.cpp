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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/event/event_dispatcher.h>

// END Includes. /////////////////////////////////////////////////////

void EventDispatcher::allocateThreadPool( const std::size_t numWorkers ) {
    // Checking the precondition.
    assert( numWorkers > 0 );

    mPool = new ThreadPool(numWorkers);
}

EventDispatcher::EventDispatcher( void ) {
    allocateThreadPool(kDefaultNumWorkers);
}

EventDispatcher::EventDispatcher( const std::size_t numWorkers ) {
    allocateThreadPool(numWorkers);
}

EventDispatcher::~EventDispatcher( void ) {
    mPool->stop();
    delete mPool; mPool = nullptr;
}

void EventDispatcher::dispatch( Event * event ) {
    Task * t;

    // Checking the precondition.
    assert( event != nullptr );

    t = new DispatchEventTask(&mSplitter,event);
    mPool->enqueue(t);
}

void EventDispatcher::addChannel( EventChannel * channel ) {
    // Checking the precondition.
    assert( channel != nullptr );

    mSplitter.addChannel(channel);
}

void EventDispatcher::removeChannel( EventChannel * channel ) {
    // Checking the precondition.
    assert( channel != nullptr );

    mSplitter.removeChannel(channel);
}
