#include "ble_server.h"
#include "espNow.h"
 
void setup() {
  //Initialize Serial Monitor
  Serial.begin(115200);
  configBLE();
  configESPNOW();
}
 
void loop() {

  delay(1000);  
}