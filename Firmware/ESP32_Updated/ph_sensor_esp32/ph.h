/*
 * You can send commands in the serial monitor to execute the calibration.
 * Serial Commands:
 *   enterph -> enter the calibration mode
 *   calph   -> calibrate with the standard buffer solution, two buffer solutions(4.0 and 7.0) will be automaticlly recognized
 *   exitph  -> save the calibrated parameters and exit from calibration mode
 */

#include "DFRobot_ESP_PH.h"  // Required Library
#include "EEPROM.h"          // Required Library

#define ENTERPH "enterph"

DFRobot_ESP_PH ph;  // pH Object creation

#define PH_PIN pH_SENSOR_PIN

float phvoltage, phValue, phtemperature = 21;

// Function for configure pH Sensor
void configPH() {
  EEPROM.begin(32);  //needed to permit storage of calibration value in eeprom
  ph.begin();
}


// Function for get pH value from sensor
float getPH() {
  static unsigned long timepoint1 = millis();
  static float voltageReadings[20] = {0};  // Array to store the last 20 readings
  static int currentIndex = 0;
  static bool arrayFilled = false;

  if (millis() - timepoint1 > 1000U)  // Time interval: 1s
  {
    timepoint1 = millis();

    // Read the analog value with 12-bit resolution
    analogReadResolution(12);  // Set the ADC resolution to 12 bits (0-4095)
    float currentVoltage = analogRead(PH_PIN) / ESPADC * ESPVOLTAGE;

    // Store the reading in the array
    voltageReadings[currentIndex] = currentVoltage;
    currentIndex = (currentIndex + 1) % 20;

    // Check if the array has been filled at least once
    if (currentIndex == 0) {
      arrayFilled = true;
    }

    // Calculate the average voltage
    float voltageSum = 0;
    int readingsCount = arrayFilled ? 20 : currentIndex;  // Determine how many readings to average
    for (int i = 0; i < readingsCount; i++) {
      voltageSum += voltageReadings[i];
    }
    phvoltage = voltageSum / readingsCount;

    Serial.print("voltage:");
    Serial.println(phvoltage, 4);

    // Uncomment and modify if you have a temperature sensor
    // phtemperature = readTemperature(); 
    Serial.print("temperature:");
    Serial.print(phtemperature, 1);
    Serial.println("^C");

    phValue = ph.readPH(phvoltage, phtemperature);  // Convert voltage to pH with temperature compensation
    Serial.print("pH:");
    Serial.println(phValue, 4);
  }
  ph.calibration(phvoltage, phtemperature);  // Calibration process by Serial CMD
  return phValue;
}
