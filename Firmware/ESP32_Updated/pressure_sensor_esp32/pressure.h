/************************************************************
  Calibration: connect the 3 pin wire to the ESP-32 (VCC, GND and Signal)
  without connecting the sensor to the water pipe and run the program
  for once. Mark down the LOWEST voltage value through the serial
  monitor and revise the "OffSet" value to complete the calibration.

  After the calibration the sensor is ready for measuring!
**************************************************************/

float OffSet = 0.400;  // Offset voltage

float V, P;

// Function for getting pressure from sensor
float getPressure() {
  //Connect sensor to Analog 0
  V = analogRead(PRESSURE_SENSOR_PIN) * (3.3 / 4095.0);  //Sensor output voltage
  //V = analogRead(PRESSURE_SENSOR_PIN) * (5 / 1024);  //Sensor output voltage

  P = (V - OffSet) * 250;                                //Calculate water pressure
  P = ((P / 100) / 6) * 1000 ; // / 100 To turn Kpa to Bar // / 7 for calibratingfactor for Preassure03 // * 1000 for mbar

  Serial.print("Voltage:");
  Serial.print(V, 3);
  Serial.println("V");

  Serial.print(" Pressure:");
  Serial.print(P, 1);
  Serial.println(" Bar");
  Serial.println();

  return P;
}
