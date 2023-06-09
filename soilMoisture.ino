#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "soilMoisture.h"
#include <EEPROM.h>
#include <ArduinoJson.h>

#define SERVER_IP "192.168.178.69:5000"
#define EEPROM_SIZE 12

String deviceName = "test";
byte deviceIdAdress = 0;
int deviceId = 0;

#ifndef STASSID
#define STASSID "Tielbeke"
#define STAPSK "123456789"
#endif

soilMoisture soilMoistureSen(A0, 5);
int readings [10];

void setup() {
  // put your setup code here, to run once:
  EEPROM.begin(EEPROM_SIZE);

  // EEPROM.write(deviceIdAdress, 0);
  // EEPROM.commit();

  Serial.begin(9600);
  pinMode(16, OUTPUT);
  digitalWrite(16, HIGH);
  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  digitalWrite(16, LOW);
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  deviceId = EEPROM.read(deviceIdAdress); 

  Serial.print("EEPROM DeviceId: " + deviceId);
  
  checkIfDeviceAlreadyExistsInBackend(deviceId); 

}

void loop() {

  int reading = soilMoistureSen.makeReading();

  Serial.print(reading);

  if(WiFi.status() == WL_CONNECTED) {
    digitalWrite(16, LOW);
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/api/soilmoisture");  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");

    int httpCode = http.POST("{\"moisture\":"+ (String)reading +", \"deviceid\":"+ (String)deviceId +"}");
    if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
     else {
      Serial.print(httpCode);
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  } else {
    digitalWrite(16, HIGH);
    WiFi.reconnect();
  }
}
