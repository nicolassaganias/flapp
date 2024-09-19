#include "weight.h"
#include "ble_server.h"
#include "arduino.h"

void setup() {
  Serial.begin(115200);   // Initialize the Bluno BLE Serial
  Serial2.begin(9600);    // Initialize the HC-06 BT Serial
  configBLE();
}

void loop() {
  // Capture the HC-06 BT Serial data
  getWeight();
  delay(100);
}
