#include "Arduino.h"

class soilMoisture {
  public:
  
    soilMoisture(uint8_t pin, uint8_t powerPin);
    uint8_t soilMoisturePin;
    int makeReading(bool interactive);
    int getPin();
    int getPowerPin();
  private:

    uint8_t _pin;
    uint8_t _powerPin;
};