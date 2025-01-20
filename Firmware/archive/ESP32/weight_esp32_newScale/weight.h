String weight, revData;

void getWeight(){
  if (Serial2.available() > 0) {
    // Read the incoming bytes
    String inputString = Serial2.readStringUntil('\n');

    // Find the position of the first numeric character
    int startPos = 0;
    String numericString = "";
    bool isDot = true;
    bool isChar = false;
    for (int i = 0; i < inputString.length(); i++) {
      if (isDigit(inputString[i])) {
        numericString += inputString[i];
        isChar = true;
      } else if (isDot) {
        if (inputString[i] == '.') {
          if (isChar) {
            isDot = false;
            numericString += inputString[i];
          }else{
            numericString += '0';
            numericString += inputString[i];
            isDot = false;
          }
        }
      }
    }
    weight = numericString;
    // Print the extracted numeric string
    //Serial.println(numericString);
  }
}