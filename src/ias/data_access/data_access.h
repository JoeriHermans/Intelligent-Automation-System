/**
 * An abstract interface which provides the functionality of a
 * data access objects. This class abstracts the underlaying
 * storing and caches methods.
 *
 * @date                    27 05 2016
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
#include <unordered_map>
#include <mutex>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_DATA_ACCESS_H_
#define IAS_DATA_ACCESS_H_

namespace ias {

template<typename T>
class data_access {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * An unordered map which provides fast caching access for the objects
     * the user wants to store. This cache provides an id -> object mapping.
     */
    std::unordered_map<std::size_t, T> mCache;

    /**
     * Mutex which synchronizes the access to the cache.
     */
    std::mutex mCacheMutex;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////
    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////

    bool cache_contains(T element) {
        bool contains;

        mCacheMutex.lock();
        auto it = mCache.find(element->get_id());
        contains = (it != mCache.end());
        mCacheMutex.unlock();

        return contains;
    }

    void cache_clear(void) {
        mCacheMutex.lock();
        // Free the allocated memory as well.
        for(auto it = mCache.begin(); it != mCache.end(); ++it)
            delete it->second;
        mCache.clear();
        mCacheMutex.unlock();
    }

    void cache_remove(T element) {
        std::size_t id;

        id = element->get_id();
        mCacheMutex.lock();
        mCache.erase(id);
        mCacheMutex.unlock();
    }

    void cache_remove(const std::size_t id) {
        mCacheMutex.lock();
        mCache.erase(id);
        mCacheMutex.unlock();
    }

    void cache_store(T element) {
        mCacheMutex.lock();
        mCache[element->get_id()] = element;
        mCacheMutex.unlock();
    }

    void cache_store_fast(const std::vector<T> & elements) {
        mCacheMutex.lock();
        // Store all elements in a fast way.
        for(auto it = elements.begin(); it != elements.end(); ++it) {
            T element = (*it);
            mCache[element->get_id()] = element;
        }
        mCacheMutex.unlock();
    }

    T cache_get(const std::size_t id) {
        T element = nullptr;

        mCacheMutex.lock();
        auto it = mCache.find(id);
        if(it != mCache.end())
            element = it->second;
        mCacheMutex.unlock();

        return element;
    }

    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    data_access<T>(void) = default;

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~data_access<T>(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual std::vector<T> get_all(void) const = 0;

    virtual T get(const std::size_t id) const = 0;

    virtual void add(T element) = 0;

    virtual void remove(T element) = 0;

    virtual void remove(const std::size_t id) = 0;

    virtual void update(T element) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
