#include "ble_server.h"


#define RELAY_PIN 27

void controlRelay(bool status){
  digitalWrite(RELAY_PIN, !status);
}

void setup() {
  Serial.begin(115200);
  Serial.println("Start");

  pinMode(RELAY_PIN, OUTPUT);

  configBLE();

}

void loop() {

}
