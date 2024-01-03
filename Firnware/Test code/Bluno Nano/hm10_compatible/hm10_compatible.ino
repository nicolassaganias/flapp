#include "bleATCommand.h"


void setup() {
  Serial.begin(115200);
  
  delay(1000);
  
  configBLE("Bluno Nano");
  


}


void loop() {
  String data = getData();

  if(data != ""){
    Serial.print("Received data: ");
    Serial.println(data);
  }
  else {
    Serial.println("No data received");
    sendData("Send Data");
  }

  delay(1000);

}
