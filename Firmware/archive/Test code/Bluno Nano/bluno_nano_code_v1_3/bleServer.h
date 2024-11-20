// Function for configuare ble on Bluno
void configBLE(){
  // Config BLE on Bluno
  Serial.print("+++");
  Serial.print("AT+SETTING=DEFAULT\r\n");
  Serial.print("AT+MIN_INTERVAL=20\r\n");
  Serial.print("AT+MAX_INTERVAL=40\r\n");
  Serial.print("AT+BLUNODEBUG=ON\r\n");
  Serial.print("AT+USBDEBUG=ON\r\n");
  Serial.print("AT+EXIT\r\n");
}

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