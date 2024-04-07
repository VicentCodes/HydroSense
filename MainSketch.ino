#include <Arduino.h>

#include "TDS.h"
#include "MotorControl.h"
#include "TempSensor.h"
#include "pHSensor.h"



// TDS Pins NO SETUP
const int pinTDS = 11; // Pin TDS
TDS tdsSensor(pinTDS);
//

// Pumb Water Pins
const int ENA = 10;
const int IN1 = 11;
const int IN2 = 12;
MotorControl motor(ENA, IN1, IN2);
//

// DS18B20 Temp pins
const int pinDatosDQ = 13;
TempSensor temperatureSensor(pinDatosDQ);
//

//PH sensor pins NO SETUP
const int analogInPin = 35;
pHSensor pH_Sensor(analogInPin);
//




void setup() {
  Serial.begin(9600);
  motor.setupMotor(); //motor Setup
  temperatureSensor.setupSensor(); // DS18B20 Setup
}

void loop() {
  int tdsValue = tdsSensor.readTDS();
  motor.extractWater();
  motor.expelWater();
 float temperature = temperatureSensor.readTemperature(); // C°
 float pHValue = pH_Sensor.readpHValue();
  
  
}
