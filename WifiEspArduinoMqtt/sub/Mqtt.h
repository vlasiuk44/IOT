#include <PubSubClient.h>

PubSubClient mqtt_client(network_client);

String mqtt_broker = "broker.emqx.io";
int mqtt_port = 1883;

void callback(char* topic, byte* payload, unsigned int length){
  String str = "";

  for (int i = 0; i < length; i++){
    str += (char)payload[i];
  }

  if (str == "on") {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }

  Serial.println(str);
  Serial.println("---------------");
}

void MQTT_init() {
  mqtt_client.setServer(mqtt_broker.c_str(), mqtt_port);
  mqtt_client.setCallback(callback);
  while(!mqtt_client.connected()) {
    if (mqtt_client.connect("ESP8266")) {
      Serial.println("connected");
    } else {
      Serial.print("failed with state ");
      Serial.println(mqtt_client.state());
      delay(2000);
    }
  }
}