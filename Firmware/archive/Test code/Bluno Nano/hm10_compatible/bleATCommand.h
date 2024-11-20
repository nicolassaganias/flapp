#include "HardwareSerial.h"
#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);  // RX, TX

String getBleAtData() {
  String msg = "";
  unsigned long time = millis() + 500;  // maximum wait for 500 ms
  while (time > millis()) {
    if (mySerial.available() > 0) {
      msg = mySerial.readStringUntil('\n');  // Receive response from HM-10
      // Check the command is successfully worked or not
      if (msg.indexOf("OK") >= 0) {
        //Serial.println("Ok Found");
        break;
      }
      else{
        Serial.println("Configuration Error");
      }
    }
  }
  msg.trim();
  // Serial.print("Received data: ");
  // Serial.println(msg);
  return msg;
}


void atCommand(String cmd){
  Serial.print("Send Command: ");
  Serial.println(cmd);
  mySerial.print(cmd.c_str());
  String rspn = getBleAtData();
  Serial.print("Received Response: ");
  Serial.println(rspn);
}

void configBLE(String deviceName) {
  mySerial.begin(9600); // Initialized the serial communication

  Serial.println("Wait for configuration");
  atCommand("AT");
  atCommand("AT+RESET");
  atCommand("AT+IMME1");
  atCommand("AT+NOTI1");
  atCommand("AT+NOTP1");
  atCommand("AT+NAME" + deviceName);
  atCommand("AT+UUID0x3935");
  atCommand("AT+CHAR0xC29C");
  atCommand("AT+ROLE0");
  atCommand("AT+ADVI0");
  atCommand("AT+ADTY0");
  atCommand("AT+FLAG0");
  atCommand("AT+IMME0");
  atCommand("AT+MODE2");
  Serial.println("Configuration Process End");
}


void sendData(String data){
  mySerial.print(data);
}

String getData(){
  String msg = "";
  unsigned long time = millis() + 500;  // maximum wait for 500 ms
  while (time > millis()) {
    if (mySerial.available() > 0) {
      msg = mySerial.readStringUntil('\n');  // Receive response from HM-10
    }
  }
  return msg;
}