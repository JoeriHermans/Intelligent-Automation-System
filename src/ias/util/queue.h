/**
 * This queue a container of std::queue. However, this queue is threadsafe.
 *
 * @date                    14 January, 2015
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

#ifndef QUEUE_H_
#define QUEUE_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <queue>
#include <mutex>

// END Includes. /////////////////////////////////////////////////////

template<class T>
class Queue {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Queue which contains the raw data.
     */
    std::queue<T> mQueue;

    /**
     * Mutex which is responsible for data access synchronization.
     */
    mutable std::mutex mMutex;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    Queue( void ) = default;

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Queue( void ) = default;

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    void pop( void ) {
        mMutex.lock();
        mQueue.pop();
        mMutex.unlock();
    }

    void push( T element ) {
        mMutex.lock();
        mQueue.push(element);
        mMutex.unlock();
    }

    T front( void ) const {
        T element;

        mMutex.lock();
        element = mQueue.front();
        mMutex.unlock();

        return ( element );
    }

    std::size_t size( void ) const {
        std::size_t n;

        mMutex.lock();
        n = mQueue.size();
        mMutex.unlock();

        return ( n );
    }

    bool empty( void ) const {
        bool empty;

        mMutex.lock();
        empty = mQueue.empty();
        mMutex.unlock();

        return ( empty );
    }

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* QUEUE_H_ */
