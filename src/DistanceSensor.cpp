#include <Arduino.h>
#include <ArduinoJson.h>
#include "DistanceSensor.h"


//----------------------------------------------------------------------------\\
//
//    Public
//
//----------------------------------------------------------------------------\\

DistanceSensor::DistanceSensor(uint8_t echoPin, uint8_t trigPin) {
  _echoPin = echoPin;
  _trigPin = trigPin;
  
  pinMode(_echoPin,INPUT);
  pinMode(_trigPin, OUTPUT);
}

DistanceSensor::~DistanceSensor() {
  pinMode(_trigPin, INPUT);
}

void DistanceSensor::update() {
  // Prep trig pin
  digitalWrite(_trigPin, LOW);
  delayMicroseconds(2);
  
  // Send ping
  digitalWrite(_trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(_trigPin, LOW);
  
  microseconds = pulseIn(_echoPin, HIGH);
  inches = microsecondsToInches();
  centimeters = microsecondsToCentimeters();
}

JsonObject& DistanceSensor::createJsonObject(JsonObject& node) {
  JsonObject& distance_sensor = node.createNestedObject("distance_sensor");
  distance_sensor["type"] = "distance";
  distance_sensor["duration"] = microseconds; 
  distance_sensor["inches"] = inches;
  distance_sensor["centimeters"] = centimeters;
  
  return distance_sensor;
}

//----------------------------------------------------------------------------\\
//
//    Private
//
//----------------------------------------------------------------------------\\

unsigned long DistanceSensor::microsecondsToInches() {
  return microseconds / 148;
}

unsigned long DistanceSensor::microsecondsToCentimeters() {
  return microseconds / 58;
}