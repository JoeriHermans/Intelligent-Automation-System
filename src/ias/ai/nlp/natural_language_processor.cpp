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
#include <iostream>

// Application dependencies.
#include <ias/ai/nlp/natural_language_processor.h>
#include <ias/util/util.h>

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
        mDeviceIds.push_back(d->getId());
    }
}

void NaturalLanguageProcessor::buildFeatures( void ) {
    std::vector<Technology *> technologies;
    std::size_t i;
    
    technologies = mContainerTechnologies->getAll();
    for( Technology * t : technologies ) {
        const std::vector<Feature *> & features = t->getFeatures();
        for( Feature * f : features ) {
            std::string identifier = f->getIdentifier();
            std::string name = f->getName();
            std::transform(identifier.begin(),identifier.end(),
                           identifier.begin(),::tolower);
            std::transform(name.begin(),name.end(),name.begin(),::tolower);
            mFeatures.push_back(
                std::pair<std::string,std::string>(identifier,name)
            );
            mFeatureIds.push_back(f->getId());
        }
    }
}

void NaturalLanguageProcessor::calculateDistribution(
    const std::vector<std::pair<std::string,std::string>> & v,
    const Sentence & sentence,
    double * p ) const {
    evaluateWindow(v,sentence,p);
}

std::vector<std::string> NaturalLanguageProcessor::getWords( 
    const Sentence & sentence ) const {
    std::vector<std::string> words;
    std::size_t n;
    
    n = sentence.numEntities();
    for( std::size_t i = 0 ; i < n ; ++i ) {
        if( sentence.isWord(i) )
            words.push_back(sentence.getEntity(i));
    }
    
    return ( words );
}

void NaturalLanguageProcessor::evaluateWindow(
    const std::vector<std::pair<std::string,std::string>> & v,
    const Sentence & sentence,
    double * p ) const {
    double probabilitySum;
    std::vector<std::string> words;
    std::size_t minDistance;
    std::size_t distanceIdentifier;
    std::size_t distanceName;
    std::size_t nEntities;
    std::size_t nWords;
    std::size_t n;
    
    probabilitySum = 0;
    n = v.size();
    words = getWords(sentence);
    nWords = words.size();
    for( std::size_t vi = 0 ; vi < n ; ++vi ) {
        minDistance = INFINITY;
        for( std::size_t l = 1 ; l <= nWords ; ++l ) {
            for( std::size_t i = 0 ; i < nWords ; ++i ) {
                std::string subset;
                for( std::size_t j = 0 ; (i + j) < nWords && j < l &&
                     (i + l) <= nWords ; ++j ) {
                    if( sentence.isWord(j + i) ) {
                        subset += " " + words.at(j + i);
                    }
                }
                if( subset.length() > 0 ) {
                    distanceIdentifier = editDistance(subset,v.at(vi).first);
                    distanceName = editDistance(subset,v.at(vi).second);
                    if( distanceIdentifier < minDistance )
                        minDistance = distanceIdentifier;
                    else
                    if( distanceName < minDistance )
                        minDistance = distanceName;
                }
            }
        }
        p[vi] = 1 / ( exp((double) minDistance) );
        probabilitySum += p[vi];
    }
    // Normalize distribution.
    for( std::size_t vi = 0 ; vi < n ; ++vi ) {
        p[vi] /= probabilitySum;
    }
}

void NaturalLanguageProcessor::evaluateSubsets(
    const std::vector<std::pair<std::string,std::string>> & v,
    const Sentence & sentence,
    double * p ) const {
    std::size_t nSubsets;
    std::size_t nEntities;
    std::size_t nWords;
    std::size_t n;
    std::size_t mask;
    std::size_t minDistance;
    std::size_t distanceIdentifier;
    std::size_t distanceName;
    double probabilitySum;
    
    n = v.size();
    nEntities = sentence.numEntities();
    nWords = sentence.numWords();
    probabilitySum = 0;
    for( std::size_t vi = 0 ; vi < n ; ++vi ) {
        minDistance = INFINITY;
        mask = (1 << nEntities);
        for( std::size_t i = 1 ; i < mask ; ++i ) {
            std::string subset;
            
            for( std::size_t j = 0 ; j < nEntities ; ++j ) {
                if( sentence.isWord(j) && (i & (1 << j)) > 0 )
                    subset += sentence.getEntity(j) + " ";
            }
            trim(subset);
            distanceIdentifier = editDistance(v.at(vi).first,subset);
            distanceName = editDistance(v.at(vi).second,subset);
            if( distanceIdentifier < minDistance )
                minDistance = distanceIdentifier;
            else
            if( distanceName < minDistance )
                minDistance = distanceName;
        }
        p[vi] = 1 / ( exp((double) minDistance) );
        probabilitySum += p[vi];
    }
    // Normalize the distribution.
    for( std::size_t vi = 0 ; vi < n ; ++vi ) {
        p[vi] /= probabilitySum;
    }
}

