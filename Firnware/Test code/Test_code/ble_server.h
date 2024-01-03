#include <BLEDevice.h>  // Required Library
#include <BLEServer.h>  // Required Library

// Define service and all characteristic uuid
#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define EC_CHAR_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define PH_CHAR_UUID "4a37b01d-364e-44d9-9335-770e2025b29f"
#define PRESSURE_CHAR_UUID "5c91853c-e8a9-4f44-b425-7a81c42ff3a1"
#define TEMPERATURE_CHAR_UUID "72c0a892-5a94-4d59-8951-dc80bc640c96"
#define WEIGHT_CHAR_UUID "5ad0b248-3ed1-470b-a79a-b46e4e8de64e"


BLEServer* pServer = NULL; // BLEServer object creation

// All charateristic object creation
BLECharacteristic* ecCharacteristic = NULL;
BLECharacteristic* phCharacteristic = NULL;
BLECharacteristic* pressureCharacteristic = NULL;
BLECharacteristic* temperatureCharacteristic = NULL;
BLECharacteristic* weightCharacteristic = NULL;

bool deviceConnected = false;

String receivedData;
String sendData;

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
    }
  }
};



// Function for creating a service and multiple characteristics and configure BLE in esp32
void configBLE() {
  BLEDevice::init("ESP-32 BLE");  // BLE Initialization
  pServer = BLEDevice::createServer(); // Create a BLE Server
  pServer->setCallbacks(new MyServerCallbacks());  // Set the callback function for checking the device is connected or not

  BLEService* pService = pServer->createService(SERVICE_UUID);  // Create a service on the server

  // Create characteristic for EC value
  ecCharacteristic = pService->createCharacteristic(
    EC_CHAR_UUID, BLECharacteristic::PROPERTY_READ
                           | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  ecCharacteristic->setCallbacks(new MyCallbacks());

  // Create characteristic for pH value
  phCharacteristic = pService->createCharacteristic(
    PH_CHAR_UUID, BLECharacteristic::PROPERTY_READ
                           | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  phCharacteristic->setCallbacks(new MyCallbacks());

  // Create characteristic for pressure value
  pressureCharacteristic = pService->createCharacteristic(
    PRESSURE_CHAR_UUID, BLECharacteristic::PROPERTY_READ
                           | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pressureCharacteristic->setCallbacks(new MyCallbacks());

  // Create characteristic for temperature value
  temperatureCharacteristic = pService->createCharacteristic(
    TEMPERATURE_CHAR_UUID, BLECharacteristic::PROPERTY_READ
                           | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  temperatureCharacteristic->setCallbacks(new MyCallbacks());

  // Create characteristic for weight value
  weightCharacteristic = pService->createCharacteristic(
    WEIGHT_CHAR_UUID, BLECharacteristic::PROPERTY_READ
                           | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  weightCharacteristic->setCallbacks(new MyCallbacks());

  pService->start(); // Start the server

  // Start advertisment
  pServer->getAdvertising()->addServiceUUID(pService->getUUID());
  pServer->getAdvertising()->start();

  delay(1000);
}

// Function for sending data on desired characteristic
void send_data(BLECharacteristic* pCharacteristic, String data){
  pCharacteristic->setValue(data.c_str());  // sending from esp32
  pCharacteristic->notify();  // Notify the client for receiving data
}
