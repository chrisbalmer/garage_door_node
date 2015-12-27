#include <Arduino.h>
#include <ArduinoJson.h>
#include "LightSensor.h"

//----------------------------------------------------------------------------\\
//
//    Public
//
//----------------------------------------------------------------------------\\

LightSensor::LightSensor(int pin) {
	_photoresistorPin = pin;

	pinMode(_photoresistorPin, INPUT);
}

void LightSensor::update() {
	light = analogRead(_photoresistorPin);
}

JsonObject& LightSensor::createJsonObject(JsonObject& node) {
	JsonObject& light_sensor = node.createNestedObject("light_sensor");
  light_sensor["type"] = "photoresistor";
  light_sensor["light"] = light;
	
	return light_sensor;
}