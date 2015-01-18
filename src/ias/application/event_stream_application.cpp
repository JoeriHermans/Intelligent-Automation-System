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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/application/event_stream_application.h>

// END Includes. /////////////////////////////////////////////////////

inline void EventStreamApplication::initialize( void ) {
    mSocket = nullptr;
    mFlagRunning = true;
}

EventStreamApplication::EventStreamApplication( const int argc,
                                                const char ** argv ) {
    initialize();
}

EventStreamApplication::~EventStreamApplication( void ) {
    delete mSocket; mSocket = nullptr;
}

void EventStreamApplication::run( void ) {
    // TODO Implement.
}

void EventStreamApplication::stop( void ) {
    mFlagRunning = false;
}
