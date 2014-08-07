Intelligent Automation System 0.1.0
===================================

A dynamic automation system which doesn't require additional plugins to model
and automate an environment.

Installation
------------

```sh
git clone https://github.com/JoeriHermans/IntelligentAutomationSystem.git ias
cd ias
make
sudo make install
```

#### Requirements

In order to build or run IAS, you will need to install the following dependencies:
- libmysqlclient (or libmariadbclient)
- clang 3.4 (or higher)
- Linux 2.6.18 (or higher)

#### Database

Since IAS currently only supports a `mysql` driver. You will need to run the
`ias.sql` file in your MySQL installation to produce a database and the
required tables.

#### Configuration

When running `sudo make install`, the makefile will create default configuration files in `/etc/ias/configuration`.

##### Server configuration

###### /etc/ias/server

```sh
# IAS 0.1 server configuration.
# -----------------------------
#
# This the the IAS server configuration file.

# Database configuration.
# In IAS 0.1 only the MySQL database driver is currently supported.
database_driver     = mysql
database_username   = username
database_password   = password
database_schema     = schema
database_host       = 127.0.0.1

# Network configuration.
network_bind_port   = 5000

# Security settings.
security_presalt    = hash_presalt
security_postsalt   = hash_postsalt
```

##### Controller configuration

###### /etc/ias/configuration/controller

```sh
# IAS 0.1 controller configuration.
# ---------------------------------
#
# This the the IAS controller configuration file.

# Basic controller settings.
# The controller identifier is the unique identifier of the controller.
controller_identifier = server0
# The security code which is associated with the specified controller identifier.
# This setting will be used to authenticate the controller with the IAS server.
controller_security_code = securityserver0

# IAS server settings.
server_address  = 127.0.0.1
server_port     = 5000

# Device list.
# In this file you specify the processes which need to be initiated
# to start the device processes.
devices         = /etc/ias/configuration/controller_devices

```

###### /etc/ias/configuration/controller_devices

```sh
# IAS 0.1 controller devices configuration.
# -----------------------------------------
#
# This the the IAS controller configuration file.
# In this file you will specify the unique device identifiers with the
# processes which need to be called by the system to initiate a device process.
#
# Example:
#
# device0
# /usr/bin/python3 /home/ias/scripts/weather.py [arguments]
#
# The first line indicates the device identifier, this way the controller knows
# what devices are allowed to connect. Note that the device process needs to
# authenticate itself with the controller service.
#
# The next line indicates the process which needs to be called by the
# system (with possible arguments).
#
```

Architecture
------------

TODO