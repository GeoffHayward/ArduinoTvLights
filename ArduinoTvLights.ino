#include "arduino_secrets.h"

// Properties
const float ON_THRESHOLD  = AC_CURRENT_ON_THRESHOLD;
const float OFF_THRESHOLD = AC_CURRENT_OFF_THRESHOLD;


void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

  arduinoWifi();
  
  if(readACCurrentValue() >= ON_THRESHOLD) {
    // Verify with n many readings.
    for (int n = 3; 0 <= n && readACCurrentValue() >= ON_THRESHOLD; n--) {
      Serial.print(n);
      Serial.print(" - ");
      Serial.print(readACCurrentValue());
      Serial.println(" A - on");
      if(n == 0) {
        hueLightsOn(); 
        Serial.println("TV Lights on");
      } else {
        delay(200);
      }
    }
  }
  
  else if(readACCurrentValue() <= OFF_THRESHOLD) {
    // Verify with n many readings.
    for (int n = 5; 0 <= n && readACCurrentValue() <= OFF_THRESHOLD; n--) {
      Serial.print(n);
      Serial.print(" - ");
      Serial.print(readACCurrentValue());
      Serial.println(" A - off");
      if(n == 0) {
        hueLightsOff();
      } else {
        delay(200);
      }
    }
  }
  
  else {
    Serial.print(readACCurrentValue());
    Serial.println(" A - gray zone");
  }
  
  delay(200);
}
