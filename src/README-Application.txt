README.txt

 ------------------------- Utilisation de l'application Projet_Bluetooth ------------------------

Screen 1 : Bluetooth Connection
-> Appuyer sur le bouton Scan pour scanner les alentours à la recherche d'appareils
-> Cliquer sur un élément de la liste
-> Cliquer sur le bouton Connect pour connecter le téléphone avec l'élément de la liste (!! Pas opérationnel !!)

-> Cliquer sur le bouton View Localisation Idea pour passer au screen Localisation Idea

-> Cliquer sur le bouton View Real Localisation pour passer au screen Real Localisation

Screen 2 : Localisation Idea
-> Bouger le slider Phone's X position afin de modifier la coordonnée X du téléphone
-> Bouger le slider Phone's Y position afin de modifier la coordonnée Y du téléphone

-> Observer le label Phone's position qui change en fonction de la position du téléphone et de sa proximité avec les ancres

Screen 3 : Real Localisation
-> Au démarrage de la page, le scan se déclenche automatiquement

-> Chercher les ancres dans la listView ListBLE et cliquer sur les trois (! important de seulement cliquer sur les 3 ancres et non sur d'autres appareils, sinon ça ne fonctionnera pas !)
-> Après avoir cliquer sur les trois ancres, les RSSI des 3 ancres vont s'afficher dans les labels RSSI of ModuleBLE1, 2 et 3

-> Cliquer sur le bouton Calcul X and Y position pour calculer grâce à la triangulation, les coordonnées x et y du téléphone
-> Une fois le bouton cliqué, les labels Phone's X position et Phone's X position vont afficher les valeurs de x et y calculées
-> Puis le téléphone dans le Canvas va se déplacer aux bonnes coordonnées

 -------------- Détails de création et fonctionnement de l'application Projet_Bluetooth ---------------

Screen 1 : Bluetooth Connection
¤ Lorsqu'on appuie sur le bouton scan, l'application va demander la permission d'activer la localisation car cela est nécessaire au bon fonctionnement du scan
¤ A chaque appareil trouvé (when BluetoothBLE.DeviceFound), la liste va s'incrémenter avec le nouvelle élément trouvé

Screen 2 : Localisation Idea
¤ Initialisation de variable global PhoneX et PhoneY afin de conserver les coordonnées et de pouvoir les exploiter (valeur 0 au départ)

¤ Lorsque la position du sliderX change, le téléphone garde la valeur de Y stocké dans la variable PhoneY et récupère la valeur choisie au sliderX puis se déplace en concordance avec ses valeurs
¤ De même pour la position du sliderY avec la valeur de PhoneX et la valeur choisie au sliderY

¤ Ensuite, une condition if est établie afin de vérifier où se trouve le téléphone par rapport aux module 1, 2 et 3
¤ Le canvas est un rectangle de largeur 300 pixels et de hauteur 200 pixels avec le module1 dans le coin haut à gauche, le module2 dans le coin haut à droite 
  et le module3 dans le coin bas à gauche. La distance entre le module1 et le module2 est donc de 300 pixel et la distance entre le module1 et le module3 est de 200 pixel
  En partant du principe que le téléphone est plus proche des modules de gauche si sa coordonnée X est inférieure à 150 et plus proche des modules du haut si 
  sa coordonnée Y est inférieure à 100, les conditions suivantes sont créées :
	- Si PhoneX est inférieure à 150 et PhoneY est inférieure à 100, alors le téléphone est plus proche du module1
	- Si PhoneX est supérieure à 150 et PhoneY est inférieure à 100, alors le téléphone est plus proche du module2
	- Si PhoneX est inférieure à 150 et PhoneY est supérieure à 100, alors le téléphone est plus proche du module3
	- Si PhoneX est supérieure à 150 et PhoneY est supérieure à 100, alors le téléphone n'est proche d'aucun module

Screen 3 : Real Localisation
¤ Initialisation de nombreuses variables qui vont stocker des données :
	- DeviceList pour stocker la liste des 3 ancres
	- ModuleBLE1, 2 et 3 pour stocker les adresses MAC de nos ancres
	- RSSI1, 2 et 3 pour stocker les RSSI de chaque ancre
	- nbpuissance1, 2 et 3 pour stocker les nombres qui vont se trouver dans la puissance de 10 lors du calcul des distances
	- d1, d2, d3 pour stocker le calcul des distances entre les ancres et le téléphone
	- x, y pour stocker la valeur des coordonnées calculées

¤ Création d'une fonction square qui permet de calculer directement

¤ A chaque clic sur une des ancres, la DeviceList va s'incrémenter avec l'élément cliqué. Quand la taille de la liste atteint 3, le parsing commence.
¤ Les éléments de la DeviceList sont sous la forme : MAC NOM RSSI avec chaque paramètre séparé d'un espace. Avec le bloc split at space, il est possible
  de faire de cet élément, une liste de la forme [MAC;NOM;RSSI]. Il est donc possible ensuite de choisir chaque élément de cette liste en indiquant le bon index.
  L'index 1 va permettre de récupérer la MAC, l'index 2 le NOM et l'index 3 le RSSI.
¤ Une condition if est donc créée afin de vérifier si une adresse MAC d'un des trois éléments correspond à l'adresse MAC du module1 stocké dans ModuleBLE1. S'il y a bien
  correspondance, le RSSI de l'élément en question est stocké dans RSSI1.
¤ Les mêmes conditions sont créées pour vérifier les adresses MAC des ModuleBLE2 et ModuleBLE3 puis récupérer les RSSI2 et RSSI3

¤ Après clic sur le bouton Calcul X and Y position, le calcul de triangulation (voir code triangulation par Elyse) est effectué.
¤ Le principe de la localisation du Phone est la même que pour la screen Localisation Idea




