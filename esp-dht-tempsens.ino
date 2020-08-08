#include "DHT.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h> 
#include <ESP8266mDNS.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>


#define DHTPIN 4
#define DHTTYPE DHT22

ESP8266WiFiMulti wifiMulti;
ESP8266WebServer server(80);
DHT dht(DHTPIN, DHTTYPE);

void handleRoot();
void handleJson();
void handleNotFound();


void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');

  wifiMulti.addAP("SSID1", "wifipassword1");
  //wifiMulti.addAP("SSID2", "wifipassword2");
  //wifiMulti.addAP("SSID3", "wifipassword3");

  Serial.println("Connecting ...");
  int i = 0;
  while (wifiMulti.run() != WL_CONNECTED) {
    delay(500);
    Serial.print('.');
  }
  Serial.println('\n');
  Serial.print("Connected to ");
  Serial.println(WiFi.SSID());
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("temp-sens-01")) {
    Serial.println("mDNS responder started");
  } else {
    Serial.println("Error setting up MDNS responder!");
  }

  server.on("/", handleRoot);
  server.on("/json", handleJson);
  server.onNotFound(handleNotFound);

  server.begin();
  Serial.println("HTTP server started");

  dht.begin();
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  float temperature = dht.readTemperature();  
  server.send(200, "text/plain", String(temperature));
}

void handleJson() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  StaticJsonDocument<200> doc;
  doc["temperature"] = temperature;
  doc["humidity"] = humidity;

  String out;
  serializeJson(doc, out);
  server.send(200, "application/json", out);
}

void handleNotFound(){
  server.send(404, "text/plain", "404: Not found");
}
