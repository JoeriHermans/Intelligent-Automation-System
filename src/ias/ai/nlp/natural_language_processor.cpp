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

// BEGIN Includes. ///////////////////////////////////////////////////

// System dependencies.
#include <cassert>
#include <cstring>
#include <utility>

// Application dependencies.
#include <ias/ai/nlp/natural_language_processor.h>

// END Includes. /////////////////////////////////////////////////////

void NaturalLanguageProcessor::setAreaContainer( 
    const Container<Area *> * areas ) {
    // Checking the precondition.
    assert( areas != nullptr );
    
    mContainerAreas = areas;
}

void NaturalLanguageProcessor::setDeviceContainer(
    const Container<Device *> * devices ) {
    // Checking the precondition.
    assert( devices != nullptr );
    
    mContainerDevices = devices;
}

void NaturalLanguageProcessor::setTechnologyContainer(
    const Container<Technology *> * technologies ) {
    // Checking the precondition.
    assert( technologies != nullptr );
    
    mContainerTechnologies = technologies;
}

void NaturalLanguageProcessor::buildDistributions( void ) {
    buildAreas();
    buildDevices();
    buildFeatures();
}

void NaturalLanguageProcessor::buildAreas( void ) {
    std::vector<Area *> areas;
    
    areas = mContainerAreas->getAll();
    for( Area * a : areas ) {
        mAreas.push_back(
            std::pair<std::string,std::string>(a->getIdentifier(),a->getName())
        );
    }
}

void NaturalLanguageProcessor::buildDevices( void ) {
    std::vector<Device *> devices;
    
    devices = mContainerDevices->getAll();
    for( Device * d : devices ) {
        mDevices.push_back(
            std::pair<std::string,std::string>(d->getIdentifier(),d->getName())
        );
    }
}

void NaturalLanguageProcessor::buildFeatures( void ) {
    std::vector<Technology *> technologies;
    
    technologies = mContainerTechnologies->getAll();
    for( Technology * t : technologies ) {
        const std::vector<Feature *> & features = t->getFeatures();
        for( Feature * f : features ) {
            mFeatures.push_back(
                std::pair<std::string,std::string>(
                    f->getIdentifier(),f->getName())
            );
        }
    }
}

NaturalLanguageProcessor::NaturalLanguageProcessor( 
    const Container<Area *> * areas,
    const Container<Device *> * devices,
    const Container<Technology *> * technologies ) {
    setAreaContainer(areas);
    setDeviceContainer(devices);
    setTechnologyContainer(technologies);
    buildDistributions();
}

NaturalLanguageProcessor::~NaturalLanguageProcessor( void ) {
    // Nothing to do here.
}

void NaturalLanguageProcessor::process( const std::string & raw ) {
    Sentence sentence(raw);
    
    // TODO Implement.
}
