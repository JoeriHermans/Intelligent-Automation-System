/**
 * Utility functions used in the startup process of IAS. This will
 * initialise all crypographic libraries and start the application
 * requested by the user.
 *
 * @date                    28 04 2016
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
// END Includes. /////////////////////////////////////////////////////

int main(const int argc, const char ** argv);

bool requested_client(const int argc, const char ** argv);

bool requested_controller(const int argc, const char ** argv);

bool requested_eventstream(const int argc, const char ** argv);

bool requested_generate_hash(const int argc, const char ** argv);

bool requested_server(const int argc, const char ** argv);

bool requested_version(const int argc, const char ** argv);

void cleanup_logger(void);

void cleanup_ssl(void);

void display_logo(void);

void initialize_random_number_generator(void);

void initialize_ssl(void);

void run_application(const int argc, const char ** argv);

void show_version(void);

void start_client(const int argc, const char ** argv);

void start_controller(const int argc, const char ** argv);

void start_eventstream(const int argc, const char ** argv);

void start_generate_hash(const int argc, const char ** argv);

void start_server(const int argc, const char ** argv);

void usage(void);
