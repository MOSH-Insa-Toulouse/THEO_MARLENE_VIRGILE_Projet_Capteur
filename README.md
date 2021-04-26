# THEO_MARLENE_VIRGILE_Projet_Capteur
Ce projet s'inscrit dans l'UF **"Du capteur au banc de Test"** en 4ème année Génie Physique, à l'INSA de Toulouse. 
***
Ce dernier a pour but l'élaboration d'un **capteur de déformation** à bas coût à base de graphite, dont le fonctionnement est basé sur le principe de déplacement des électrons entre les nanoparticules par effet tunnel. A
La contrainte mécanique appliquée modifiant la distance entre les particules, la conductivité électrique de la couche de graphite subit elle aussi une modification. La déformation du capteur créé grâce à un dépôt au crayon à papier engendre donc une variation de résistance alors mesurable.
*** 
Dans ce dossier sont présentées les différentes étapes que nous avons suivies : du design de notre shield, à notre code Arduino en passant par la réalisation d'une application pour téléphone et d'un banc de mesure réalisé en impression 3D. 




## Sommaire 

* [1. Description du projet et détail des livrables](#PremiereSection) 
* [2. Arduino](#DeuxiemeSection)
  * [2.1. Librairies utilisées](#DeuxiemeSection1)
  * [2.2. Code Arduino](#DeuxiemeSection2)
* [3. KICAD](#TroisiemeSection)  
  * [3.1 Symboles et empreintes](#TroisiemeSection1)
  * [3.2 Schématique](#TroisiemeSection2)
  * [3.3 Placement des composants](#TroisiemeSection3)
  * [3.4 Visualisation 3D](#TroisiemeSection4)
* [4. Fabrication du shield](#QuatriemeSection)
  * [4.1 Réalisation du PCB](#QuatriemeSection1)
  * [4.2 Perçage et soudure](#QuatriemeSection2)
* [5. Application Android](#CinquiemeSection) 
* [6. Tests](#SixiemeSection)
  * [6.1. Résultats obtenus](#SixiemeSection1)
  * [6.2. Résultats obtenus](#SixiemeSection2)
  * [6.3. Analyse des résultats et discussion](#SixiemeSection3)
* [7. Datasheet](#SeptiemeSection)

## 1. Description du projet et détail des livrables

Liste des livrables :

- [x] Un code Arduino permettant une mesure de résistance et un contrôle des fonctionnalités Bluetooth, OLED... 
- [x] Un shield PCB
- [x] Une application android APK 
- [x] Un protocole du banc de test
- [x] Une datasheet des capteurs de déformation

Dans un premier temps, nous avons réalisé un **code Arduino** fonctionnel permettant de contrôler un amplificateur transimpédance, un encodeur rotatoire, un écran OLED ainsi qu'un module Bluetooth. Nous l'avons ensuite testé en effectuant nos premiers branchements.
Ensuite, nous avons réalisé le design de notre **shield** à l'aide du logiciel *KICAD*, nous l'avons fabriqué, puis nous avons assemblé nos composants dessus. 
A la suite de cela, nous avons utilisé le logiciel *MIT App Inventor* afin de développer une **application téléphone APK**, capable de communiquer et recevoir des données à distance à l'aide du module Bluetooth (notamment de récupérer la résistance ressentie par le capteur et de l'afficher sur un graphique). 
Nous avons également designé puis réalisé, un **banc de mesure** en impression 3D, qui, à l'aide d'un servomoteur nous permet de caractériser la réponse en déformation de nos futurs capteurs. 
Finalement, nous sommes passés à la phase de tests et avons créé nos capteurs, en les "coloriant" avec divers types de crayons à papier (HB,B,...). Nous avons ensuite caractérisé ces derniers en récupérant leur résistance en fonction de leur déformation, et avons ainsi pu établir une **datasheet**.

## 2. Arduino

### 2.1. Librairies utilisées

- Pour développer notre code, nous avons utilisé plusieurs librairies :["Adafruit_GFX_Library"](Arduino_Shield/prog_arduino) et ["Adafruit_SSD1306"](Arduino_Shield/prog_arduino) nous permettant le contrôle de nos modules.


### 2.2. Code Arduino

[Le code](/Programme Arduino) développé sous Arduino IDE permet la communication du module Bluetooth, de l'OLED ou encore de l'encodeur rotatoire avec le téléphone portable (réception et envoi de données sous forme de bits).
Il permet de récupérer tout d'abord une valeur de tension, puis la valeur de résistance correspondante en fonction de la courbure du capteur.  
Cette valeur est ensuite affichée sur l'écran OLED, ainsi que différents menus via l'encodeur rotatoire. 

## 3. KICAD
