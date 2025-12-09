#include <Arduino.h>
#include <SoftwareSerial.h>

// RX, TX  (Arduino receives on RX)
SoftwareSerial BTSerial(2, 3);  // RX = 10, TX = 11

int joyX = 0;
int joyY = 0;

void setup() {
  Serial.begin(9600);       // For debugging in Serial Monitor
  BTSerial.begin(9600);     // For Bluetooth (HC-05)
  
  Serial.println("SoftwareSerial Bluetooth Joystick Reader");
}

void loop() {
  if (BTSerial.available()) {
    String data = BTSerial.readStringUntil('\n');  // Read until newline
    
    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      // Parse
      joyX = data.substring(0, commaIndex).toInt();
      joyY = data.substring(commaIndex + 1).toInt();

      // Debug
      Serial.print("X: ");
      Serial.print(joyX);
      Serial.print(" | Y: ");
      Serial.println(joyY);
    }
  }
}