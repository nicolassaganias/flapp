// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };

#include "espNow.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();

  myData.id = 2;
  myData.value = 1.99;
  sendData();

  
}

void loop() {
  

  delay(2000);
}
