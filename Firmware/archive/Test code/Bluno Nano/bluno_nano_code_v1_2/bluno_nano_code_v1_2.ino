#include "temperature.h"
#include "bleServer.h"



void setup(){
  Serial.begin(115200);
  Serial.println("Start Execution");
  configBLE();

}

void loop(){
  delay(5000);
  float temp = readTemperature();
  dataSend((String) temp);

}