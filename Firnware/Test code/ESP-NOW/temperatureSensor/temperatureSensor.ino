// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
#define TEMPERATURE_SENSOR_PIN 5  // Temperature sensor data pin
#include "espNow.h"
#include "temperature.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();

  myData.id = 4; // For temperature

  
}

void loop() {
  
  sendTemperature();
  delay(1000);
}
