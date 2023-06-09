void checkIfDeviceAlreadyExistsInBackend(int id) {

  Serial.print("test");

  if (id <= 0) {
    if (WiFi.status() == WL_CONNECTED) {
      digitalWrite(16, LOW);
      WiFiClient client;
      HTTPClient http;

      Serial.print("[HTTP] begin...\n");
      // configure traged server and url
      http.begin(client, "http://" SERVER_IP "/api/soilmoisture");  // HTTP
      http.addHeader("Content-Type", "application/json");

      Serial.print("[HTTP] POST...\n");

      int httpCode = http.POST("{\"moisture\":" + (String)reading + ", \"deviceid\":" + (String)DEVICE_ID + "}");
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
      return;
    }
  }

  if (WiFi.status() == WL_CONNECTED) {
    digitalWrite(16, LOW);
    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    // configure traged server and url
    http.begin(client, "http://" SERVER_IP "/api/soilmoisture");  // HTTP
    http.addHeader("Content-Type", "application/json");

    Serial.print("[HTTP] POST...\n");

    int httpCode = http.POST("{\"moisture\":" + (String)reading + ", \"deviceid\":" + (String)DEVICE_ID + "}");
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