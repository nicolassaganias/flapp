// Define the MAC address of the receiver ESP32 
//uint8_t mainBoardMacAddress[] = { 0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF };


#define rxPinRS232 10             // RX pin of software serial
#define txPinRS232 11             // TX pin of software serial
#include "espNow.h"
#include "weight.h"



void setup() {
  Serial.begin(115200);

  configESPNOW();
  configRS232();

  myData.id = 5; // this id for weight sensor value sending

}

void loop() {
  sendWeight();
  delay(1000);
}
