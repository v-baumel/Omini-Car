#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include <Arduino.h>

class DCMotor {
public:
    DCMotor();
    void init(int enablePin, int in1Pin, int in2Pin);
    void setPower(float power);
private:
    int _enablePin;
    int _in1Pin;
    int _in2Pin;
};

#endif