#ifndef TempSensor_h
#define TempSensor_h

#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>

class TempSensor {
  public:
    TempSensor(int pinDatos);
    void setupSensor();
    float readTemperature();
  private:
    OneWire _oneWire;
    DallasTemperature _sensorDS18B20;
};

#endif
