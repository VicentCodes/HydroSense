#ifndef TDS_h
#define TDS_h

#include <Arduino.h>

class TDS {
  public:
    TDS(int pin);
    int readTDS();
  private:
    int _pinTDS;
};

#endif
