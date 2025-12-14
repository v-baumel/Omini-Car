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

const int MAX_PWM = 255;

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

DCMotor MFL, MFR, MBL, MBR; // Motor Front Left, Motor Front Right, Motor Back Left, Motor Back Right

void setup(){
    Serial.begin(9600);       

    // Motor 1 (Front Left): ENA=D3, IN1=D2, IN2=D4
    MFL.init(3, 2, 4);      

    // Motor 2 (Front Right): ENB=D5, IN3=D6, IN4=D7
    MFR.init(5, 6, 7);    

    // Motor 3 (Back Left): ENA=D9, IN1=D8, IN2=D12
    MBL.init(9, 8, 12);    

    // Motor 4 (Back Right): ENB=D10, IN3=D11, IN4=D13
    MBR.init(10, 11, 13);

    Serial.println("TESTE INICIADO");
}

void loop(){
    Serial.println("Iniciando teste do motor frontal esquerdo");
    MFL.setPower(1);
    delay(1000);
    MFL.setPower(0.4);
    delay(1000);
    MFL.setPower(0);
    delay(1000);
    MFL.setPower(-0.4);
    delay(1000);
    MFL.setPower(-1);
    delay(1000);
    MFL.setPower(0);

    Serial.println("Iniciando teste do motor frontal direito");
    MFR.setPower(1);
    delay(1000);
    MFR.setPower(0.4);
    delay(1000);
    MFR.setPower(0);
    delay(1000);
    MFR.setPower(-0.4);
    delay(1000);
    MFR.setPower(-1);
    delay(1000);
    MFR.setPower(0);

    Serial.println("Iniciando teste do motor traseiro esquerdo");
    MBL.setPower(1);
    delay(1000);
    MBL.setPower(0.4);
    delay(1000);
    MBL.setPower(0);
    delay(1000);
    MBL.setPower(-0.4);
    delay(1000);
    MBL.setPower(-1);
    delay(1000);
    MBL.setPower(0);

    Serial.println("Iniciando teste do motor traseiro direito");
    MBR.setPower(1);
    delay(1000);
    MBR.setPower(0.4);
    delay(1000);
    MBR.setPower(0);
    delay(1000);
    MBR.setPower(-0.4);
    delay(1000);
    MBR.setPower(-1);
    delay(1000);
    MBR.setPower(0);

}