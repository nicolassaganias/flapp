#include "weight.h"
#include "ble_server.h"

// #include <SoftwareSerial.h>

// #define txPin 3 // TX pin of HC-10
// #define rxPin 4 // RX pin of HC-10



// SoftwareSerial Serial2(txPin, rxPin); //Rx,Tx

void setup() {
  Serial.begin(9600);   // Initialize the Bluno BLE Serial
  Serial2.begin(9600);  // Initialize the HC-10 BT Serial
  configBLE();
}


void loop() {
  // Capture the HC-10 BT Serial data
  delay(100);
}
