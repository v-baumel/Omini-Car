#include <Arduino.h>
#include <SoftwareSerial.h>
SoftwareSerial BT(2, 3);

void setup() {
  Serial.begin(9600);
  BT.begin(9600); // taxa padrão do HC-05

  Serial.println("Hearing HC-05...");
}

void loop() {
  if (BT.available()) {
    char c = BT.read();
    Serial.print("Input recieved: ");
    Serial.println(c);
  }
}
