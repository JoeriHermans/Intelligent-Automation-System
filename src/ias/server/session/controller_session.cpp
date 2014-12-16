/**
 * A class which describes the properties and actions of a controller session.
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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <cstring>
#include <iostream>

// Application dependencies.
#include <ias/server/session/controller_session.h>
#include <ias/logger/logger.h>

// END Includes. /////////////////////////////////////////////////////

inline void ControllerSession::initialize( void ) {
    mController = nullptr;
    mControllers = nullptr;
    mFlagRunning = false;
}

void ControllerSession::setContainer( Container<Controller *> * controllers ) {
    // Checking the precondition.
    assert( controllers != nullptr );

    mControllers = controllers;
}

void ControllerSession::authorize( void ) {
    std::uint8_t header[3];
    Controller * controller;

    logi("Authorizing controller.");
    if( readBytes(reinterpret_cast<char *>(header),3) && header[0] == 0x00 ) {
        char identifier[header[1] + 1];
        char securityCode[header[2] + 1];

        if( readBytes(identifier,header[1]) &&
            readBytes(securityCode,header[2]) ) {
            identifier[header[1]] = 0;
            securityCode[header[2]] = 0;
            controller = mControllers->get(identifier);
            if( controller != nullptr &&
                controller->matchesSecurityCode(securityCode) &&
                !controller->isConnected() ) {
                logi("Controller " + controller->getIdentifier() + " authorized.");
                mController = controller;
                mController->setConnected(getSocket());
                mFlagRunning = true;
            }
        }
    }
    if( !mFlagRunning )
        loge("Controller authorization failed.");
}

void ControllerSession::controllerUpdate( void ) {
    std::uint8_t length[3];
    std::size_t nBytes;
    Device * device;
    Reader * reader;
    bool success;

    success = false;
    reader = getSocket()->getReader();
    nBytes = reader->readBytes(reinterpret_cast<char *>(length),3);
    if( nBytes == 3 ) {
        char deviceIdentifier[length[0] + 1];
        char stateIdentifier[length[1] + 1];
        char stateValue[length[2] + 1];

        if( !readBytes(deviceIdentifier,length[0]) ||
            !readBytes(stateIdentifier,length[1]) ||
            !readBytes(stateValue,length[2]) )
            return;

        deviceIdentifier[length[0]] = 0;
        stateIdentifier[length[1]] = 0;
        stateValue[length[2]] = 0;
        device = mController->getDevice(deviceIdentifier);
        if( device != nullptr ) {
            device->set(stateIdentifier,stateValue);
            success = true;
        }
    }
    if( !success )
        getSocket()->closeConnection();
}

void ControllerSession::controllerDisconnect( void ) {
    if( mController != nullptr )
        logi(mController->getIdentifier() + " disconnecting.");
    else
        logi("Unauthenticated controller disconnecting.");
    mFlagRunning = false;
}

ControllerSession::ControllerSession( Socket * socket,
                                      Container<Controller *> * controllers ) :
    Session(socket) {
    initialize();
    setContainer(controllers);
}

ControllerSession::~ControllerSession( void ) {
    stop();
}

void ControllerSession::run( void ) {
    std::uint8_t messageType;
    std::size_t nBytes;
    Reader * reader;

    authorize();
    reader = getSocket()->getReader();
    while( mFlagRunning && getSocket()->isConnected() ) {
        nBytes = reader->readByte(reinterpret_cast<char *>(&messageType));
        if( nBytes == 0 ) {
            stop();
        } else {
            switch(messageType) {
            case 0x01:
                controllerUpdate();
                break;
            case 0x02:
                controllerDisconnect();
                break;
            default:
                controllerDisconnect();
                break;
            }
        }
    }
    getSocket()->closeConnection();
    if( mController != nullptr )
        mController->setConnected(nullptr);
}

void ControllerSession::stop( void ) {
    static const std::uint8_t stop = 0xff;
    Writer * writer;

    if( mFlagRunning ) {
        mFlagRunning = false;
        if( mController != nullptr && getSocket()->isConnected() ) {
            writer = getSocket()->getWriter();
            // Send controller stop message.
            writer->writeBytes(reinterpret_cast<const char *>(&stop),1);
        }
        controllerDisconnect();
    }
}
