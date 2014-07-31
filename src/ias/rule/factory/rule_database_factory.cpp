/**
 * A database factory which is responsible for extracting rules from a
 * database.
 *
 * @date                    Jul 21, 2014
 * @author                  Joeri HERMANS
 * @version                 0.1
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

// Application dependencies.
#include <ias/rule/factory/rule_database_factory.h>

// END Includes. /////////////////////////////////////////////////////

void RuleDatabaseFactory::setDeviceContainer( Container<Device *> * devices ) {
    // Checking the preconditions.
    assert( devices != nullptr );
    
    mDeviceContainer = devices;
}

RuleDatabaseFactory::RuleDatabaseFactory( DatabaseConnection * dbConnection,
                                          Container<Device *> * devices ) :
    DatabaseFactory<Rule *>(dbConnection) {
    setDeviceContainer(devices);
}

RuleDatabaseFactory::~RuleDatabaseFactory( void ) {
    // Nothing to do here.
}

std::vector<Rule *> RuleDatabaseFactory::fetchAll( void ) {
    std::vector<Rule *> rules;
    
    // TODO Implement.
    
    return ( rules );
}
