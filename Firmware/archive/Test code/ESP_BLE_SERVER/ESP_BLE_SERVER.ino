#include <BLEDevice.h>
#include <BLEServer.h>


#define SERVICE_UUID        "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
bool deviceConnected = false;

String receivedData;
String sendData;

unsigned long generateRealRandom(int min, int max) {
  randomSeed(analogRead(A5));
  uint64_t realRandom = random(1, 10) + random(1, 100) + random(1, 1000) + random(1, 10000);
  realRandom %= (max - min);
  realRandom += min;
  return realRandom;
}


void randomSendData() {
  sendData = "";
  for (int i = 0; i < 3; i++) {
    unsigned long d = generateRealRandom(0, 20);
    sendData += (String)d;
    sendData += " ";
  }
}

class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    deviceConnected = false;
    pServer->startAdvertising();
  }
};

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


void setup() {
  Serial.begin(115200);
  Serial.println("Connect to T-QT Pro");

  BLEDevice::init("ESP-32 BLE");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE |
                      BLECharacteristic::PROPERTY_NOTIFY );

  pCharacteristic->setCallbacks(new MyCallbacks());
  randomSendData();
  Serial.println(sendData);
  pCharacteristic->setValue(sendData.c_str());  // sending from esp32

  pService->start();

  pServer->getAdvertising()->addServiceUUID(pService->getUUID());
  pServer->getAdvertising()->start();

  delay(1000);
}

void loop() {
  delay(10000);
  randomSendData();
  Serial.println(sendData);
  pCharacteristic->setValue(sendData.c_str());  // sending from esp32
  pCharacteristic->notify();
}
