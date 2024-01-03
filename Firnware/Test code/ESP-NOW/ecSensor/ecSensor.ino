// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
#define EC_SENSOR_PIN 12          // Output pin of EC Sensor

#define ESPADC 4096.0    // the esp Analog Digital Convertion value
#define ESPVOLTAGE 3300  // the esp voltage supply value

#include "espNow.h"
#include "ec.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();
  configEC();

  myData.id = 1; // For ec value

  
}

void loop() {
  
  sendEC();
  delay(1000);
}
