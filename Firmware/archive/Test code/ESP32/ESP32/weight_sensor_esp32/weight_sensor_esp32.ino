#include "ble_server.h"

// #include <SoftwareSerial.h>

// #define txPin 3 // TX pin of HC-06
// #define rxPin 4 // RX pin of HC-06

String weight, revData;

// SoftwareSerial Serial1(txPin, rxPin); //Rx,Tx

void setup() {
  Serial.begin(9600);   // Initialize the Bluno BLE Serial
  Serial1.begin(9600);  // Initialize the HC-06 BT Serial
}


void loop() {
  // Capture the HC-06 BT Serial data
  if (Serial1.available()) {
    weight = Serial1.readStringUntil('\n');
    int colonPos = weight.indexOf(":");
    weight = weight.substring(colonPos + 1);
    weight.trim();
    colonPos = weight.indexOf(" ");
    weight = weight.substring(0, colonPos);
  }

  if (receivedData == "od") {
    send_data((String)weight);
  }
}