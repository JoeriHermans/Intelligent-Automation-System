/**
 * A class which describes the properties and actions of an area. An area is a
 * representation of a certain room or a collection of rooms, e.g., a living
 * room. An area has a set of associated devices.
 *
 * @date                    1 March, 2015
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

#ifndef AREA_H_
#define AREA_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <vector>
#include <mutex>

// Application dependencies.
#include <ias/util/identifiable.h>

// END Includes. /////////////////////////////////////////////////////

class Area : public Identifiable {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////

    /**
     * Unique integer identifier of an area.
     */
    std::size_t mId;

    /**
     * Unique string identifier of an area.
     */
    std::string mIdentifier;

    /**
     * Human-readable name of an area.
     */
    std::string mName;

    /**
     * Description of an area.
     */
    std::string mDescription;

    /**
     * A list of adjacent areas.
     *
     * @note    We chose a list because the number of adjacent areas will
     *          probably always small.
     */
    std::vector<Area *> mAdjacentAreas;

    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////

    void setId( const std::size_t id );

    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////

    Area( const std::size_t id,
          const std::string & identifier,
          const std::string & name );

    Area( const std::size_t id,
          const std::string & identifier,
          const std::string & name,
          const std::string & description );

    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////

    virtual ~Area( void );

    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////

    virtual std::size_t getId( void ) const;

    virtual const std::string & getIdentifier( void ) const;

    virtual void setIdentifier( const std::string & identifier );

    virtual const std::string & getName( void ) const;

    virtual void setName( const std::string & name );

    virtual const std::string & getDescription( void ) const;

    virtual bool hasDescription( void ) const;

    virtual void setDescription( const std::string & description );

    std::size_t numAdjacentAreas( void ) const;

    bool isAdjacent( const Area * area ) const;

    Area * getAdjacentArea( const std::size_t index ) const;

    void removeAdjacentArea( const Area * area );

    void connectArea( Area * area );

    void connectAreaBidirectionally( Area * area );

    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* AREA_H_ */
