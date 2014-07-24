/**
 * A class which describes the properties of a technology member.
 *
 * @date                    Jul 3, 2014
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

#ifndef MEMBER_H_
#define MEMBER_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// Application dependencies.
#include <ias/technology/value_type.h>
#include <ias/util/identifiable.h>

// END Includes. /////////////////////////////////////////////////////

class Member : public Identifiable {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains the unique id of a device.
     */
    std::size_t mId;
    
    /**
     * Contains the unique identifier of a device.
     */
    std::string mIdentifier;
    
    /**
     * Contains the name of the device.
     */
    std::string mName;
    
    /**
     * Contains the description of the device.
     */
    std::string mDescription;
    
    /**
     * Contains mutexes for the editing of class members.
     */
    std::mutex mMutexIdentifier;
    std::mutex mMutexName;
    std::mutex mMutexDescription;
    std::mutex mMutexDefaultValue;
    std::mutex mMutexValueType;
    
    /**
     * Contains the default value of the member.
     */
    std::string mDefaultValue;
    
    /**
     * Contains the value type of the member.
     */
    const ValueType * mValueType;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    inline void initialize( void );
    
    void setId( const std::size_t id );
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    Member( const std::size_t id,
            const std::string & identifier,
            const std::string & name,
            const std::string & description,
            const std::string & defaultValue,
            const ValueType * valueType );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~Member( void );
    
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
    
    void setDefaultValue( const std::string & valueType );
    
    const std::string & getDefaultValue( void ) const;
    
    void setValueType( const ValueType * valueType );
    
    const ValueType * getValueType( void ) const;
        
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* MEMBER_H_ */
