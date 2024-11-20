#include <BLEDevice.h>
#include <BLEServer.h>


#define SERVICE_UUID "4fafc201-1fb5-459e-8fcc-c5c9c331914b"
#define CHARACTERISTIC_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a8"
#define CHARACTERISTIC2_UUID "beb5483e-36e1-4688-b7f5-ea07361b26a9"

BLEServer* pServer = NULL;
BLECharacteristic* pCharacteristic = NULL;
BLECharacteristic* pCharacteristic2 = NULL;
bool deviceConnected = false;
bool continious = false;

String receivedData, receivedData2;
String sendData;

unsigned long generateRealRandom(int min, int max) {
  randomSeed(analogRead(A5));
  uint64_t realRandom = random(1, 10) + random(1, 100) + random(1, 1000) + random(1, 10000);
  realRandom %= (max - min);
  realRandom += min;
  return realRandom;
}

float generateFloatRandom(int min, int max) {
  return (generateRealRandom(min, max) + (generateRealRandom(0, 100) / 100.00));
}


class MyServerCallbacks : public BLEServerCallbacks {
  void onConnect(BLEServer* pServer) {
    Serial.println("Client Connected");
    deviceConnected = true;
  };

  void onDisconnect(BLEServer* pServer) {
    Serial.println("Client disConnected");
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
      Serial.print("CHAR1 New value: ");
      Serial.println(receivedData);
      if (receivedData == "pair") {
        pCharacteristic->setValue("t:pair");  // sending from esp32
        pCharacteristic->notify();
      } else if (receivedData == "od") {
        float t = generateFloatRandom(25, 50);
        String d = "t:" + (String)t;
        pCharacteristic->setValue(d.c_str());  // sending from esp32
        pCharacteristic->notify();
      } else if (receivedData == "con") {
        continious = true;
      } else if (receivedData == "stop") {
        continious = false;
      }
    }
  }
};

class MyCallbacks2 : public BLECharacteristicCallbacks {
  void onWrite(BLECharacteristic* pCharacteristic) {
    std::string value = pCharacteristic->getValue();
    receivedData2 = "";
    if (value.length() > 0) {
      for (int i = 0; i < value.length(); i++) {
        receivedData2 += value[i];
      }
      Serial.print("CHAR2 New value: ");
      Serial.println(receivedData2);
    }
  }
};


void setup() {
  Serial.begin(115200);
  Serial.println("Connect to T-QT Pro");

  BLEDevice::init("Bluno");
  pServer = BLEDevice::createServer();
  pServer->setCallbacks(new MyServerCallbacks());

  BLEService* pService = pServer->createService(SERVICE_UUID);

  pCharacteristic = pService->createCharacteristic(
    CHARACTERISTIC_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic->setCallbacks(new MyCallbacks());

  pCharacteristic2 = pService->createCharacteristic(
    CHARACTERISTIC2_UUID,
    BLECharacteristic::PROPERTY_READ | BLECharacteristic::PROPERTY_WRITE | BLECharacteristic::PROPERTY_NOTIFY);

  pCharacteristic2->setCallbacks(new MyCallbacks2());

  pService->start();

  pServer->getAdvertising()->addServiceUUID(pService->getUUID());
  pServer->getAdvertising()->start();

  delay(1000);
}

void loop() {
  while (continious) {
    float t = generateFloatRandom(25, 50);
    String d = "t:" + (String)t;
    Serial.println(d);
    pCharacteristic->setValue(d.c_str());  // sending from esp32
    pCharacteristic->notify();
    delay(1000);
  }
  delay(1000);
}
