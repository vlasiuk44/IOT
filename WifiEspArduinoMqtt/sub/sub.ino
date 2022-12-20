#include "Config.h"
#include "Wifi.h"
#include "Server.h"
#include "Mqtt.h"
#include <SoftwareSerial.h>

#define echoPin 14
#define trigPin 12
#define senPin A0

long duration;
int distance;

SoftwareSerial swrSer(4, 5);

int getDistance() {
  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  return distance;
}

int getBright() {
  return analogRead(senPin);
}

void setup() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(senPin, INPUT);
  pinMode(ledPin, OUTPUT);

  Serial.begin(9600);
  swrSer.begin(9600);

  WIFI_init(false);
  server_init();
  MQTT_init();
  
  while(!Serial) {}
  while(!swrSer) {}

  mqtt_client.subscribe(String("lab/dungeon/cv9t").c_str());
}

void loop() {
  mqtt_client.loop();

  server.handleClient();

  int data;
  char prefix;

  if (isBright) {
    data = getBright();
    prefix = 'b';
  } else {
    data = getDistance();
    prefix = 'd';
  }

  swrSer.println(String(prefix) + String(data));

  // delay(250);
}
