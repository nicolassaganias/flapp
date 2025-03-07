#define WATER_LEVEL_SENSOR_PIN 32  // Pin connected to the water level sensor
#define RELAY_PIN 13               // Pin connected to the relay module
#define YELLOW_PIN 16
#define GREEN_PIN 17
#define BLUE_PIN 18
void setup() {
  pinMode(YELLOW_PIN, OUTPUT);
  digitalWrite(YELLOW_PIN, HIGH);
  delay(2000);
  pinMode(WATER_LEVEL_SENSOR_PIN, INPUT_PULLUP);  // The sensor normally stays HIGH
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);  // Ensure relay is off initially

  Serial.begin(115200);
  Serial.println("Water level monitoring started...");
  delay(1000);
}

void loop() {
  int waterLevel = digitalRead(WATER_LEVEL_SENSOR_PIN);

  Serial.print("Water Level Sensor: ");
  Serial.print(waterLevel);
  Serial.println(waterLevel == LOW ? " // Normal" : " // Overflow Detected");

  if (waterLevel == HIGH) {
    Serial.println("Water level exceeded! Turning on the pump...");
    digitalWrite(RELAY_PIN, LOW);  // Turn on relay (activating the pump)
    digitalWrite(GREEN_PIN, LOW);
    digitalWrite(BLUE_PIN, HIGH);
    delay(30000);  // Keep the pump running for 30 seconds

    Serial.println("Stopping the pump...");
    digitalWrite(RELAY_PIN, HIGH);  // Turn off relay
    digitalWrite(BLUE_PIN, LOW);
  } else {
    digitalWrite(GREEN_PIN, HIGH);
    digitalWrite(YELLOW_PIN, LOW);
    digitalWrite(BLUE_PIN, LOW);
  }
  delay(1000);  // Small delay before next reading
}
