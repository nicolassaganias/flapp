#include "temperature.h"
#include "bleServer.h"

#define CODE "temperature"

void setup() {
  Serial.begin(115200);
  delay(1000);
  configBLE();
}

void loop() {
  String revData = getBleData();
  if(revData.indexOf(CODE) >= 0){
    float temparature = readTemperature();
    Serial.println(temparature);
  }
  delay(500);
}
