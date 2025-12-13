#include <Arduino.h>
#include <SoftwareSerial.h>
#include "mecanum.h"
#include "DCMotor.h"

DCMotor MFL, MFR, MBL, MBR; // Motor Front Left, Motor Front Right, Motor Back Left, Motor Back Right
void setPower(MecanumOutput P){
  Serial.print("FL: ");
  Serial.print(P.fl);
  Serial.print(" | FR: ");
  Serial.print(P.fr);
  Serial.print(" | BL: ");
  Serial.print(P.bl);
  Serial.print(" | BR: ");
  Serial.println(P.br);

  MFR.setPower(P.fr);
  MFL.setPower(P.fl);
  MBR.setPower(P.br);
  MBL.setPower(P.bl);
}

SoftwareSerial BTSerial(A0, A1);  // RX, TX

void setup() {
  Serial.begin(9600);       
  BTSerial.begin(9600);

  // Motor 1 (Front Left): ENA=D3, IN1=D2, IN2=D4
  MFL.init(3, 2, 4);      
  
  // Motor 2 (Front Right): ENB=D5, IN3=D6, IN4=D7
  MFR.init(5, 6, 7);    

  // Motor 3 (Back Left): ENA=D9, IN1=D8, IN2=D12
  MBL.init(9, 8, 12);    
  
  // Motor 4 (Back Right): ENB=D10, IN3=D11, IN4=D13
  MBR.init(10, 11, 13);

  Serial.println("OMINICAR ATIVADO");
}


// milis usa unsigned long
unsigned long lastBT = 0;  
unsigned long BT_TIMEOUT = 2000; // tempo para desligar o bluetooth caso não haja input 
float x = 0; 
float y = 0; 
float z = 0; 


void loop() {
  if (BTSerial.available()) {
    lastBT = millis();

    String data = BTSerial.readStringUntil(';');
    //Serial.println(data);


    int c1 = data.indexOf(',');
    int c2 = data.indexOf(',', c1 + 1);

    if (c1 != -1 && c2 != -1) {
      x = data.substring(0, c1).toFloat();
      y = data.substring(c1 + 1, c2).toFloat();
      z = data.substring(c2 + 1).toFloat();

        // Serial.print("x=");
        // Serial.print(x);
        // Serial.print(" y=");
        // Serial.print(y);
        // Serial.print(" z=");
        // Serial.println(z);

      setPower(mecanum_from_vector(x, y, z));
    }
  }

  if (millis() - lastBT > BT_TIMEOUT) {
    setPower(MecanumOutput{0,0,0,0}); // desilgar os motores se parar de receber bluetooth por muito tempo
    lastBT = millis();
  }
}
