/**
 * A command which describes the full properties of a specified device in
 * detail.
 *
 * @date                    11 January, 2015
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

// Command dependencies.
#include <cassert>

// Application dependencies.
#include <ias/application/constants.h>
#include <ias/user/command/command_device_detail.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

// BEGIN Constants. //////////////////////////////////////////////////

const char CommandDeviceDetail::kIdentifier[] = "ddetail";

// END Constants. ////////////////////////////////////////////////////

void CommandDeviceDetail::setDeviceContainer( Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );

    mDevices = devices;
}

void CommandDeviceDetail::buildResponse( const Device * d,
                                         std::string & response ) const {
    Member * m;
    std::size_t n;
    std::size_t technologyId;
    std::size_t controllerId;

    // Checking the precondition.
    assert( d != nullptr );

    technologyId = d->getTechnology()->getId();
    if( d->getController() == nullptr )
        controllerId = 0;
    else
        controllerId = d->getController()->getId();
    response = "{\n";
    response += "  \"id\":" + std::to_string(d->getId()) + ",\n";
    response += "  \"identifier\":\"" + d->getIdentifier() + "\",\n";
    response += "  \"name\":\"" + d->getName() + "\",\n";
    response += "  \"description\":\"" + d->getDescription() + "\",\n";
    response += "  \"technology_id\":\"" + std::to_string(technologyId) + "\",\n";
    response += "  \"controller_id\":\"" + std::to_string(controllerId) + "\",\n";
    response += "  \"state\": [\n";
    const std::vector<Member *> & members = d->getTechnology()->getMembers();
    n = members.size();
    for( std::size_t i = 0 ; i < n ; ++i ) {
        m = members.at(i);
        response += "    {\"" + m->getIdentifier() + "\":\"" +
                            d->get(m->getIdentifier()) +
                            "\"}";
        if( n > 1 && i < ( n - 1 ) )
            response += ',';
        response += "\n";
    }
    response += "]}";
}

CommandDeviceDetail::CommandDeviceDetail( Container<Device *> * devices ) :
    Command(kIdentifier) {
    setDeviceContainer(devices);
}

std::string CommandDeviceDetail::execute( User * user, const std::string & parameters ) {
    const Device * d;
    std::string response;

    // Checking the precondition.
    assert( user != nullptr );

    if( isNumber(parameters) ) {
        std::size_t id = std::stoull(parameters,nullptr,0);
        d = mDevices->get(id);
    } else {
        d = mDevices->get(parameters);
    }
    if( d != nullptr )
        buildResponse(d,response);
    if( response.empty() )
        response = kProtocolNack;

    return ( response );
}
