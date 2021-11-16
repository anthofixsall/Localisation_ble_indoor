#include <SoftwareSerial.h>

SoftwareSerial BTSerial(2, 3); // RX | TX
#define BT_Key 9   //Key Pin du HC-05
#define BaliseID 'C' // Identificateur Balise

void setup()
{
  //Pin pour activation du  AT mode
  pinMode(BT_Key, OUTPUT); 
  digitalWrite(BT_Key, HIGH);
  Serial.begin(38400);
  Serial.println("Configuration de la Balise en Cours");
  //Vitesse Communication Module and Arduino
  BTSerial.begin(38400);   
  delay(3000);
  //Configuration en Slave du Module HC-05
  // Le role (0 = Slave || 1 = Master)
  Serial.write("AT+ROLE=0\r\n");
  BTSerial.write("AT+ROLE=0\r\n");
  Serial.write(BTSerial.read());
  delay(1000);
  // Mode de fonctionnement (0 = Attachement par @ || 1 = Visible à tous)
  Serial.write("AT+CMODE=1\r\n");
  BTSerial.write("AT+CMODE=1\r\n");
  Serial.write(BTSerial.read());
  delay(1000);
  // Inquire Acces Code ( 9e8b33 (HEXA) = Code Generale pour IAC) 
  //                    ( XXXXXX = Code Personalisé)
  Serial.write("AT+IAC=9e8b33\r\n");
  BTSerial.write("AT+IAC=9e8b33\r\n");
  Serial.write(BTSerial.read());
  delay(1000);
  // Identificateur de la Balise
  Serial.write("AT+NAME=Balise ");
  Serial.write(BaliseID);
  Serial.write("\r\n");
  BTSerial.write("AT+NAME=Balise ");
  BTSerial.write(BaliseID);
  BTSerial.write("\r\n");
  Serial.write(BTSerial.read());
  delay(1000);
  Serial.println("Configuration Balise Realisé");
  // Reset pour entrer en mode Balise et desactivation du mode AT
  digitalWrite(BT_Key, LOW);
  BTSerial.write("AT+RESET\r\n");
  delay(2000);
  digitalWrite(BT_Key, HIGH);
}

void loop()
{    
  // Si connexion etablie ==> echange des données
    String Data = " ";
    if (Serial.available())
    BTSerial.write(Serial.read());
    
    if (BTSerial.available())
    {  
       Data = BTSerial.readString();
       Serial.print(Data);
    }  
}
