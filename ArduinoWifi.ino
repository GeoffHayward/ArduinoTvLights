#include <SPI.h>
#include <WiFiNINA.h>
#include "arduino_secrets.h"

const char ssid[] = SECRET_SSID;        // your network SSID (name)
const char pass[] = SECRET_PASS;    // your network password (use for WPA, or use as key for WEP)


void arduinoWifi() {

  if (WiFi.status() != WL_CONNECTED) {
  
    // check for the WiFi module:
    if (WiFi.status() == WL_NO_MODULE) {
      Serial.println("Communication with WiFi module failed!");
      while (true); // don't continue
    }
 
    /*if (WiFi.firmwareVersion() < WIFI_FIRMWARE_LATEST_VERSION) {
      Serial.println(WiFi.firmwareVersion());
      Serial.println(WIFI_FIRMWARE_LATEST_VERSION);
      Serial.println("Please upgrade the firmware");
    }*/

    // attempt to connect to WiFi network:
    while (WiFi.status() != WL_CONNECTED) {
      if(WiFi.status() == WL_IDLE_STATUS) {
  
        // Switch on LED to indicate that connecting to wifi.
        digitalWrite(LED_BUILTIN, HIGH); 
        
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);

        Serial.println("before");
        // Connect to WPA/WPA2 network. Change this line if using open or WEP network:
        WiFi.begin(ssid, pass);
        Serial.println("after");
        delay(10000);
      }
    }
  
    if(WiFi.status() == WL_CONNECTED) {
  
      // Switch off LED to indicate that wifi is connected.
      digitalWrite(LED_BUILTIN, LOW); 
      
      Serial.println("Connected to WiFi");
    
      // print the SSID of the network you're attached to:
      Serial.print("SSID: ");
      Serial.println(WiFi.SSID());
    
      // print your board's IP address:
      IPAddress ip = WiFi.localIP();
      Serial.print("IP Address: ");
      Serial.println(ip);
    
      // print the received signal strength:
      long rssi = WiFi.RSSI();
      Serial.print("signal strength (RSSI):");
      Serial.print(rssi);
      Serial.println(" dBm");
    }
  }
}
