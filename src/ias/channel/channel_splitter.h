/**
 * A class which describes the properties and actions of a channel splitter.
 * This channel will take an element at it source and divides the element over
 * all its exits.
 *
 * Please note that this class is NOT responsible for the descruction of the
 * specified channels.
 *
 * @date                    16 January, 2015
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

#ifndef CHANNEL_SPLITTER_H_
#define CHANNEL_SPLITTER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/channel/channel.h>

// END Includes. /////////////////////////////////////////////////////

template<class T>
class ChannelSplitter : public Channel<T> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * A vector which holds all the exits of the splitter.
     *
     * @note    By default, this vector will be empty.
     */
    std::vector mExits;

    /**
     * A mutex which synchronizes the access to the exit channels.
     */
    mutable std::mutex mMutexExits;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    ChannelSplitter( void ) = default;

    ChannelSplitter( const std::vector<Channel *> & exits ) {
        mExits = exits;
    }

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~ChannelSplitter( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual void pipe( T argument ) {
        mMutexExits.lock();
        for( auto it = mExits.begin() ; it != mExits.end() ; ++it )
            it->pipe(argument);
        mMutexExits.unlock();
    }

    void addExit( Channel<T> * channel ) {
        mMutexExits.lock();
        mExits.push_back(channel);
        mMutexExits.unlock();
    }

    void removeChannel( const Channel<T> * channel ) {
        mMutexExits.lock();
        mExits.erase(
                std::remove(mExits.begin(),mExits.end(),channel),mExits.end());
        mMutexExits.unlock();
    }

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CHANNEL_SPLITTER_H_ */
