/*
@pH Sensor V1.1
@Firmware Version: v1.0
@Modified Date: 22.04.2024
*/

#include <Preferences.h>
Preferences preferences;

#include "PHSensor.h"
#include "ESP32BLEServer.h"

void setup() {
  Serial.begin(115200);
  configBLE();
  // Serial.println("Starting");
  // Serial.println(Offset);
  preferences.begin("myApp", false);
  Offset = preferences.getFloat("Offset");
  preferences.end();
  if(Offset == 0.0){
    Offset = 2.0;     // set default offset value
  }
  Serial.println(Offset);
}

void loop() {
  float sensor_data = readpHSensor();
  send_data(String(sensor_data));
  delay(3000);
}