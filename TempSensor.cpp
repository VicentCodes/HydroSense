#include "TempSensor.h"

TempSensor::TempSensor(int pinDatos) : _oneWire(pinDatos), _sensorDS18B20(&_oneWire) {}

void TempSensor::setupSensor() {
    _sensorDS18B20.begin();
}

float TempSensor::readTemperature() {
    _sensorDS18B20.requestTemperatures();
    return _sensorDS18B20.getTempCByIndex(0);
}
