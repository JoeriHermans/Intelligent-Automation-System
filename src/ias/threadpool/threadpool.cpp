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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <cstring>

// Application dependencies.
#include <ias/threadpool/threadpool.h>

// END Includes. /////////////////////////////////////////////////////

inline void ThreadPool::lockQueue( void ) {
    mMutexQueue.lock();
}

inline void ThreadPool::unlockQueue( void ) {
    mMutexQueue.unlock();
}

void ThreadPool::initialize( void ) {
    mFlagRunning = true;
    mNumSleepingThreads = 0;
    mNumWorkingThreads = 0;
}

void ThreadPool::spawnThreads( const std::size_t numThreads ) {
    std::thread * thread;

    // Checking the precondition.
    assert( numThreads > 0 );
    
    for( std::size_t i = 0 ; i < numThreads ; ++i ) {
        thread = new std::thread(ThreadPool::process,this);
        mThreads.push_back(thread);
    }
}

void ThreadPool::join( void ) {
    std::thread * thread;
    std::size_t nThreads;
    
    stop();
    nThreads = mThreads.size();
    mTaskLoad.notify_all();
    for( std::size_t i = 0 ; i < nThreads ; ++i ) {
        thread = mThreads.at(i);
        thread->join();
        delete thread;
    }
}

std::size_t ThreadPool::numWorking( void ) const
{
    std::size_t n;
    
    mMutexWorkingThreads.lock();
    n = mNumWorkingThreads;
    mMutexWorkingThreads.unlock();
    
    return ( n );
}

std::size_t ThreadPool::numSleeping( void ) const
{
    std::size_t n;
    
    mMutexSleepingThreads.lock();
    n = mNumSleepingThreads;
    mMutexSleepingThreads.unlock();
    
    return ( n );
}

bool ThreadPool::wakeupRequired( void ) const {
    std::size_t nSleeping;
    std::size_t nWorking;
    std::size_t nTotal;
    std::size_t nNotWorking;
    bool wakeup;
    
    nSleeping = numSleeping();
    nWorking = numWorking();
    nTotal = numThreads();
    nNotWorking = nTotal - nWorking - nSleeping;
    wakeup = ( nNotWorking == 0 );
    
    return ( wakeup );
}

void ThreadPool::incrementWorkingThread( void ) {
    mMutexWorkingThreads.lock();
    ++mNumWorkingThreads;
    mMutexWorkingThreads.unlock();
}

void ThreadPool::decrementWorkingThread( void ) {
    mMutexWorkingThreads.lock();
    --mNumWorkingThreads;
    mMutexWorkingThreads.unlock();
}

void ThreadPool::incrementSleepingThread( void ) {
    mMutexSleepingThreads.lock();
    ++mNumSleepingThreads;
    mMutexSleepingThreads.unlock();
}

void ThreadPool::decrementSleepingThread( void ) {
    mMutexSleepingThreads.lock();
    --mNumSleepingThreads;
    mMutexSleepingThreads.unlock();
}

std::size_t ThreadPool::numSleepingThreads( void ) const {
    std::size_t numSleepingThreads;
    
    mMutexSleepingThreads.lock();
    numSleepingThreads = mNumSleepingThreads;
    mMutexSleepingThreads.unlock();
    
    return ( numSleepingThreads );
}

Task * ThreadPool::nextTask( void ) {
    Task * task;
    
    task = nullptr;
    lockQueue();
    if( mQueue.size() > 0 ) {
        task = mQueue.front();
        mQueue.pop();
    }
    unlockQueue();
    
    return ( task );
}

bool ThreadPool::tasksLeft( void ) const
{
    std::size_t n;
    
    mMutexQueue.lock();
    n = mQueue.size();
    mMutexQueue.unlock();
    
    return ( n > 0 );
}

void ThreadPool::cleanupTasks( void ) {
    while( !mQueue.empty() ) {
        delete mQueue.front();
        mQueue.pop();
    }
}

ThreadPool::ThreadPool( const std::size_t numThreads ) {
    initialize();
    spawnThreads(numThreads);
}

ThreadPool::~ThreadPool( void ) {
    join();
    cleanupTasks();
}

bool ThreadPool::isRunning( void ) const {
    return ( mFlagRunning );
}

std::size_t ThreadPool::numThreads( void ) const {
    return ( mThreads.size() );
}

void ThreadPool::stop( void ) {
    mFlagRunning = false;
}

void ThreadPool::enqueue( Task * task ) {
    // Checking the precondition.
    assert( task != nullptr );
    
    lockQueue();
    mQueue.push(task);
    unlockQueue();
    if( wakeupRequired() ) {
        mTaskLoad.notify_one();
    }
}

void ThreadPool::process( ThreadPool * pool ) {
    std::unique_lock<std::mutex> lock(pool->mThreadLock);
    Task * task;

    while( pool->isRunning() ) {
        task = pool->nextTask();
        if( task != nullptr ) {
            pool->incrementWorkingThread();
            task->execute();
            delete task;
            pool->decrementWorkingThread();
            continue;
        }
        if( !pool->tasksLeft() ) {
            pool->incrementSleepingThread();
            pool->mTaskLoad.wait(lock);
            pool->decrementSleepingThread();
        }
    }
}
