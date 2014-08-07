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

In the following subsections I will be discussing the different base entities
and their properties and role within IAS.

#### Technologies

A technology is in essence a model of a device / set of devices with which IAS
will be interacting with. Such a model consists of:

- _Members_: describe the state of a device which implements a technology. Note
that a member has a value type. 

 For example, a member of a light bulb could be
 _on_. This member describes whether a device which implements a technology 
 _light bulb_ is on or off.

- _Features_: are actions which can be performed by a device which implements the technology. Depending on the model of a feature, a feature could have an optional parameter with a value type.

As a result of the fact that technologies are just models of a physical technology, different controllers can have different implementations of specific a model. This abstraction allows for a whole range of devices which in the end achieve the same result (e.g., turning on a lamp), but which require a different set of actions to achieve that result (e.g., turning on a LED which is connected to an Arduino). 

#### Devices

Devices are entities which implement a certain technology, and which keep track
of their own state. As discussed above, a technology implements a set of
members and features. As a result, a device which implements a specific 
technology copies the members of the technology it implements and registers 
state updates from the controller to which the physical device is connected.

Users and the system can perform actions on a device. An action could
result in a state update, which a device will process.

#### Controllers

Bofore a user or the system can interact with a device which is associated with
a certain controller, the controller in question needsd to connect to the
server process. When a connection is mode, the controller will send an
authorization key, which in turn will be validated by IAS.

When the controller's authorization key has been accepted, a controller can
notify the server of specific device updates and execute received features.

#### Rules

Rules are entities which contain a set of condition sets and exactly one action
set. When the conditions in one of the condition sets are met, the rule will
execute the action set, which in turn will execute a set of device actions.

A condition set consists of a set of _dynamic conditions_ and / or
_static conditions_. A _dynamic condition_ compares the current value of two
different devices. This in constrast to a _static condition_ which will compare
the current value of a member of a certain device with a static value.