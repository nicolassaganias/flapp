// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };
#define pH_SENSOR_PIN 13          // Output pin of pH Sensor

#define ESPADC 4096.0    // the esp Analog Digital Convertion value
#define ESPVOLTAGE 3300  // the esp voltage supply value

#include "espNow.h"
#include "ph.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();
  configPH();

  myData.id = 2; // For pH Value

  
}

void loop() {
  
  sendPH();
  delay(1000);
}
