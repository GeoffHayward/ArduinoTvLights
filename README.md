# ArduinoTvLights
An Arduino project that uses a non invasive current sensor (on the TV's power cord) to switch 
the lights under my TV on/off respective to the TV state.

Requires:
- Arduino Uno WiFi Rev 2.
- Non Invasive Current Sensor. I am using https://www.dfrobot.com/product-1486.html
- Philips Hue v2 Bridge.
- Zigbee light(s) (i.e. Hue compatible). I am using the Ikea TRÅDFRI Zigbee Driver with Ikea OMLOPP LED spotlights.   

See https://developers.meethue.com/ for details on the Hue Bridge REST API.

## Set up
Add a file called arduino_secrets.h with the following.

```
// Wifi (ArduinoWifi)
#define SECRET_SSID "***********"
#define SECRET_PASS "***********"

// Philips Hue
#define HUE_BRIDGE "192.***.*.***" // Hue IP Address on the same network
#define HUE_USERNAME "********"
#define HUE_LIGHT 5 // Light id on Hue Bridge

// AC CurrentSensor
#define AC_CURRENT_ON_THRESHOLD 0.17 // My TV's above standby (on)
#define AC_CURRENT_OFF_THRESHOLD 0.14 // My TV's standby (probably off - watch out for apps loading)
#define ACTectionRange 20;    //set Non-invasive AC Current Sensor tection range (5A,10A,20A)

// Arduino
#define _VREF 4.96 // Multimeter reading
```
