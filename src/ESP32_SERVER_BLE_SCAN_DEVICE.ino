#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEServer.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>
#include <BLE2902.h>

#include <string>
#include <iostream>

// https://www.uuidgenerator.net/  

#define SERVICE_UUID        "29943f82-85c2-4fd4-ab41-0c2a6f7af32a"

#define CHARACTERISTIC_UUID_ROOM1 "5322ceb0-a48f-42bc-ad8b-28670fefee5a"  // ancre 1 
#define CHARACTERISTIC_UUID_ROOM2 "5d6ed9ec-4db5-4c75-8dca-4567ab5af830"  // ancre 2
#define CHARACTERISTIC_UUID_ROOM3 "addbf900-ac76-4b38-afff-ba06f6c7b18d"  // ancre 3
#define CHARACTERISTIC_UUID_ROOM4 "35e706b4-031b-4c52-a25f-f7ca96045313"  // ancre 4 ( implémenté mais pas utlisée pour le momment)

#define CUTOFF -50 // seul de sensiblité ( endBm)
#define PIN 2   // Pin de selection pour la led blache 

BLECharacteristic *pCharacteristic_room1;
BLECharacteristic *pCharacteristic_room2;
BLECharacteristic *pCharacteristic_room3;
BLECharacteristic *pCharacteristic_room4;

String mac_ancre_1 = "10:52:1c:5a:c2:0e"; // MAC ancre 1
String mac_ancre_2 = "c8:c9:a3:d1:4c:72"; // MAC ancre 2
String mac_ancre_3 = "fc:f5:c4:26:f5:8e"; // MAC ancre 3
String mac_test =    "f8:0a:c2:86:4a:4d"; // MAC montre connecté pour test 

class MyCallbacks: public BLECharacteristicCallbacks { // fonction qui lire les données recu depuis un client qui se connecte au service 
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
  Serial.begin(115200); //configuration du port uart a 115200 bauds 

  BLEDevice::init("MyESP32-TAG");
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
  pCharacteristic_room1->setValue("value rssi 1"); //mise d'une valeur par défaut 

  pCharacteristic_room2->setCallbacks(new MyCallbacks());
  pCharacteristic_room2->setValue("value rssi 2"); //mise d'une valeur par défaut 
  
  pCharacteristic_room3->setCallbacks(new MyCallbacks());
  pCharacteristic_room3->setValue("value rssi 3"); //mise d'une valeur par défaut 

  pCharacteristic_room4->setCallbacks(new MyCallbacks());
  pCharacteristic_room4->setValue("value rssi 4"); //mise d'une valeur par défaut 
  pService->start();

  BLEAdvertising *pAdvertising = pServer->getAdvertising();
  pAdvertising->start(); //lancement du serveur 
  Serial.println("server init");
}

void loop() {

  //delay(100);
  BLEScan *scan = BLEDevice::getScan();
  scan->setActiveScan(true); // scan active plus performant mais plus gourment en énergie 
  BLEScanResults results = scan->start(1); .. résultat du scanner 

  Serial.println("---- New devices found  ----");

  
  for (int i = 0; i < results.getCount(); i++) { // balayage du scan, etude de chaque device trouvé  
 
    BLEAdvertisedDevice device = results.getDevice(i);
    int rssi = device.getRSSI(); // recuperation du rssi 
    String address = device.getAddress().toString().c_str(); //recupération de l'@ mac
    String msg; 
    msg += device.getAddress().toString().c_str() + ',' + String(device.getRSSI()); //creation d'une tram 
    Serial.print(device.getAddress().toString().c_str()); //affichage de la tram 
    Serial.println(device.getRSSI()); //affichage de la valeur rssi 
    {
      Serial.println("-----------------");
      Serial.print("rssi:");
      Serial.println(rssi);
      float rssi_to_m =  pow(10, ((-69 - (float(device.getRSSI())) ) / (10 * 2)) );  // calcul du rssi en distance ( -69 corespond à 1m ) 
      Serial.print("distance:");
      Serial.println(rssi_to_m);
    }
    Serial.println("msg sent");
    Serial.println(rssi);

    //char tx[sizeof(msg)]; 
    //strcpy(tx, msg.c_str());
      pCharacteristic_room4->setValue(rssi);  //mise à jour de la Characteristic 4 (debug dans le cas pratique)
      pCharacteristic_room4->notify();  //
    

    if(address == mac_ancre_1){ //si l'ancre 1 est trouvée 
      
      pCharacteristic_room1->setValue(rssi); // mise à jour de la characteristic 1
      pCharacteristic_room1->notify();  //notifier le serveur pour metre à jour la valeur 
      if(rssi > CUTOFF){ 
        Serial.println("ancre 1 found");
        float rssi_to_m =  pow(10, ((-69 - (float(device.getRSSI())) ) / (10 * 2)) ); 
        Serial.print("distance:");
        Serial.println(rssi_to_m);
        digitalWrite(PIN, HIGH);
      }else{
        digitalWrite(PIN, LOW);
      }

    }else if(address == mac_ancre_2){ //si l'ancre 2 est trouvée 

      pCharacteristic_room2->setValue(rssi); // mise à jour de la characteristic 2
      pCharacteristic_room2->notify();       //notifier le serveur pour metre à jour la valeur 
      if(rssi > CUTOFF){
        Serial.println("ancre 2 found");
        float rssi_to_m =  pow(10, ((-69 - (float(device.getRSSI())) ) / (10 * 2)) ); 
        Serial.print("distance:");
        Serial.println(rssi_to_m);
        digitalWrite(PIN, HIGH);
      }else{
        digitalWrite(PIN, LOW);
      }

    }else if(address == mac_ancre_3){ //si l'ancre 3 est trouvée 
      
      pCharacteristic_room3->setValue(rssi); // mise à jour de la characteristic 3
      pCharacteristic_room3->notify();       //notifier le serveur pour metre à jour la valeur 
      if(rssi > CUTOFF){
        Serial.println("ancre 3 found");
        float rssi_to_m =  pow(10, ((-69 - (float(device.getRSSI())) ) / (10 * 2)) ); 
        Serial.print("distance:");
        Serial.println(rssi_to_m);
        digitalWrite(PIN, HIGH);
      }else{
        digitalWrite(PIN, LOW);
      }
    }
    }

  }
