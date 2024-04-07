#ifndef pHSensor_h
#define pHSensor_h

#include <Arduino.h>

class pHSensor {
  public:
    pHSensor(int pin);
    void setupSensor();
    float readpHValue();
  private:
    int _analogInPin;
    unsigned long int _avgValue;
    int _buf[10], _temp;
};

#endif
