#include <EEPROM.h>
#define PRESSURE_SENSOR_PIN A5 // Connect the pressure sensor with Bluno A5 pin

// Choose an EEPROM address to store the data
const int dataAddress = 1;

float OffSet = 0.483;  // Change this Offset voltage from calibration result

float V, P;

void configPressure(){
  EEPROM.get(dataAddress, OffSet);
}

void calibrate(){
  V = analogRead(PRESSURE_SENSOR_PIN) * (3.3 / 4095.0);  //Sensor output voltage
  Serial.print("Offset value: ");
  Serial.println(V);
  EEPROM.put(dataAddress, V);
  configPressure();
}

// Function for getting pressure from sensor
float getPressure() {
  V = analogRead(PRESSURE_SENSOR_PIN) * (3.3 / 4095.0);  //Sensor output voltage
  P = (V - OffSet) * 250;                                //Calculate water pressure
  Serial.println(OffSet);
  return P;
}
