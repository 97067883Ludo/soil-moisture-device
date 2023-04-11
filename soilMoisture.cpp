#include "Arduino.h"
#include "soilMoisture.h"

soilMoisture::soilMoisture(uint8_t pin, uint8_t powerPin) {
  _pin = pin;
  _powerPin = powerPin;
  pinMode(pin, INPUT);
  pinMode(powerPin, OUTPUT);
}


int soilMoisture::makeReading() {

  soilMoisture::allReadingsAddedUp = 0;
  // soilMoisture::makeIndividualReading(true);
  for(int i = 0; i < 10; i++) {
    soilMoisture::readings[i] = soilMoisture::makeIndividualReading(false);
    soilMoisture::allReadingsAddedUp += soilMoisture::readings[i];
    delay(60000);
    Serial.print(i);
    Serial.print(": ");
    Serial.println(soilMoisture::readings[i]);
  }

  return soilMoisture::allReadingsAddedUp / (sizeof(soilMoisture::readings) / sizeof(int)); 
}

int soilMoisture::getPin() {

  return _pin;
}

int soilMoisture::getPowerPin() {

  return _powerPin;
}

int soilMoisture::makeIndividualReading(bool interactive) {

  digitalWrite(soilMoisture::getPowerPin(), HIGH);
  delay(100);
  int currentValue = analogRead(soilMoisture::getPin());

  if(interactive) {
    Serial.print("Current value: ");
    Serial.println(currentValue);
  }

  digitalWrite(soilMoisture::getPowerPin(), LOW);

  return currentValue;
}