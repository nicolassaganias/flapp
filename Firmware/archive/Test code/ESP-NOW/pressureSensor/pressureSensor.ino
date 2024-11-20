// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
#define PRESSURE_SENSOR_PIN 14    // Output pin of pressure sensor
#include "espNow.h"
#include "pressure.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();

  myData.id = 3; // For pressure value

  
}

void loop() {
  
  sendPressure();
  delay(1000);
}
