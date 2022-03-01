#include "arduino_secrets.h"
#include <SoftTimers.h>

#define LOOP_TIME 200
#define ON_CHECK_TIME 1000 // The amount of time above the on threshold, before on is assumed true.
#define OFF_CHECK_TIME 3000 // The amount of time under the off threshold, before off is assumed true.

// Properties
const float ON_THRESHOLD  = AC_CURRENT_ON_THRESHOLD;
const float OFF_THRESHOLD = AC_CURRENT_OFF_THRESHOLD;

// Variables
SoftTimer loopTimer;
SoftTimer onCheckTimer;
SoftTimer offCheckTimer;

void setup() {
  // Serial for debugging
  Serial.begin(9600);

  // Wifi connection
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW); 
  WiFiConnect();

  // Soft timers
  loopTimer.setTimeOutTime(LOOP_TIME);
  loopTimer.reset();
  onCheckTimer.setTimeOutTime(ON_CHECK_TIME);
  onCheckTimer.reset();
  offCheckTimer.setTimeOutTime(OFF_CHECK_TIME);
  offCheckTimer.reset();
}

void loop() {

  WiFiKeepConnection();

  if(loopTimer.hasTimedOut()) {
    
    float ACCurrentValue = readACCurrentValue();

    Serial.print("Loop - ");
    Serial.print(ACCurrentValue);
    Serial.println(" A");

    if(ACCurrentValue  >= ON_THRESHOLD) {
      if(onCheckTimer.hasTimedOut()) {
        hueLightsOn(); 
      }
    } else {
      onCheckTimer.reset();
    }

    
   if(ACCurrentValue  <= OFF_THRESHOLD) {
      if(offCheckTimer.hasTimedOut()) {
        hueLightsOff();
      }
    } else {
      offCheckTimer.reset();
    }
    
    loopTimer.reset();
  }
  
}
