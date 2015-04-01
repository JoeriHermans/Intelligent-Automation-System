/**
 * A set of functions and method which assist the main function to set up
 * the requested feature of the Intelligent Automation System.
 *
 * @date                    Jul 2, 2014
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

#ifndef MAIN_H_
#define MAIN_H_

// BEGIN Includes. ///////////////////////////////////////////////////
// END Includes. /////////////////////////////////////////////////////

void startController( const int argc , const char ** argv );

void startServer( const int argc , const char ** argv );

void startClient( const int argc , const char ** argv );

void startEventStream( const int argc , const char ** argv );

bool controllerRequested( const int argc , const char ** argv );

bool serverRequested( const int argc , const char ** argv );

bool clientRequested( const int argc , const char ** argv );

bool eventStreamRequested( const int argc , const char ** argv );

void initializeSsl( void );

void cleanupSsl( void );

void usage( void );

void cleanupLogger( void );

void displayLogo( void );

#endif /* MAIN_H_ */
