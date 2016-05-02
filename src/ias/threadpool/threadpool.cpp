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
#include <cassert>
#include <cstring>

// Application dependencies.
#include <ias/threadpool/threadpool.h>

// END Includes. /////////////////////////////////////////////////////

namespace ias {

    inline void threadpool::lock_queue(void) {
        mMutexQueue.lock();
    }

    inline void threadpool::unlock_queue(void) {
        mMutexQueue.unlock();
    }

    inline void threadpool::initialize(void) {
        mFlagRunning = true;
        mNumSleepingThreads = 0;
        mNumWorkingThreads = 0;
    }

    void threadpool::spawn_threads(const std::size_t numThreads) {
        std::thread * thread;

        // Checking the precondition.
        assert(numThreads > 0);

        for(std::size_t i = 0; i < numThreads; ++i) {
            thread = new std::thread(ias::threadpool::process, this);
            mThreads.push_back(thread);
        }
    }

    void threadpool::join(void) {
        std::thread * thread;
        std::size_t nThreads;

        stop();
        nThreads = mThreads.size();
        mTaskLoad.notify_all();
        for(std::size_t i = 0; i < nThreads; ++i) {
            thread = mThreads.at(i);
            thread->join();
            delete thread;
        }
    }

    std::size_t threadpool::num_working(void) const {
        std::size_t n;

        mMutexWorkingThreads.lock();
        n = mNumWorkingThreads;
        mMutexWorkingThreads.unlock();

        return n;
    }

    std::size_t threadpool::num_sleeping(void) const {
        std::size_t n;

        mMutexSleepingThreads.lock();
        n = mNumSleepingThreads;
        mMutexSleepingThreads.unlock();

        return n;
    }

    bool threadpool::wakeup_required(void) const {
        std::size_t nSleeping;
        std::size_t nWorking;
        std::size_t nTotal;
        std::size_t nNotWorking;
        bool wakeup;

        nSleeping = num_sleeping();
        nWorking = num_working();
        nTotal = num_threads();
        nNotWorking = nTotal - nWorking - nSleeping;
        wakeup = (nNotWorking == 0);

        return wakeup;
    }

    void threadpool::increment_working_thread(void) {
        mMutexWorkingThreads.lock();
        ++mNumWorkingThreads;
        mMutexWorkingThreads.unlock();
    }

    void threadpool::decrement_working_thread(void) {
        mMutexWorkingThreads.lock();
        --mNumWorkingThreads;
        mMutexWorkingThreads.unlock();
    }

    void threadpool::increment_sleeping_thread(void) {
        mMutexSleepingThreads.lock();
        ++mNumSleepingThreads;
        mMutexSleepingThreads.unlock();
    }

    void threadpool::decrement_sleeping_thread(void) {
        mMutexSleepingThreads.lock();
        --mNumSleepingThreads;
        mMutexSleepingThreads.unlock();
    }

    ias::threadpool_task * threadpool::next_task(void) {
        ias::threadpool_task * task;

        task = nullptr;
        mMutexQueue.lock();
        if(mQueue.size() > 0) {
            task = mQueue.front();
            mQueue.pop();
        }
        mMutexQueue.unlock();

        return task;
    }

    bool threadpool::tasks_left(void) const {
        std::size_t n;

        mMutexQueue.lock();
        n = mQueue.size();
        mMutexQueue.unlock();

        return n > 0;
    }

    void threadpool::cleanup_tasks(void) {
        while(!mQueue.empty()) {
            delete mQueue.front();
            mQueue.pop();
        }
    }

    threadpool::threadpool(const std::size_t numThreads) {
        initialize();
        spawn_threads(numThreads);
    }

    threadpool::~threadpool(void) {
        join();
        cleanup_tasks();
    }

    bool threadpool::is_running(void) const {
        return mFlagRunning;
    }

    std::size_t threadpool::num_threads(void) const {
        return mThreads.size();
    }

    void threadpool::stop(void) {
        mFlagRunning = false;
    }

    void threadpool::enqueue(ias::threadpool_task * task) {
        // Checking the precondition.
        assert(task != nullptr);

        lock_queue();
        mQueue.push(task);
        unlock_queue();
        if(wakeup_required())
            mTaskLoad.notify_one();
    }

    void threadpool::process(ias::threadpool * pool) {
        std::unique_lock<std::mutex> lock(pool->mThreadLock);
        ias::threadpool_task * task;

        while(pool->is_running()) {
            task = pool->next_task();
            if(task != nullptr) {
                pool->increment_working_thread();
                task->execute();
                delete task;
                pool->decrement_working_thread();
                continue;
            }
            if(!pool->tasks_left()) {
                pool->increment_sleeping_thread();
                pool->mTaskLoad.wait(lock);
                pool->decrement_sleeping_thread();
            }
        }
    }

};
