#include "DCMotor.h"

const int MAX_PWM = 255;

DCMotor::DCMotor() {
}

void DCMotor::init(int enablePin, int in1Pin, int in2Pin) {
    _enablePin = enablePin;
    _in1Pin = in1Pin;
    _in2Pin = in2Pin;

    pinMode(_enablePin, OUTPUT);
    pinMode(_in1Pin, OUTPUT);
    pinMode(_in2Pin, OUTPUT);
    setPower(0.0);
}

void DCMotor::setPower(float power) {
    float clampedPower = constrain(power, -1.0, 1.0);
    int pwmValue = (int)(abs(clampedPower) * MAX_PWM);
    if (clampedPower > 0.0) {
        digitalWrite(_in1Pin, HIGH);
        digitalWrite(_in2Pin, LOW);
    } else if (clampedPower < 0.0) {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, HIGH);
    } else {
        digitalWrite(_in1Pin, LOW);
        digitalWrite(_in2Pin, LOW);
    }

    analogWrite(_enablePin, pwmValue);
}