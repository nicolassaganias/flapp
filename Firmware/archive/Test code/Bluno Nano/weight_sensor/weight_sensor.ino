#define txPinRS232 7  // Pin defination
#define rxPinRS232 8  // Pin defination
#define CODE "weight"  // Code for detecting pressure

#include "weight.h"  
#include "bleServer.h"



void setup() {
  Serial.begin(115200);  // Serial and BLE initialization
  delay(1000);
  configBLE(); // Confiure the BLE on Bluno
  configRS232(); // Configure the RS232
}

void loop() {
  String revData = getBleData(); // Get data from BLE
  if(revData.indexOf(CODE) >= 0){
    String weight = getWeight();  // Get pressure data from sensor
    Serial.println(weight);  // Send the pressure data to BLE
  }
  delay(500);
}
