#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

// Properties
const String hue_username = HUE_USERNAME;
const int hue_light = HUE_LIGHT;
const String LIGHT_ON_COMMAND  = "{\"on\": true }";
const String LIGHT_OFF_COMMAND = "{\"on\": false }";

// Variables
WiFiClient client;
bool hue_light_is_on = false;

void hueLightsOn(){
  if(!hue_light_is_on) {
    sendCommand(LIGHT_ON_COMMAND);
    hue_light_is_on = true;
  } else {
    Serial.println("TV Lights are on!");
  }
}

void hueLightsOff(){
  if(hue_light_is_on) {
    sendCommand(LIGHT_OFF_COMMAND);
    hue_light_is_on = false;
  } else {
    Serial.println("TV Lights are off!");
  }
}

void sendCommand(String command){
  if(client.connect(HUE_BRIDGE, 80)) {
      // if connected:
      Serial.println("Connected to server");

      client.println("PUT /api/" + hue_username + "/lights/" + hue_light + "/state HTTP/1.1");
      client.println("Host: " + String(HUE_BRIDGE));
      client.println("Content-Type: text/plain;charset=UTF-8");
      client.println("User-Agent: Arduino/1.0");
      client.print("Content-Length: ");
      client.println(command.length());
      client.println(); // end HTTP header
      client.println(command);

      bool read = false;
      while(client.connected()) {
        if(client.available()) {
          char c = client.read();
          Serial.print(c);
          read = true;
        } else if(read) {
          client.stop();
        }
      }
      
      // the server's disconnected, stop the client:
      client.stop();
      Serial.println();
      Serial.println("disconnected");
      
  } else {
    Serial.println("connection failed");
  }
}