std::size_t NaturalLanguageProcessor::getDeviceIndex( const std::size_t id ) const {
    std::size_t index;
    
    index = 0;
    for( std::size_t i = 0 ; i < mDevices.size() ; ++i ) {
        if( mDeviceIds.at(i) == id ) {
            index = i;
            break;
        }
    }
    
    return ( index );
}

std::size_t NaturalLanguageProcessor::getFeatureIndex( const std::size_t id ) const {
    std::size_t index;
    
    index = 0;
    for( std::size_t i = 0 ; i < mFeatures.size() ; ++i ) {
        if( mFeatureIds.at(i) == id ) {
            index = i;
            break;
        }
    }
    
    return ( index );
}

void NaturalLanguageProcessor::mapArea( double * p , const double * pA ) const {
    std::size_t index;
    std::size_t i;
    Area * area;
    double prob;
    
    i = 0;
    for( auto pair : mAreas ) {
        area = mContainerAreas->get(pair.first);
        prob = pA[i];
        std::vector<Device *> devices = area->getDevices();
        prob /= (double) devices.size();
        for( Device * d : devices ) {
            index = getDeviceIndex(d->getId());
            p[index] += prob;
        }
        ++i;
    }
}

void NaturalLanguageProcessor::mapFeature( double * p , const double * pPostD ) 
    const {
    Device * d;
    double prob;
    std::size_t i;
    std::size_t index;
    
    i = 0;
    for( auto pair : mDevices ) {
        d = mContainerDevices->get(pair.first);
        prob = pPostD[i];
        const std::vector<Feature *> & features = 
            d->getTechnology()->getFeatures();
        prob /= features.size();
        for( Feature * f : features ) {
            index = getFeatureIndex(f->getId());
            p[index] += prob;
        }
    }
}

double NaturalLanguageProcessor::totalProbability( const double * p,
                                                   const std::size_t n ) const {
    double t;
    
    t = 0;
    for( std::size_t i = 0 ; i < n ; ++i )
        t += p[i];
    
    return ( t );
}

void NaturalLanguageProcessor::add( double * dest, 
                                    const double * a, 
                                    const double * b, 
                                    const std::size_t n ) const {
    for( std::size_t i = 0 ; i < n ; ++i ) {
        dest[i] = a[i] + b[i];
    }
}

void NaturalLanguageProcessor::divide( double * dest,
                                       const double * a,
                                       const double factor,
                                       const std::size_t n ) const {
    for( std::size_t i = 0 ; i < n ; ++i ) {
        dest[i] = a[i] / factor;
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
    std::size_t nAreas = mAreas.size();
    std::size_t nDevices = mDevices.size();
    std::size_t nFeatures = mFeatures.size();
    
    double pA[nAreas];
    double pD[nDevices];
    double pPostD[nDevices];
    double pF[nFeatures];
    double pPostF[nFeatures];
    double t;
    
    // Reset the probability distributions.
    memset(pA,0,nAreas);
    memset(pD,0,nDevices);
    memset(pPostD,0,nDevices);
    memset(pF,0,nFeatures);
    memset(pPostF,0,nFeatures);
    // Calculate the prior probability distributions.
    calculateDistribution(mAreas,sentence,pA);
    calculateDistribution(mDevices,sentence,pD);
    calculateDistribution(mFeatures,sentence,pF);
    mapArea(pPostD,pA);
    t = totalProbability(pPostD,nDevices);
    t += totalProbability(pD,nDevices);
    add(pPostD,pPostD,pD,nDevices);
    divide(pPostD,pPostD,2,nDevices);
    divide(pPostD,pPostD,t,nDevices);
    mapFeature(pPostF,pPostD);
    t = totalProbability(pPostF,nFeatures);
    t += totalProbability(pPostF,nFeatures);
    add(pPostF,pPostF,pF,nFeatures);
    divide(pPostF,pPostF,2,nFeatures);
    divide(pPostF,pPostF,t,nFeatures);
    for( std::size_t i = 0 ; i < nDevices ; ++i ) {
        std::cout << "P(D = " << mDevices.at(i).first << ") = " << std::to_string(pPostD[i]) << std::endl;
    }
    for( std::size_t i = 0 ; i < nFeatures ; ++i ) {
        std::cout << "P(F = " << mFeatures.at(i).first << ") = " << std::to_string(pPostF[i]) << std::endl;
    }
}
