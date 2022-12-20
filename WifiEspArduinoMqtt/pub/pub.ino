#include <SoftwareSerial.h>

SoftwareSerial swrSer(9, 10);

void setup() {
  Serial.begin(9600);
  swrSer.begin(9600);

  while (!Serial) {}
  while (!swrSer) {}
}

void loop() {
  if (swrSer.available() > 0) {
    Serial.write(swrSer.read());
  }
}
