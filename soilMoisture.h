#include "Arduino.h"

class soilMoisture {
  public:

    soilMoisture(uint8_t pin, uint8_t powerPin);
    uint8_t soilMoisturePin;
    int makeReading();
    int getPin();
    int getPowerPin();
    int makeIndividualReading(bool interactive);
  private:

    uint8_t _pin;
    uint8_t _powerPin;
    int readings[10];
    int allReadingsAddedUp;
};