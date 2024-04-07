#ifndef MotorControl_h
#define MotorControl_h

#include <Arduino.h>

class MotorControl {
  public:
    MotorControl(int enaPin, int in1Pin, int in2Pin);
    void setupMotor();
    void extractWater();
    void expelWater();
    void changeSpeed();
  private:
    int _ENA;
    int _IN1;
    int _IN2;
    const int _frequency = 500;
    const int _pwm_channel = 0;
    const int _resolution = 8;
};

#endif
