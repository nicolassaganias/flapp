#include <BLEDevice.h>  // Required Library
#include <BLEServer.h>  // Required Library

// Define service and all characteristic uuid
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHAR_UUID "4a37b01d-364e-44d9-9335-770e2025b29f"

#define ENTER "ENTEREC"
#define CAL "CALEC"
#define EXIT "EXITEC"
#define TAG "ec:"

#define UNIT "unit:ms/cm"
#define INFO "info:k=10"

BLEServer* pServer = NULL;  // BLEServer object creation

// All charateristic object creation
BLECharacteristic* characteristic = NULL;

bool deviceConnected = false;

String receivedData;

// Callback function for checking the BLE is connected to anything or not
class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
    Serial.println("Connected");
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    pServer->startAdvertising();
  }
};

// Function for sending data on desired characteristic
void send_data(String data2) {
  String data = TAG + data2;
  characteristic->setValue(data.c_str());  // sending from esp32
  characteristic->notify();                // Notify the client for receiving data
}

// Callback function for receiving data from client and process it
class MyCallbacks : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    receivedData = "";
    if (value.length() > 0) {
      for (int i = 0; i < value.length(); i++) {
        receivedData += value[i];
      }
      Serial.print("New value: ");
      Serial.println(receivedData);
      if (receivedData == "od") {
        float pHValue = getEC();
        send_data((String) pHValue);

      } 
      else if (receivedData == "pair") {
        send_data("pair");
      }
      else if (receivedData == "enterec") {
        int status = ec.calibration(3.2, 25.0, ENTER);
        send_data((String)status);
      }
      else if (receivedData.indexOf("calec") >= 0) {
        int colonPos = receivedData.indexOf(":");
        String temparatureString = receivedData.substring(colonPos+1);
        
        temperature = temparatureString.toFloat();
        Serial.print("Received Temperature: ");
        Serial.println(temperature);

        voltage = analogRead(EC_PIN) / ESPADC * ESPVOLTAGE;  // read the voltage
        Serial.print("Get volatge for calibration: ");
        Serial.println(voltage);

        int status = ec.calibration(voltage, temperature, CAL);
        send_data((String)status);
      }
      else if (receivedData == "exitec") {
        int status = ec.calibration(voltage, temperature, EXIT);
        send_data((String)status);
      }
      else if (receivedData == "unit") {
        send_data((String)UNIT);
      }
      else if (receivedData == "info") {
        send_data((String)INFO);
      }
    }
  }
};

// Function for creating a service and multiple characteristics and configure BLE in esp32
void configBLE() {
  BLEDevice::init("EC K=10");                   // BLE Initialization
  pServer = BLEDevice::createServer();             // Create a BLE Server
  pServer->setCallbacks(new MyServerCallbacks());  // Set the callback function for checking the device is connected or not

  BLEService* pService = pServer->createService(SERVICE_UUID);  // Create a service on the server

  // Create characteristic for EC value
  characteristic = pService->createCharacteristic(
    CHAR_UUID, BLECharacteristic::PROPERTY_READ
                 | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  characteristic->setCallbacks(new MyCallbacks());

  pService->start();  // Start the server

  // Start advertisment
  pServer->getAdvertising()->addServiceUUID(pService->getUUID());
  pServer->getAdvertising()->start();

  delay(1000);
}
