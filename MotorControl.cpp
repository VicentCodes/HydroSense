#include "MotorControl.h"

MotorControl::MotorControl(int enaPin, int in1Pin, int in2Pin) {
  _ENA = enaPin;
  _IN1 = in1Pin;
  _IN2 = in2Pin;
}

void MotorControl::setupMotor() {
  pinMode(_ENA, OUTPUT);
  pinMode(_IN1, OUTPUT);
  pinMode(_IN2, OUTPUT); 
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);

  ledcSetup(_pwm_channel, _frequency, _resolution);
  ledcAttachPin(_ENA, _pwm_channel);
}

void MotorControl::extractWater() {

  ledcWrite(_pwm_channel, 255);
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  
}

void MotorControl::expelWater() {

  ledcWrite(_pwm_channel, 255);
  digitalWrite(_IN1, HIGH);
  digitalWrite(_IN2, LOW);
  
}

void MotorControl::changeSpeed() {
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, HIGH);
  
  for (int i = 0; i < 256; i++) {
    ledcWrite(_pwm_channel, i);
    delay(20);
  }
  
  for (int i = 255; i >= 0; --i) {
    ledcWrite(_pwm_channel, i);
    delay(20);
  }
  digitalWrite(_IN1, LOW);
  digitalWrite(_IN2, LOW);
}
