/**
 * A class which describes the actions and properties of a threadpool.
 * One can supply classes which implement the threadpool_task interface.
 *
 * @date                    02 05 2016
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
#include <vector>
#include <thread>
#include <queue>
#include <mutex>
#include <ctime>
#include <condition_variable>

// Application dependencies.
#include <ias/threadpool/threadpool_task.h>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_THREADPOOL_H_
#define IAS_THREADPOOL_H_

namespace ias {

class threadpool {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * A flag which indicates wheter the threadpool is allowed to continue.
     *
     * @note By default, this member is equal to true.
     */
    bool mFlagRunning;

    /**
     * Holds the mutex for manipulating the sleeping threads.
     */
    mutable std::mutex mMutexSleepingThreads;

    /**
     * Holds the mutex for manipulating the working threads.
     */
    mutable std::mutex mMutexWorkingThreads;

    /**
     * Holds the mutex which is responsible for managing the task queue.
     */
    mutable std::mutex mMutexQueue;

    /**
     * Mutex responsible for handling the sleeping threads.
     */
    mutable std::mutex mThreadLock;

    /**
     * Holds the number of sleeping threads.
     *
     * @note By default, this member will be equal to 0.
     */
    std::size_t mNumSleepingThreads;

    /**
     * Holds the number of working threads.
     *
     * @note By default, this member will be equal to 0.
     */
    std::size_t mNumWorkingThreads;

    /**
     * Condition variable for waking up sleeping threads.
     */
    std::condition_variable mTaskLoad;

    /**
     * A queue which holds pending tasks.
     *
     * @note By default, this queue will be empty.
     */
    std::queue<ias::threadpool_task *> mQueue;

    /**
     * Vector which holds all worker threads (working and sleeping).
     */
    std::vector<std::thread *> mThreads;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void lock_queue(void);

    inline void unlock_queue(void);

    inline void initialize(void);

    void spawn_threads(const std::size_t numThreads);

    void join(void);

    bool wakeup_required(void) const;

    std::size_t num_working(void) const;

    std::size_t num_sleeping(void) const;

    void increment_working_thread(void);

    void decrement_working_thread(void);

    void increment_sleeping_thread(void);

    void decrement_sleeping_thread(void);

    ias::threadpool_task * next_task(void);

    bool tasks_left(void) const;

    void cleanup_tasks(void);

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    threadpool(const std::size_t numThreads);

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~threadpool(void);

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    bool is_running(void) const;

    std::size_t num_threads(void) const;

    void stop(void);

    void enqueue(ias::threadpool_task * task);

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////

    static void process(ias::threadpool * threadpool);

    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
