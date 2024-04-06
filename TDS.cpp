#include "TDS.h"

TDS::TDS(int pin) {
  _pinTDS = pin;
  pinMode(_pinTDS, INPUT);
}

int TDS::readTDS() {
  int rawValue = analogRead(_pinTDS);
  return rawValue;
}
