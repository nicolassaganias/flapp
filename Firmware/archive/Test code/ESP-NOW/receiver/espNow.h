#include <esp_now.h>
#include <WiFi.h>
#include <stdlib.h>

// Structure example to receive data
// Must match the sender structure
typedef struct struct_message {
  int id;
  float value;
};

// Create a struct_message called myData
struct_message myData;

void sendSendorData(int id, String value){
  if(id == 1){
    send_data(ecCharacteristic,value);
  }
  else if (id == 2){
    send_data(phCharacteristic,value);
  }
  else if (id == 3){
    send_data(pressureCharacteristic,value);
  }
  else if (id == 4){
    send_data(temperatureCharacteristic,value);
  }
  else if (id == 5){
    send_data(weightCharacteristic,value);
  }

}


// callback function that will be executed when data is received
void OnDataRecv(const uint8_t *mac_addr, const uint8_t *incomingData, int len) {
  char macStr[18];
  Serial.print("Packet received from: ");
  snprintf(macStr, sizeof(macStr), "%02x:%02x:%02x:%02x:%02x:%02x",
           mac_addr[0], mac_addr[1], mac_addr[2], mac_addr[3], mac_addr[4], mac_addr[5]);
  Serial.println(macStr);
  memcpy(&myData, incomingData, sizeof(myData));
  Serial.printf("Board ID %u: %u bytes\n", myData.id, len);

  // Perform Action

  Serial.println(myData.value);

  sendSendorData(myData.id, (String) myData.value);

  
}
void configESPNOW() {
  //Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  //Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for recv CB to
  // get recv packer info
  esp_now_register_recv_cb(OnDataRecv);
}