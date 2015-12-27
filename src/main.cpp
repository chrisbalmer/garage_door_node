#include <ESP8266WiFi.h>
#include <ArduinoJson.h>
#include "LightSensor.h"
#include "DistanceSensor.h"
#include "ssid.h"

const int httpPort = 80;
const int photoresistorPin = A0;  // Yellow
const int echoPin = 13;           // Blue
const int trigPin = 14;           // Green

unsigned long processTime;

WiFiServer server(httpPort);
LightSensor lightSensor(photoresistorPin);
DistanceSensor distanceSensor(echoPin, trigPin);


String HTMLHeader() {
  String header = "HTTP/1.1 200 OK\r\n";
  header += "Content-Type: text/html\r\n\r\n";
  return header;
}

void connectToWiFi() {
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println(WiFi.localIP());
}

void startWebServer() {
  server.begin();
  Serial.println("Server started.");
}

void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println("Start");
  
  connectToWiFi();
  startWebServer();
}

void loop() {
  processTime = millis();
  
  if (WiFi.status() != WL_CONNECTED) {
    Serial.print("WiFi not connected, status: ");
    Serial.print(WiFi.status());
    Serial.print(", time: ");
    Serial.println(millis());
    delay(500);
  }
  
  // Wait for a client connection.
  WiFiClient client = server.available();
  if (!client) {
    yield();
    return;
  }

  lightSensor.update();
  yield();

  distanceSensor.update();
  yield();
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& node = jsonBuffer.createObject();
  node["node"] = "garage_door1";
  node["time"] = millis();
  
  distanceSensor.createJsonObject(node);
  lightSensor.createJsonObject(node);
  
  Serial.println("New client");
  while (!client.available()) {
    yield();
  }
  
  String req = client.readStringUntil('\r');
  Serial.println(req);
  client.flush();
  
  String header = HTMLHeader();
  
  client.print(header);
  node.printTo(client);
  client.stop();
  yield();
  
  node.printTo(Serial);
  
  Serial.println("");
  Serial.println("Client disconnected.");
  
  processTime = millis() - processTime;
  Serial.print("Time to process data: ");
  Serial.print(processTime);
  Serial.println("ms.");
  Serial.println("");
}