#include <Arduino.h>
#include <SoftwareSerial.h>
#include "mecanum.h"
#include "DCMotor.h"

SoftwareSerial BTSerial(A0, A1); // motores vão usar todos os digitais, dá pra usar analog como digital

DCMotor MFL, MFR, MBL, MBR;

int x = 0; 
int y = 0; 
int z = 0; 

void setPower(MecanumOutput P){
      MFR.setPower(P.fr);
      MFL.setPower(P.fl);
      MBR.setPower(P.br);
      MBL.setPower(P.bl);
}

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

void loop() {
  if (BTSerial.available()) {
    String data = BTSerial.readStringUntil('\n');  
    int comma1Index = data.indexOf(',');
    int comma2Index = data.indexOf(',', comma1Index + 1);
    
    if (comma1Index != -1 && comma2Index != -1) {
      x = data.substring(0, comma1Index).toInt();
      y = data.substring(comma1Index + 1, comma2Index).toInt();
      z = data.substring(comma2Index + 1).toInt();

      // para debug
      Serial.print("X: ");
      Serial.print(x);
      Serial.print(" | Y: ");
      Serial.print(y);
      Serial.print(" | Z: ");
      Serial.println(z);

      setPower(mecanum_from_vector(x,y,z));
    } 
    else setPower({0,0,0,0});

  } else setPower({0,0,0,0});
}