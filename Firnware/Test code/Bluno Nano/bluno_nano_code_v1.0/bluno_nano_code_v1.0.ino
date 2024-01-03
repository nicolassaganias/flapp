#include <SoftwareSerial.h>
#include "temperature.h"

SoftwareSerial mySerial(10, 11); // RX, TX pins on Bluno Nano

const char* deviceName = "Bluno Nano Device";
const char* serviceUUID = "19B10010-E8F2-537E-4F6C-D104768A1214";
const char* characteristicUUID = "19B10012-E8F2-537E-4F6C-D104768A1214";

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600); // Set the baud rate according to your Bluno Nano's firmware

  delay(1000); // Wait for Bluno Nano to initialize

  // Configure Bluno Nano as a BLE peripheral
  sendCommand("AT+ROLE1"); // Set the Bluno Nano as a peripheral
  sendCommand("AT+IMME1"); // Enable immediate advertising
  sendCommand("AT+RESET"); // Reset the Bluno Nano

  // Set the device name
  sendCommand("AT+NAME" + String(deviceName));

  // Create the service and characteristic
  sendCommand("AT+UUID" + String(serviceUUID)); // Set the custom service UUID
  sendCommand("AT+CHAR" + String(characteristicUUID) + ",16,20,20"); // Set the custom characteristic UUID, properties, and value length

  // Start advertising the custom service
  sendCommand("AT+ADVDATA1,07,09,42,4C,55,4E,4F"); // Set the manufacturer data for the advertising packet
  sendCommand("AT+ADVEN1"); // Enable advertising
}

void loop() {
  // Main loop
  delay(1000);
  
  // Send data on the characteristic
  String data = "Hello, Bluno Nano!";
  sendCommand("AT+CHAR" + String(characteristicUUID) + ",3," + String(data.length()) + "," + data); // Write data to the characteristic
}

void sendCommand(String command) {
  mySerial.println(command);
  delay(500);

  while (mySerial.available()) {
    Serial.write(mySerial.read());
  }
}
