#include "Arduino.h"
#include "soilMoisture.h"

soilMoisture::soilMoisture(uint8_t pin, uint8_t powerPin) {
  _pin = pin;
  _powerPin = powerPin;
  pinMode(pin, INPUT);
  pinMode(powerPin, OUTPUT);
}

int soilMoisture::makeReading(bool interactive = false) {
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

int soilMoisture::getPin() {
  return _pin;
}

int soilMoisture::getPowerPin() {
  return _powerPin;
}