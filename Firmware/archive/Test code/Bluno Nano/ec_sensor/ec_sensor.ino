#define EC_SENSOR_PIN A1  // Pin defination
#define CODE "ec"  // Code for detecting ec

#include "ec.h"  
#include "bleServer.h"

void setup() {
  Serial.begin(115200);  // Serial and BLE initialization
  delay(1000);
  configBLE(); // Confiure the BLE on Bluno
  configEC();  // Configure the EC
}

void loop() {
  String revData = getBleData(); // Get data from BLE
  if(revData.indexOf(CODE) >= 0){
    float ec = getEC();  // Get pressure data from sensor
    Serial.println(ec);  // Send the pressure data to BLE
  }
  delay(500);
}
