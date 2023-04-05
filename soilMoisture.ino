#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include "soilMoisture.h"

#define SERVER_IP "192.168.178.42"

#ifndef STASSID
#define STASSID "Tielbeke"
#define STAPSK "123456789"
#endif

soilMoisture soilMoistureSen(A0, 16);
int readings [10];

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  WiFi.begin(STASSID, STAPSK);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  soilMoistureSen.makeReading(false);

  if(WiFi.status() == WL_CONNECTED) {
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/postplain/");  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");
    // start connection and send HTTP header and body
    int httpCode = http.POST("{\"hello\":\"world\"}");
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();
        Serial.println("received payload:\n<<");
        Serial.println(payload);
        Serial.println(">>");
      }
     else {
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }


  delay(500);
}
