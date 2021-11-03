#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLE2902.h>

#include <string>
#include <iostream>

// See the following for generating UUIDs:
// https://www.uuidgenerator.net/  

#define SERVICE_UUID        "29943f82-85c2-4fd4-ab41-0c2a6f7af32a"

#define CHARACTERISTIC_UUID_ROOM1 "5322ceb0-a48f-42bc-ad8b-28670fefee5a"
#define CHARACTERISTIC_UUID_ROOM2 "5d6ed9ec-4db5-4c75-8dca-4567ab5af830"
#define CHARACTERISTIC_UUID_ROOM3 "addbf900-ac76-4b38-afff-ba06f6c7b18d"
#define CHARACTERISTIC_UUID_ROOM4 "35e706b4-031b-4c52-a25f-f7ca96045313"

#define CUTOFF -55
#define PIN 2

BLECharacteristic *pCharacteristic_room1;
BLECharacteristic *pCharacteristic_room2;
BLECharacteristic *pCharacteristic_room3;
BLECharacteristic *pCharacteristic_room4;

String mac_ancre_1 = "00:14:03:05:ED:C5";
String mac_ancre_2 = "00:14:03:05:ED:7E";
String mac_ancre_3 = "00:14:03:05:ED:49";
String mac_test =    "f8:0a:c2:86:4a:4d";


class MyCallbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
      std::string value = pCharacteristic->getValue();

      if (value.length() > 0) {
        Serial.println("*********");
        Serial.print("New value: ");
        for (int i = 0; i < value.length(); i++)
          Serial.print(value[i]);

        Serial.println();
        Serial.println("*********");
      }
    }
};

void setup() {

  pinMode(PIN, OUTPUT);
  Serial.begin(115200);

  BLEDevice::init("MyESP32");
  BLEServer *pServer = BLEDevice::createServer();

  BLEService *pService = pServer->createService(SERVICE_UUID);

  pCharacteristic_room1 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_ROOM1,
                                         BLECharacteristic::PROPERTY_READ  |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY 
                                       );
  pCharacteristic_room2 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_ROOM2,
                                         BLECharacteristic::PROPERTY_READ  |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY 
                                       );
  pCharacteristic_room3 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_ROOM3,
                                         BLECharacteristic::PROPERTY_READ  |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY 
                                       );                                 
  pCharacteristic_room4 = pService->createCharacteristic(
                                         CHARACTERISTIC_UUID_ROOM4,
                                         BLECharacteristic::PROPERTY_READ  |
                                         BLECharacteristic::PROPERTY_WRITE |
                                         BLECharacteristic::PROPERTY_NOTIFY 
                                       );                                 


  pCharacteristic_room1->setCallbacks(new MyCallbacks());
  pCharacteristic_room1->setValue("value rssi 1");

  pCharacteristic_room2->setCallbacks(new MyCallbacks());
  pCharacteristic_room2->setValue("value rssi 2");
  
  pCharacteristic_room3->setCallbacks(new MyCallbacks());
  pCharacteristic_room3->setValue("value rssi 3");

  pCharacteristic_room4->setCallbacks(new MyCallbacks());
  pCharacteristic_room4->setValue("value rssi 4");
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start();
  Serial.println("server init");
}

void loop() {

  delay(1000);
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true);
  BLEScanResults results = scan->start(1);

  Serial.println("---- New devices found  ----");

  
  for (int i = 0; i < results.getCount(); i++) {

    BLEAdvertisedDevice device = results.getDevice(i);
    int rssi = device.getRSSI();
    String address = device.getAddress().toString().c_str();
    String msg;
    msg += device.getAddress().toString().c_str() + ',' + String(device.getRSSI());

    Serial.print(device.getAddress().toString().c_str());
    Serial.println(device.getRSSI());
    Serial.println("msg sent");
    Serial.println(rssi);

    //char tx[sizeof(msg)]; 
    //strcpy(tx, msg.c_str());
      pCharacteristic_room4->setValue(rssi);
      pCharacteristic_room4->notify(); 
    

    if(address == mac_ancre_1){
      pCharacteristic_room1->setValue(rssi);
      pCharacteristic_room1->notify(); 

    }else if(address == mac_ancre_2){
      pCharacteristic_room2->setValue(rssi);
      pCharacteristic_room2->notify(); 

    }else if(address == mac_ancre_3){
      pCharacteristic_room3->setValue(rssi);
      pCharacteristic_room3->notify(); 
    }

    if(address == mac_ancre_1 || address == mac_ancre_2 || address == mac_ancre_3 || address == mac_test ){
      Serial.println("ancre found");
      if(rssi > CUTOFF){
        digitalWrite(PIN, HIGH);
      }else{
        digitalWrite(PIN, LOW);
      }
    }

  }
}
