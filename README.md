# MCWMQTT

MCWMQTT is an Omnis Studio external component (xcomp) that provides integration with an MQTT broker, allowing applications to publish messages and manage connections using the MQTT protocol.
This project uses the C++ version of the Paho MQTT library, as it is the only version that provides support for MQTT v5 features.


## Features

- Connect and disconnect from an MQTT broker
- Publish messages to topics
- Configure QoS, retained messages, and timeouts
- Support for authentication (username/password)
- Automatic reconnect option
- MQTT session and message expiry configuration (MQTT v5)
- Error reporting and connection status monitoring


## Todo:
- Implement subscription methods (subscribe/unsubscribe)


## Windows
- Install **vcpkg**
- Install the required library: vcpkg install paho-mqttpp3:x46-windows or paho-mqttpp3:x46-windows-static (for static linking)


## Linux
On Windows, vcpkg installs the correct version of the library automatically.
However, on Linux, the package manager does not provide a compatible version.
For this reason, the library must be built manually using the following commands:

cmake \
  -DPAHO_BUILD_STATIC=ON \
  -DPAHO_BUILD_SHARED=OFF \
  -DPAHO_WITH_MQTT_C=ON \
  -DCMAKE_POSITION_INDEPENDENT_CODE=ON \
  -DPAHO_WITH_SSL=ON

make && sudo make install
