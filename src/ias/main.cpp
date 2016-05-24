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

// System dependencies.
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <openssl/conf.h>
#include <openssl/engine.h>
#include <openssl/bio.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

// Application dependencies.
#include <ias/main.h>
#include <ias/application/constants.h>
#include <ias/util/util.h>

// END Includes. /////////////////////////////////////////////////////

int main(const int argc, const char ** argv) {
    // Initialize dependencies.
    initiailze_rnadom_number_generator();
    initialize_ssl();

    return EXIT_SUCCESS;
}

void initialize_random_number_generator(void) {
    srand(static_cast<unsigned int>(time(0)));
}

void initialize_ssl(void) {

}
