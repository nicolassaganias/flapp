bool sending = false;

// Getting response from putting AT comand
String getBleAtData() {
  String msg = "";
  unsigned long time = millis() + 500;  // maximum wait for 500 ms
  while (time > millis()) {
    if (Serial.available() > 0) {
      msg = Serial.readStringUntil('\n');  // Receive response from HM-10
      // Check the command is successfully worked or not
      if (msg.indexOf("OK") >= 0) {
        break;
      }
    }
  }
  msg.trim();
  return msg;
}

// Function for giving AT command
bool atCommand(char _msg[]) {
  Serial.print(_msg);         // Send command to HM-10
  String msg = getBleAtData();  // Receive response from HM-10
  Serial.println(msg);
  if (msg.indexOf("stop") >= 0) {
    sending = false;
    Serial.println("Data sending stopped");
    return;
  }
  // Check the command is successfully worked or not
  if (msg.indexOf("OK") >= 0) {
    return true;
  }
  return false;
}


//AT command for configure BLE of Bluno Nano
bool configBLE() {
  atCommand("AT");
  atCommand("AT+RESET");
  atCommand("AT+ROLE0");
  atCommand("AT+IMME1");
  atCommand("AT+NOTI1");
  atCommand("AT+NOTP1");
  atCommand("AT+NAMEBluno Nano");
  atCommand("AT+UUID0x3935");
  atCommand("AT+CHAR0xC29C");
  atCommand("AT+ADVI0");
  atCommand("AT+ADTY0");
  atCommand("AT+FLAG0");
  atCommand("AT+IMME0");
  atCommand("AT+MODE2");
}

// Function for sending data
void dataSend(String sendData) {
  Serial.println(sendData);
  sending = true;
  //Sending the sensor data untill data is received by app
  while (sending) {
    atCommand(sendData.c_str());
  }
}