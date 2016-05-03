/**
 * A class which describes the properties and actions of a channel
 * splitter. This channel will take an argument at its source and pipe
 * the argument over all sinks.
 *
 * @date                    03 05 2016
 * @author                  Joeri HERMANS
 * @version                 0.1
 *
 * Copyright 2016 Joeri HERMANS
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
#include <cassrt>
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/channel/channel.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_CHANNEL_SPLITTER_H_
#define IAS_CHANNEL_SPLITTER_H_

namespace ias {

template<class T>
class channel_splitter : public channel<T> {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * A vector which holds all the sinks of the splitter.
     *
     * @note By default, this vector will be empty, i.e., no sink will
     *       be attached.
     */
    std::vector<ias::channel<T> *> mSinks;

    /**
     * A mutex which synchronized the access to the sinks.
     */
    mutable std::mutex mMutexSinks;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    channel_splitter(void) = default;

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~channel_splitter(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual void pipe(T argument) {
        mMutexSinks.lock();
        for(auto it = mSinks.begin(); it != mSinks.end(); ++it)
            (*it)->pipe(argument);
        mMutexSinks.unlock();
    }

    void add_channel(ias::channel<T> * channel) {
        // Checking the precondition.
        assert(channel != nullptr);

        mMutexSinks.lock();
        mSinks.push_back(channel);
        mMutexSinks.unlock();
    }

    void remove_channel(ias::channel<T> * channel) {
        ias::channel<T> * c;

        // Checking the precondition.
        assert(channel != nullptr);

        mMutexSinks.lock();
        for(auto it = mSinks.begin(); it != mSinks.end(); ++it) {
            c = (*it);
            if(c == channel) {
                mSinks.erase(it);
                break;
            }
        }
        mMutexSinks.unlock();
    }

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
