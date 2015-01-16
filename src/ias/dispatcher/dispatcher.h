/**
 * A template which is responsible for dispatching instances of T to the
 * appropriate channels.
 *
 * @date                    July 7, 2014
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

#ifndef DISPATCHER_H_
#define DISPATCHER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <vector>
#include <string>
#include <mutex>
#include <map>

// Application dependencies.
#include <ias/channel/channel.h>

// END Includes. /////////////////////////////////////////////////////

template<class T>
class Dispatcher {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A map which holds the channels.
     */
    std::map<std::string,Channel<T> *> mChannels;

    /**
     * A mutex which synchronizes the channels.
     */
    std::mutex mLock;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    Dispatcher( void ){}

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Dispatcher( void ) {
        for( auto it = mChannels.begin() ; it != mChannels.end() ; ++it ) {
            delete it->second;
        }
    }

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void addChannel( const std::string & identifier, Channel<T> * channel ) {
        // Checking the preconditions.
        assert( !identifier.empty() && channel != nullptr );

        mLock.lock();
        mChannels[identifier] = channel;
        mLock.unlock();
    }

    void removeChannel( const std::string & identifier ) {
        typename std::map<std::string,Channel<T> *>::iterator it;

        mLock.lock();
        it = mChannels.find(identifier);
        if( it != mChannels.end() ) {
            delete it->second;
            mChannels.erase(it);
        }
        mLock.unlock();
    }

    bool containsChannel( const std::string & identifier ) {
        typename std::map<std::string,Channel<T> *>::iterator it;
        bool contains;

        contains = false;
        mLock.lock();
        it = mChannels.find(identifier);
        if( it != mChannels.end() )
            contains = true;
        mLock.unlock();

        return ( contains );
    }

    void dispatch( const std::string & identifier , T argument ) {
        typename std::map<std::string,Channel<T> *>::const_iterator it;
        Channel<T> * channel;

        channel = nullptr;
        mLock.lock();
        it = mChannels.find(identifier);
        if( it != mChannels.end() ) {
            channel = it->second;
        }
        mLock.unlock();
        if( channel != nullptr ) {
            channel->pipe(argument);
        }
    }

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* DISPATCHER_H_ */
