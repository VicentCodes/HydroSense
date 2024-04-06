#include <Arduino.h>
#include "TDS.h"

// TDS Pins
const int pinTDS = 11; // Pin TDS
TDS tdsSensor(pinTDS);
//



void setup() {
  Serial.begin(9600);
}

void loop() {
  int tdsValue = tdsSensor.readTDS();
  
  Serial.print("Valor de TDS: ");
  Serial.println(tdsValue);

  delay(1000); // Espera un segundo antes de la próxima lectura
}
