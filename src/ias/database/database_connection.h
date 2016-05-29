/**
 * An interface which describes the actions of a database connection.
 * This interface will be used to provide a general and uniform
 * looking API.
 *
 * @date                    29 05 2016
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
#include <string>

// END Includes. /////////////////////////////////////////////////////

#ifndef IAS_DATABASE_CONNECTION_H_
#define IAS_DATABASE_CONNECTION_H_

namespace ias {

class database_connection {

    public:

    // BEGIN Class constants. ////////////////////////////////////////////////

    /**
     * Holds the default host of a database server, which is "localhost".
     */
    static const char kDefaultHost[];

    // END Class constants. //////////////////////////////////////////////////

    private:

    // BEGIN Private members. ////////////////////////////////////////////////

    /**
     * Properties associated with a database connection.
     */
    std::string mHost;
    std::string mPort;
    std::string mSchema;
    std::string mUsername;
    std::string mPassword;

    // END Private members. //////////////////////////////////////////////////

    // BEGIN Private methods. ////////////////////////////////////////////////

    inline void set_host(const std::string & host) {
        // Checking the preconditions.
        assert(!host.empty());

        mHost = host;
    }

    inline void set_port(const std::string & port) {
        // Checking the precondition.
        assert(!port.empty());

        mPort = port;
    }

    inline void set_schema(const std::string & schema) {
        // Checking the precondition.
        assert(!schema.empty());

        mSchema = schema;
    }

    inline void set_username(const std::string & username) {
        // Checking the precondition.
        assert(!username.empty());

        mUsername = username;
    }

    inline void set_password(const std::string & password) {
        // Checking the precondition.
        assert(!password.empty());

        mPassword = password;
    }

    // END Private methods. //////////////////////////////////////////////////

    protected:

    // BEGIN Protected methods. //////////////////////////////////////////////

    const std::string & get_host(void) const {
        return mHost;
    }

    const std::string & get_port(void) const {
        return mPort;
    }

    const std::string & get_username(void) const {
        return mUsername;
    }

    const std::string & get_password(void) const {
        return mPassword;
    }

    const std::string & get_schema(void) const {
        return mSchema;
    }

    // END Protected methods. ////////////////////////////////////////////////

    public:

    // BEGIN Constructor. ////////////////////////////////////////////////////

    database_connection(const std::string & host,
                        const std::string & port,
                        const std::string & schema,
                        const std::string & username,
                        const std::string & password) {
        set_host(host);
        set_port(port);
        set_schema(schema);
        set_username(username);
        set_password(password);
    }

    // END Constructor. //////////////////////////////////////////////////////

    // BEGIN Destructor. /////////////////////////////////////////////////////

    virtual ~database_connection(void) = default;

    // END Destructor. ///////////////////////////////////////////////////////

    // BEGIN Public methods. /////////////////////////////////////////////////

    virtual bool open_connection(void) = 0;

    virtual bool close_connection(void) = 0;

    // END Public methods. ///////////////////////////////////////////////////

    // BEGIN Public static methods. //////////////////////////////////////////
    // END Public static methods. ////////////////////////////////////////////

};

};

#endif
