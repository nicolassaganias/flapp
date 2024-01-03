#define EC_SENSOR_PIN 12          // Output pin of EC Sensor
#define pH_SENSOR_PIN 13          // Output pin of pH Sensor
#define PRESSURE_SENSOR_PIN 14    // Output pin of pressure sensor
#define TEMPERATURE_SENSOR_PIN 5  // Temperature sensor data pin
#define rxPinRS232  10                // RX pin of software serial
#define txPinRS232  11                // TX pin of software serial


#define ESPADC 4096.0    // the esp Analog Digital Convertion value
#define ESPVOLTAGE 3300  // the esp voltage supply value

// Include this header with maintains this order
#include "ble_server.h"
#include "temperature.h"
#include "ec.h"
#include "ph.h"
#include "pressure.h"
#include "weight.h"


void setup() {
  Serial.begin(115200);

  // Initialize ADC
  analogReadResolution(12);        // Set ADC resolution to 12 bits (0-4095)
  analogSetAttenuation(ADC_11db);  // Set input voltage range to 0-3.3V

  configBLE();  // Configure the esp32 BLE
  configEC();   // Configure the EC Sensor
  configPH();   // Configure the pH Sensor
  configRS232();// Configure RS232 module
}

void loop() {
  if (deviceConnected) {
    sendEC();
    delay(2000);
    sendPressure();
    delay(2000);
    sendPH();
    delay(2000);
    sendTemperature();
    delay(2000);
    sendWeight();
  }

  delay(2000);
}
