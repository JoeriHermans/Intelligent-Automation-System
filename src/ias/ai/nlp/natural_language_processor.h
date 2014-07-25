/**
 * A class which describes the actions and properties of a natural language
 * processor. The processor will take a raw string and analyze it for actions,
 * queries, ...
 *
 * @date                    Jul 23, 2014
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

#ifndef NATURAL_LANGUAGE_PROCESSOR_H_
#define NATURAL_LANGUAGE_PROCESSOR_H_

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <string>
#include <vector>
#include <utility>

// Application dependencies.
#include <ias/ai/nlp/sentence.h>
#include <ias/device/action/action.h>
#include <ias/device/device.h>
#include <ias/building/area.h>
#include <ias/user/user.h>
#include <ias/util/container.h>

// END Includes. /////////////////////////////////////////////////////

class NaturalLanguageProcessor {

    public:

    // BEGIN Class constants. ////////////////////////////////////////
    // END Class constants. //////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////
        
    /**
     * Contains entities which are required to do the NLP.
     */
    const Container<Area *> * mContainerAreas;
    const Container<Device *> * mContainerDevices;
    const Container<Technology *> * mContainerTechnologies;
    
    /**
     * Vectors which represent the elements of the discrete probability
     * distributions.
     */
    std::vector<std::pair<std::string,std::string>> mAreas;
    std::vector<std::pair<std::string,std::string>> mDevices;
    std::vector<std::size_t> mDeviceIds;
    std::vector<std::pair<std::string,std::string>> mFeatures;
    std::vector<std::size_t> mFeatureIds;
        
    // END Private members. //////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////
    
    void setAreaContainer( const Container<Area *> * areas );
    
    void setDeviceContainer( const Container<Device *> * devices );
    
    void setTechnologyContainer( const Container<Technology *> * technologies );
    
    void buildDistributions( void );
    
    void buildAreas( void );
    
    void buildDevices( void );
    
    void buildFeatures( void );
    
    void calculateDistribution( 
        const std::vector<std::pair<std::string,std::string>> & v, 
        const Sentence & sentence,
        double * p ) const;
    
    void evaluateWindow( const std::vector<std::pair<std::string,std::string>> & v,
                         const Sentence & sentence,
                         double * p ) const;
    
    void evaluateSubsets( const std::vector<std::pair<std::string,std::string>> & v,
                          const Sentence & sentence,
                          double * p ) const;
    
    std::vector<std::string> getWords( const Sentence & sentence ) const;
    
    void mapArea( double * p , const double * pA ) const;
    
    void mapFeature( double * p , const double * pPostD ) const;
    
    double totalProbability( const double * p , const std::size_t n ) const;
    
    void add( double * dest, 
              const double * a, 
              const double * b, 
              const std::size_t n ) const;
    
    void divide( double * dest,
                 const double * a,
                 const double factor,
                 const std::size_t n ) const;
    
    std::size_t getDeviceIndex( const std::size_t id ) const;
    
    std::size_t getFeatureIndex( const std::size_t id ) const;
    
    // END Private methods. //////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////
    // END Protected methods. ////////////////////////////////////////

    public:

    // BEGIN Constructors. ///////////////////////////////////////////
    
    NaturalLanguageProcessor( const Container<Area *> * areas,
                              const Container<Device *> * devices,
                              const Container<Technology *> * technologies );
    
    // END Constructors. /////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////
    
    virtual ~NaturalLanguageProcessor( void );
    
    // END Destructor. ///////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////
    
    virtual void process( const std::string & raw );
    
    // END Public methods. ///////////////////////////////////////////

    // BEGIN Static methods. /////////////////////////////////////////
    // END Static methods. ///////////////////////////////////////////

};

#endif /* NATURAL_LANGUAGE_PROCESSOR_H_ */
