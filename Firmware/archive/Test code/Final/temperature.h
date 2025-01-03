#include <OneWire.h>  // Required Library

//Temperature chip i/o
OneWire ds(TEMPERATURE_SENSOR_PIN);  // Object creation

// Function for reading temperature
float readTemperature() {
  //returns the temperature from one DS18S20 in DEG Celsius

  byte data[12];
  byte addr[8];

  if (!ds.search(addr)) {
    //no more sensors on chain, reset search
    ds.reset_search();
    return -1000;
  }

  if (OneWire::crc8(addr, 7) != addr[7]) {
    Serial.println("CRC is not valid!");
    return -1000;
  }

  if (addr[0] != 0x10 && addr[0] != 0x28) {
    Serial.print("Device is not recognized");
    return -1000;
  }

  ds.reset();
  ds.select(addr);
  ds.write(0x44, 1);  // start conversion, with parasite power on at the end

  ds.reset();
  ds.select(addr);
  ds.write(0xBE);  // Read Scratchpad


  for (int i = 0; i < 9; i++) {  // we need 9 bytes
    data[i] = ds.read();
  }

  ds.reset_search();

  byte MSB = data[1];
  byte LSB = data[0];

  float tempRead = ((MSB << 8) | LSB);  //using two's compliment
  float TemperatureSum = tempRead / 16;

  return TemperatureSum;
}

// Function for sending temperature
void sendTemperature() {
  // float tempe = readTemperature(); // Getting temperature from sensor
  float tempe = (float) generateRealRandom(0,100);
  String data = (String)tempe;  // Convert it into String
  send_data(temperatureCharacteristic, data); // Send data on it's characteristic
}