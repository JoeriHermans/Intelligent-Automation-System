/**
 * A class which describes the actions and properties of a threadpool.
 *
 * @date                    Jul 2, 2014
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

#ifndef THREADPOOL_H_
#define THREADPOOL_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <ctime>
#include <condition_variable>

// Application dependencies.
#include <ias/threadpool/task.h>

// END Includes. /////////////////////////////////////////////////////

class ThreadPool {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * A flag which indicates whether the thread pool is allowed to
     * continue.
     * 
     * @note    By default, this member is equal to true.
     */
    bool mFlagRunning;
    
    /**
     * Contains the mutex for manipulating the number of
     * sleeping threads.
     */
    mutable std::mutex mMutexSleepingThreads;
    
    /**
     * A mutex which is responsible for the handling of the working threads
     * counter.
     */
    mutable std::mutex mMutexWorkingThreads;
    
    /**
     * A mutex which is responsible for handling the queue access.
     */
    mutable std::mutex mMutexQueue;
    
    /**
     * Mutex which is responsible for handling the sleeping threads.
     */
    mutable std::mutex mThreadLock;
    
    /**
     * Holds the number of sleeping threads.
     * 
     * @note    By default, this member will be equal to 0.
     */
    std::size_t mNumSleepingThreads;
    
    /**
     * Holds the number of working threads.
     * 
     * @note    By default, this member will be equal to 0.
     */
    std::size_t mNumWorkingThreads;
    
    /**
     * A condition variable for the locking threads.
     */
    std::condition_variable mTaskLoad;
    
    /**
     * A queue which hold the task which need to be processed.
     * 
     * @note    By default, this queue will be empty.
     */
    std::queue<Task *> mQueue;
    
    /**
     * A vector which hold the different threads.
     * 
     * @note    By default, this vector will be empty.
     */
    std::vector<std::thread *> mThreads;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void lockQueue( void );
    
    inline void unlockQueue( void );
    
    void initialize( void );
    
    void spawnThreads( const std::size_t numThreads );
    
    void join( void );
    
    bool wakeupRequired( void ) const;
    
    std::size_t numWorking( void ) const;
    
    std::size_t numSleeping( void ) const;
    
    void incrementWorkingThread( void );
    
    void decrementWorkingThread( void );
    
    void incrementSleepingThread( void );
    
    void decrementSleepingThread( void );
    
    std::size_t numSleepingThreads( void ) const;
    
    Task * nextTask( void );
    
    bool tasksLeft( void ) const;
    
    void cleanupTasks( void );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    ThreadPool( const std::size_t numThreads );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~ThreadPool( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    bool isRunning( void ) const;
    
    std::size_t numThreads( void ) const;
    
    void stop( void );
    
    void enqueue( Task * task );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    
    static void process( ThreadPool * pool );
    
    // END Static methods. ///////////////////////////////////////////

};

#endif /* THREADPOOL_H_ */
