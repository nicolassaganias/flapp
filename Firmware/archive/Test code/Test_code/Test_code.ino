#include "ble_server.h"

unsigned long generateRealRandom(int min, int max) {
  randomSeed(analogRead(A5));
  uint64_t realRandom = random(1, 10) + random(1, 100) + random(1, 1000) + random(1, 10000);
  realRandom %= (max - min);
  realRandom += min;
  return realRandom;
}

float generateFloatRandom(int min, int max) {
  return (generateRealRandom(min, max) + (generateRealRandom(0, 100)/100.00));
}

void setup() {
  Serial.begin(115200);
  configBLE();  // Configure the esp32 BLE
}

void loop() {
  send_data(ecCharacteristic, String(generateFloatRandom(0,100)));
  send_data(phCharacteristic, String(generateFloatRandom(3,10)));
  send_data(pressureCharacteristic, String(generateFloatRandom(10,25)));
  send_data(temperatureCharacteristic, String(generateFloatRandom(20,40)));
  send_data(weightCharacteristic, String(generateFloatRandom(30,50)));
  delay(2000);
}
