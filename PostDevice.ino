void checkIfDeviceAlreadyExistsInBackend(int id) {
  
  Serial.println(id);

  if (id <= 0) {
    if (WiFi.status() == WL_CONNECTED) {

      DynamicJsonDocument doc(1024);

      doc[String("name")] = deviceName;
      doc[String("ip")] = IpAddress2String(WiFi.localIP());
      
      String output;
      serializeJson(doc, output);

      WiFiClient client;
      HTTPClient http;

      http.begin(client, "http://" SERVER_IP "/api/Autodiscovery");  // HTTP
      http.addHeader("Content-Type", "application/json");

      int httpCode = http.POST(output);
      if (httpCode == HTTP_CODE_OK) {
        const String& payload = http.getString();

        DynamicJsonDocument doc(1024);
        deserializeJson(doc, payload);
        int id = doc[String("id")];
        Serial.print(id);
        EEPROM.write(deviceIdAdress, id);
        EEPROM.commit();
        deviceId = id;
        

      } else {
        Serial.print(httpCode);
        Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }
      http.end();
      return;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {

    DynamicJsonDocument doc(1024);

    doc[String("id")] = id;
    doc[String("name")] = deviceName;
    doc[String("ip")] = IpAddress2String(WiFi.localIP());

    String output;
    serializeJson(doc, output);

    digitalWrite(16, LOW);
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/api/startup-checkin");  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] PUT...\n");

    int httpCode = http.PUT(output);
    if (httpCode == HTTP_CODE_OK) {
      const String& payload = http.getString();
      Serial.println("received payload:\n<<");
      Serial.println(payload);
      Serial.println(">>");
    } else {
      Serial.print(httpCode);
      Serial.printf("[HTTP] POST... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }
    
    http.end();
  }

}

String IpAddress2String(const IPAddress& ipAddress)
{
    return String(ipAddress[0]) + String(".") +
           String(ipAddress[1]) + String(".") +
           String(ipAddress[2]) + String(".") +
           String(ipAddress[3]);
}