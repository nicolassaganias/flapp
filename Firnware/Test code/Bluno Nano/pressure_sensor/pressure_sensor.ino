#define PRESSURE_SENSOR_PIN A1  // Pin defination
#define CODE "pressure"  // Code for detecting pressure

#include "pressure.h"  
#include "bleServer.h"



void setup() {
  Serial.begin(115200);  // Serial and BLE initialization
  delay(1000);
  configBLE(); // Confiure the BLE on Bluno
}

void loop() {
  String revData = getBleData(); // Get data from BLE
  if(revData.indexOf(CODE) >= 0){
    float pressure = getPressure();  // Get pressure data from sensor
    Serial.println(pressure);  // Send the pressure data to BLE
  }
  delay(500);
}
