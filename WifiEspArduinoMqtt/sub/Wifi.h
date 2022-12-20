#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WiFiMulti.h>

ESP8266WiFiMulti wifiMulti;
WiFiClient network_client;

String ip = "IP unset";
String password = "12345678";
String ssid_prefix = "ESP8266_cv9t";

char* ssidCLI = "Test123";
char* passwordCLI = "ubuntu12";

String id(){
  uint8_t mac[WL_MAC_ADDR_LENGTH];
  WiFi.softAPmacAddress(mac);
  String macID = String(mac[WL_MAC_ADDR_LENGTH - 2], HEX) + String(mac[WL_MAC_ADDR_LENGTH - 1], HEX);
  macID.toUpperCase();
  return macID;
}

bool StartAPMode() {
  IPAddress apIP(192, 168, 4, 1);
  WiFi.disconnect();
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, apIP, IPAddress(255, 255, 255, 0));
  WiFi.softAP((ssid_prefix + " " + id()).c_str(), password.c_str());
  Serial.println("");
  Serial.println("WiFi up in AP mode with name: "+ ssid_prefix + " " + id());
  return true;
}

void StartCLIMode() {
  wifiMulti.addAP(ssidCLI, passwordCLI);
  while(wifiMulti.run() != WL_CONNECTED) {
  }
}

void WIFI_init(bool mode_ap) {
  if (mode_ap) {
    StartAPMode();
    ip = WiFi.softAPIP().toString();
  } else {
    StartCLIMode();
    ip = WiFi.localIP().toString();
  }
  Serial.println("IP address: ");
  Serial.println(ip);  
}