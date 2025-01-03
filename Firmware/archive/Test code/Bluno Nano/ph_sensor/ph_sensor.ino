#define pH_SENSOR_PIN A1  // Analog Pin defination
#define CODE "ph"  // Code for detecting pH

#include "ph.h"  
#include "bleServer.h"

void setup() {
  Serial.begin(115200);  // Serial and BLE initialization
  delay(1000);
  configBLE(); // Confiure the BLE on Bluno
  configPH();  // Configure the pH Sensor
}

void loop() {
  String revData = getBleData(); // Get data from BLE
  if(revData.indexOf(CODE) >= 0){
    float ph = getPH();  // Get pH data from sensor
    Serial.println(ph);  // Send the pH data to BLE
  }
  delay(500);
}
