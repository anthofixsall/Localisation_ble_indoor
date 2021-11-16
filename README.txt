PROGRAMME DE LOCALISATION 
** ------------------------------------------------ ** 
Compilation du programme de localisation :
 gcc trilateration.c -o trilateration -lm

Exécution du programme de localisation :
 ./trilateration

** ------------------------------------------------ ** 

CONFIGURATION DES HC-05 VIA ARDUINO
** ------------------------------------------------ ** 
Utilisation des commandes AT pour la configuration du dispositif
       AT+ROLE = 0 ==> Mode Slave
       AT+CMODE = 1 ==> Visible à tous
       AT+IAC= 9e8b33 ==> Code identificateur service
       AT+NAME = Balise_A ==> Nom visible en Bluetooth
       AT=STATE ==> Verification de l'etat du dispositif
       AT=RESET ==> Redemarrage du appareil
Attention : Entre chaque commande AT ==> besoin de delay pour plus d'efficacité
Posibilite d'entrer en mode AT pendant demarrage et pendant fonctionement ==> Activation de la pin EN du HC-05 pour entrer en mode AT.

** ------------------------------------------------ ** 
