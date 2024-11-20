
// Function for configure RS232
void configRS232() {
  Serial2.begin(9600); // Initialize the software serial
}

// Function for getting weight from Serial 
String getWeight() {
  if (Serial2.available()) {
    String data = Serial2.readString(); // Read the incoming string from the software serial
    Serial.println(data); // Print the received string to the hardware serial
    return data;
  }
  return "";
}

// Function for sending weight value
void sendWeight(){
  String data = getWeight(); // Getting weight from RS232
  //String data = (String) generateRealRandom(5,50);
  send_data(weightCharacteristic, data); // Send data on it's characteristic
}
