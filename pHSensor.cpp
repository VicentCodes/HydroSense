#include "pHSensor.h"

pHSensor::pHSensor(int pin) {
  _analogInPin = pin;
}

void pHSensor::setupSensor() {
  // No es necesario realizar ninguna configuración específica para el sensor en el setup()
}

float pHSensor::readpHValue() {
  for(int i = 0; i < 10; i++) { 
    _buf[i] = analogRead(_analogInPin);
    delay(10);
  }
  
  for(int i = 0; i < 9; i++) {
    for(int j = i + 1; j < 10; j++) {
      if(_buf[i] > _buf[j]) {
        _temp = _buf[i];
        _buf[i] = _buf[j];
        _buf[j] = _temp;
      }
    }
  }
  
  _avgValue = 0;
  for(int i = 2; i < 8; i++)
    _avgValue += _buf[i];
  
  float pHVol = (float)_avgValue / 6 * 3.4469 / 4095;
  
  float phValue = -5.70 * pHVol + 21.34;
  
  return phValue;
}
