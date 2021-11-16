## Table of Contents


1. [ESP32 Bluetooth Scan] 	(#esp32-bluetooth-scan)
2. [ESP32 Bluetooth Tutorial] 	(#esp32-bluetooth-tutorial)
3. [ESP32 WiFi Com 2] 	(#esp32-wifi-com-2)
4. [ESP32 RSSI MAC] 	(#esp32-rssi-mac)
5. [Inspiration]		(#inspiration)


--------------------------------------------------------------------------------------------
## ESP32 Bluetooth Scan 

*** The Program ***

-   Ce programme permet à l'ESP32 de scanner les signaux bluetooth aux alentours. Il est en attente d'un apparaige d'un autre appareil en face.
     Une fois l'appairage fait, le moniteur série dans l'IDE arduino nous affiche le RSSI de l'appareil connecté.

*** Libraries used ***

< BLEAdvertiseDevice.h >
< BLEDevice.h >
< BLEScan.h >

-------------------------------------------------------------------------------------------

## ESP32 Classic Bluetooth Tutorial 

*** The Program ***

- Ce programme permet à l'ESP32 de dialoguer avec un appareil, en bluetooth.
  Si l'ESP32 reçoit une information, celle-ci est affichée dans le moniteur série.
  Si l'ESP32 envoit des informations, ces dernières sont affichées sur l'appareil connecté.
  L'appareil appairé reçoit les messages (écrit sur l'IDE Arduino), via l'application Android : "Serial Bluetooth Terminal" (disponible sur le PlayStore)

*** Library Use ***

< BluetoothSerial.h >


---------------------------------------------------------------------------------------------

## ESP32 Wifi Com 2

*** The Program ***

 Au préalable, il nous faut un point d'accès Wi-Fi et y entrer l'identifiant ainsi que le mot de passe dans le champs prévu à cet effet, dans le code sous l'IDE Arduino.
 Une fois cela effectué, nous compilons et téléversons le programme sur notre ESP32.
 Il va scanner le point Wi-Fi et tenter de se connecter.
 Attention : Selon les smartphones ANDROID et leur sécurité, la connexion peut-être éphémère ou refusée. C'est le cas avec les smarpthones Google Pixel.

*** Library Use *** 

< WiFi.h >

-----------------------------------------------------------------------------------------------


## ESP32 RSSI MAC

*** The Program ***

  Celui-ci permet de récupérer, le RSSI et l'adresse MAC des modules bluetooth HC-05, ici représentés par des "ancres"
   On différencie ancres en fonction de leur adresse MAC unique.

*** Libraries Use *** 

< BLEAdvertisedDevice.h >
< BLEDevice.h >
< BLEScan.h >

-------------------------------------------------------------------------------------------------

## Inspiration

[ Article ] 

*** Learn ESP32 Classic Bluetooth ***
 >>  https://www.electronicshub.org/esp32-bluetooth-tutorial/

*** ESP32 Bluetooth Classic with Arduino IDE – Getting Started ***
>>  https://randomnerdtutorials.com/esp32-bluetooth-classic-arduino-ide/

*** ESP32 Bluetooth Low Energy (BLE) on Arduino IDE *** 
 >>  https://randomnerdtutorials.com/esp32-bluetooth-low-energy-ble-arduino-ide/

*** Se connecter à un réseau WiFi avec l’ESP32 *** 
>>  https://learn.upesy.com/fr/programming/Arduino-ESP32/esp32_connect_wifi_AP.html#se-connecter-a-un-reseau-wifi-avec-l-esp32


[ Vidéos ] 

*** Bluetooth Proximity Detection | FireBeetle ESP32 ***
>>  https://www.youtube.com/watch?v=azT2rosEo0k

