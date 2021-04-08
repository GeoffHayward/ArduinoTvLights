#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

const char ssid[] = SECRET_SSID;        // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)

void WiFiKeepConnection(){
 int StatusWiFi = WiFi.status();
 if(StatusWiFi == WL_CONNECTION_LOST || StatusWiFi == WL_DISCONNECTED){
  digitalWrite(LED_BUILTIN, LOW); // LED Off to show disconnected
  WiFiConnect();
 }
}

void WiFiConnect(){
 int StatusWiFi = WL_IDLE_STATUS;
 while(StatusWiFi != WL_CONNECTED){
   StatusWiFi = WiFi.begin(ssid,pass);
   if(StatusWiFi == WL_CONNECTED) {
    digitalWrite(LED_BUILTIN, HIGH); // LED on to show disconnected
   }
   else {
    delay(500);
   }
 }
}
