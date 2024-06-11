//HC-06 TXD (Transmit) to ESP32 RX2 (Receive, usually GPIO 16)
//HC-06 RXD (Receive) to ESP32 TX2 (Transmit, usually GPIO 17)

#include "weight.h"
#include "ble_server.h"

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
