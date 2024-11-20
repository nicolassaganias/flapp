// Function for configuare ble on Bluno
void configBLE(){
  // Config BLE on Bluno
  Serial.print("+++"); // Entering AT mode
  Serial.print("AT+SETTING=DEFAULT\r\n"); // Set the BLE on peripheral mode
  Serial.print("AT+MIN_INTERVAL=20\r\n"); // Set the minimum interval for connecting client
  Serial.print("AT+MAX_INTERVAL=40\r\n"); // Set the maximum interval for connecting client
  Serial.print("AT+BLUNODEBUG=ON\r\n");   // Send data on both BLE and USB which is get from UART
  Serial.print("AT+USBDEBUG=ON\r\n");     // Send data on both UART and USB which is get from BLE
  Serial.print("AT+EXIT\r\n");  // Exit from AT mode
}


// Function for get data from BLE
String getBleData() {
  String msg = "";
  unsigned long time = millis() + 500;  // maximum wait for 500 ms
  while (time > millis()) {
    if (Serial.available() > 0) {
      msg = Serial.readStringUntil('\n');  // Receive response from Bluno
    }
  }
  msg.trim();
  return msg;
}