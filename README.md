# Garage Door Node

## Description

This is the first of my home non-IoT nodes. This node monitors a garage door and the light level inside the garage. This data is kept in a Json object which is offered up via a self hosted website that can be polled by a central home management device/system.

The node is a dumb node, it does not decide if the door is open or if the light is on. It only reports data from the sensors. A management system is required to collect the data and make decisions based on it.

My goal is to build many such nodes and then also release a central management system that will poll the nodes and report the data via a local website and/or a display.

### Door Monitor

This monitor is a distance sensor that should be positioned in a spot that it can measure the distance to the garage door. This data can be used to determine if the door is open or closed. If the distance is outside of a range, the management system can report the door is opened. Or if it falls inside of the range, then the door should be considered closed.

The sensor used is an ultrasonic distance sensor, HC-SR04. The code is currently designed for a 4 pin unit (i.e. power, ground, echo and trig pins).

### Light Monitor

This monitor is a light sensor that reports back a measure of light based on the voltage measurement from an analog pin. This data can be used to determine if the inside garage light is on when it is night (or if there is no outside light allowed into the garage). If you position the photoresistor next to the lightbulb itself, you can determine if it is on during the day as well.

The sensor used is a photoresistor.

*This program does not send data to the internet, everything is self contained on your local network.*

## Build

- Install [PlatformIO](http://platformio.org/#!/get-started)
- Install the [ArduinoJson](https://github.com/bblanchon/ArduinoJson) library:

```
platformio lib install 64
```

- Configure `platformio.ini`.
  - Set `lib_dir` path.
  - Set `env:` to the board you're using.
- Configure `ssid.h`.
	- Set `const char* ssid` to the SSID you wish to connect to.
	- Set `const char* password` to your WiFi password.