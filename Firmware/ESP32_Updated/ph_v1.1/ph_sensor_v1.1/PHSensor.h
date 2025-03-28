#define SensorPin 13              //  pH meter Analog output to Arduino Analog Input 0
float Offset  = 2.0;              //  deviation compensate, default 2.0

#define calibrationFactor 1
#define samplingInterval 20
#define ArrayLenth  40           //  times of collection
#define standard_solution 7.0

int pHArray[ArrayLenth];         // Store the average value of the sensor feedback
int pHArrayIndex = 0;

double avergearray(int* arr, int number) {
  int i;
  int max, min;
  double avg;
  long amount = 0;
  if (number <= 0) {
    Serial.println("Error number for the array to avraging!/n");
    return 0;
  }
  if (number < 5) { //less than 5, calculated directly statistics
    for (i = 0; i < number; i++) {
      amount += arr[i];
    }
    avg = amount / number;
    return avg;
  } else {
    if (arr[0] < arr[1]) {
      min = arr[0]; max = arr[1];
    }
    else {
      min = arr[1]; max = arr[0];
    }
    for (i = 2; i < number; i++) {
      if (arr[i] < min) {
        amount += min;      //arr<min
        min = arr[i];
      } else {
        if (arr[i] > max) {
          amount += max;  //arr>max
          max = arr[i];
        } else {
          amount += arr[i]; //min<=arr<=max
        }
      }//if
    }//for
    avg = (double)amount / (number - 2);
  }//if
  return avg;
}

float readpHSensor(){
  static unsigned long samplingTime = millis();
  static float pHValue, voltage;

  if (millis() - samplingTime > samplingInterval){
    pHArray[pHArrayIndex++] = analogRead(SensorPin);
    if (pHArrayIndex == ArrayLenth)pHArrayIndex = 0;
    voltage = avergearray(pHArray, ArrayLenth) * 3.3 / 4095;
    pHValue = calibrationFactor * voltage + Offset;
    samplingTime = millis();
  }
    // Serial.print("Voltage:");
    // Serial.print(voltage, 2);
    // Serial.print("    pH value: ");
    // Serial.println(pHValue, 2);
    return pHValue;
}
