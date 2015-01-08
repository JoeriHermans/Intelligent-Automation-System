/**
 * A container which is responsible for storing Identifiable types.
 *
 * @date                    Jul 4, 2014
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

#ifndef CONTAINER_H_
#define CONTAINER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <vector>
#include <mutex>
#include <algorithm>
#include <utility>

// END Includes. /////////////////////////////////////////////////////

template<class T>
class Container {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Data structures. ////////////////////////////////////////

    struct Compare {
        inline bool operator()( const T & a , const T & b ) {
            return ( a->getId() < b->getId() );
        }
        inline bool operator()( const T & a , const std::size_t right ) {
            return ( a->getId() < right );
        }
        inline bool operator()( const std::size_t left , const T & b ) {
            return ( left < b->getId() );
        }
    };

    // END Data structures. //////////////////////////////////////////

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Contains a vector which stores the instances by id.
     */
    std::vector<T> mElements;

    /**
     * A mutex to prevent data corruption.
     */
    mutable std::mutex mMutexElements;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void sort( void ) {
        std::sort(mElements.begin(),mElements.end(),Compare());
    }

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    Container( void ) {
        // Nothing to do here.
    }

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Container( void ) {
        mMutexElements.lock();
        for( auto it = mElements.begin() ; it != mElements.end() ; ++it )
            delete (*it);
        mMutexElements.unlock();
    }

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    std::size_t numElements( void ) const {
        std::size_t n;

        mMutexElements.lock();
        n = mElements.size();
        mMutexElements.unlock();

        return ( n );
    }

    bool contains( const T & element ) const {
        bool contains;

        mMutexElements.lock();
        contains = ( std::find(mElements.begin(),mElements.end(),element) !=
                     mElements.end() );
        mMutexElements.unlock();

        return ( contains );
    }

    void add( T & element ) {
        // Checking the precondition.
        assert( element != nullptr );

        if( !contains(element) ) {
            mMutexElements.lock();
            mElements.push_back(element);
            sort();
            mMutexElements.unlock();
        }
    }

    void remove( const T & element ) {
        mMutexElements.lock();
        auto it = std::lower_bound(mElements.begin(),mElements.end(),
                                   element->getId(),Compare());
        if( it != mElements.end() ) {
            delete (*it);
            mElements.erase(it);
            sort();
        }
        mMutexElements.unlock();
    }

    T get( const std::size_t id ) const {
        T currentElement;
        T element;

        // Checking the precondition.
        assert( id > 0 );

        element = nullptr;
        mMutexElements.lock();
        for( auto it = mElements.begin() ; it != mElements.end() ; ++it ) {
            currentElement = (*it);
            if( currentElement->getId() == id ) {
                element = currentElement;
                break;
            }
        }
        mMutexElements.unlock();

        return ( element );
    }

    T get( const std::string & identifier ) const {
        T element;
        T currentElement;

        // Checking the precondition.
        assert( !identifier.empty() );

        element = nullptr;
        mMutexElements.lock();
        for( auto it = mElements.begin() ; it != mElements.end() ; ++it ) {
            currentElement = (*it);
            if( currentElement->getIdentifier() == identifier ) {
                element = currentElement;
                break;
            }
        }
        mMutexElements.unlock();

        return ( element );
    }

    std::vector<T> getAll( void ) const {
        std::vector<T> list;

        mMutexElements.lock();
        for( auto it = mElements.begin() ; it != mElements.end() ; ++it ) {
            list.push_back((*it));
        }
        mMutexElements.unlock();

        return ( list );
    }

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* CONTAINER_H_ */
