#include <SoftwareSerial.h>
#define RELAY_PIN 7

const float THRESHOLD = 5.0;   // ml

SoftwareSerial espSerial(10, 11);  // Rx=10, Tx=11

void setup() {
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  Serial.begin(9600);
  espSerial.begin(9600);
}

void loop() {
  if (espSerial.available()) {
    String volStr = espSerial.readStringUntil('\n');
    float vol = 0;
    vol = volStr.toFloat();
    Serial.print("Received volume: ");
    Serial.println(vol);

    if (vol > THRESHOLD) {
      unsigned long duration = (unsigned long)(vol * 1000);  // giả sử ~1 ml/s
      digitalWrite(RELAY_PIN, HIGH);
      delay(duration);
      digitalWrite(RELAY_PIN, LOW);
      Serial.print("Pumped ");
      Serial.print(vol);
      Serial.println(" ml");
    } else {
      Serial.println("Below threshold, skip pump");
    }
  }
}