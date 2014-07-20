/**
 * A command which will force the IAS server to stop.
 *
 * @date					Jul 18, 2014
 * @author					Joeri HERMANS
 * @version					0.1
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_stop.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandStop::kIdentifier[] = "stop";

// END Constants. ////////////////////////////////////////////////////

void CommandStop::setApplication( ServerApplication * app ) {
    // Checking the precondition.
    assert( app != nullptr );
    
    mApplication = app;
}

CommandStop::CommandStop( ServerApplication * application ) :
        Command(kIdentifier) {
        setApplication(application);
}

CommandStop::~CommandStop( void ) {
    // Nothing to do here.
}

std::string CommandStop::execute( const std::string & parameters ) {
    std::string result;
    
    mApplication->stop();
    result = kProtocolAck;
    
    return ( result );
}
