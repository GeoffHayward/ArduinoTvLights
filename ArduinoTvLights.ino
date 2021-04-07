#include "arduino_secrets.h"
#include <SoftTimers.h>

// Properties
const float ON_THRESHOLD  = AC_CURRENT_ON_THRESHOLD;
const float OFF_THRESHOLD = AC_CURRENT_OFF_THRESHOLD;

// Variables
SoftTimer loopTimer;
SoftTimer onTimer;
SoftTimer offTimer;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  
  loopTimer.setTimeOutTime(200);
  loopTimer.reset();

  onTimer.setTimeOutTime(2000);
  onTimer.reset();

  offTimer.setTimeOutTime(1000);
  offTimer.reset();
}

void loop() {

  arduinoWifi();

  if(loopTimer.hasTimedOut()) {
    
    float ACCurrentValue = readACCurrentValue();

    Serial.print("Loop - ");
    Serial.print(ACCurrentValue);
    Serial.println(" A");

    if(ACCurrentValue  >= ON_THRESHOLD) {
      if(onTimer.hasTimedOut()) {
        // Serial.println("ON");
        hueLightsOn(); 
      }
    } 
    else {
      Serial.println("ON RESET");
      onTimer.reset();
    }

    
   if(ACCurrentValue  <= OFF_THRESHOLD) {
      if(offTimer.hasTimedOut()) {
        // Serial.println("OFF");
        hueLightsOff();
      }
    } else {
      Serial.println("OFF RESET");
      offTimer.reset();
    }
    
    loopTimer.reset();
  }
  
}
