# THEO_MARLENE_VIRGILE_Projet_Capteur
Ce projet s'inscrit dans l'UF **"Du capteur au banc de Test"** en 4ème année Génie Physique, à l'INSA de Toulouse. 
***
Ce dernier a pour but l'élaboration d'un **capteur de déformation** à bas coût à base de graphite, dont le fonctionnement est basé sur le principe de déplacement des électrons entre les nanoparticules par effet tunnel. 
La contrainte mécanique appliquée modifiant la distance entre les particules, la conductivité électrique de la couche de graphite subit elle aussi une modification. La déformation du capteur créé grâce à un dépôt au crayon à papier engendre donc une variation de résistance alors mesurable.
*** 
Dans ce dossier sont présentés les différentes étapes que nous avons suivies : du design de notre shield, à notre code Arduino en passant par la réalisation d'une application pour téléphone et d'un banc de mesure réalisé en impression 3D. 




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
  * [6.1. Banc de test](#SixiemeSection1)
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

Pour développer notre code, nous avons utilisé plusieurs librairies :["Adafruit_GFX_Library"](/Librairies/Adafruit_GFX_Library) et ["Adafruit_SSD1306"](/Librairies/Adafruit_SSD1306) nous permettant le contrôle de nos modules, ainsi que la librairie [Adafruit_BusIO](/Librairies/Adafruit_BusIO) permettant de gérer la connexion en I2C et SPI.


### 2.2. Code Arduino

Le code [prog_arduino](/Programme%20Arduino/prog_arduino) développé sous Arduino IDE permet d'assurer la communication de tous les éléments de notre carte Arduino (Module Bluetooth, Oled et encodeur rotatoire) afin de réaliser des fonctions voulues. Nous avons ainsi réalisé quatre menus différents qui permettent de réaliser des tâches différentes. 

- Le premier menu permet d'afficher sur l'Oled la valeur de résistance de la jauge de contrainte traduite par l'acquisition de la tension de sortie de notre circuit électronique. Il permet aussi d'envoyer via le module bluetooth la valeur de tension mesurée entre 0 et 5 volts, sous la forme d'un nombre codé en 8 bits : 0 correspondant à 0V et 255 correspondant à 5V. L'objectif de cet envoi est d'ensuite le récupérer via notre application APK pour pouvoir traiter les données.
- Le second menu est assez similaire. La seule différence réside sur l'affichage de l'Oled. On n'affiche plus la valeur de résistance mais la valeur de tension. 
-  Le troisième menu permet de définir un temps d'acquisition sur l'application. On choisit la valeur en secondes grâce à l'encodeur rotatoire et lorsqu'on sélectionne la valeur choisie, elle s'envoie par Bluetooth pour être récupérée et enregistrée par l'application.
-  Le quatrième menu fonctionne de la même manière que le troisième mais permet de changer la valeur de R2 que l'on a laissé variable afin de s'adapter à la plage de mesure de la résistance du capteur. On entre la valeur voulue grâce à l'encodeur rotatoire. 


Les codes contenus dans les dossiers [BT_Test](/Programme%20Arduino/BT_Test), [ENC_TEST](/Programme%20Arduino/ENC_TEST) et [OLED_TEST](/Programme%20Arduino/OLED_TEST) permettent de vérifier individuellement l'état de fonctionnement de chaque module ajouté à notre shield. 


Enfin, Le code Arduino [Servomoteur](/Programme%20Arduino/Banc%20de%20test/Servomoteur) permet de contrôler notre banc de test et sera plus amplement expliqué dans la partie **6. Tests**.
 

## 3. KICAD

### 3.1. Symboles et empreintes
- Module Bluetooth 

<img src="/Images/Bluetooth2.png" width="400" height="150"> <img src="/Images/Bluetooth.png" width="250" height="150">


- Encodeur rotatoire 

<img src="/Images/Encodeur2.png" width="400" height="150"> <img src="/Images/Encodeur.png" width="250" height="150">


- Ecran OLED 

<img src="/Images/OLED2.png" width="350" height="150"> <img src="/Images/OLED.png" width="250" height="150">

- Amplificateur LTC 1050

<img src="/Images/LTC10502.png" width="275" height="150"> <img src="/Images/LTC1050.png" width="375" height="150">


### 3.2. Schématique de l'ensemble 

![Glob](/Images/Global.png)

Une fois les empreintes créées, nous avons pu réaliser le Eeschema de notre shield. En haut à droite sont représentées les broches de la carte Arduino. Au centre est représenté l'amplificateur transimpédance, et en bas l'écran OLED, le module Bluetooth et l'encodeur rotatoire.

### 3.3. Placement des composants
![Rout](/Images/Routage.png)

### 3.4. Visualisation 3D
<img src="/Images/3D.png" width="400" height="300"> <img src="/Images/3D%20dos.png" width="400" height="300">


## 4. Fabrication du shield
### 4.1. Réalisation du PCB

 Nous avons ensuite pu fabriquer le PCB sur une plaquette d'epoxy recouverte d'une fine couche de cuivre (environ 60µm).  
 Tout d'abord, nous avons imprimé notre modélisation du PCB sur du papier calque, puis, une insolation aux UV pendant 2 minutes a permis de transposer cette "silhouette" sur notre couche d'epoxy, permettant ainsi de déposer une résine protectrice, qui grâce à un révélateur, a pu être retirée aux endroits désirés.  
 Ensuite, la plaquette a été déposée dans un bain de perchlorure de fer afin d'être gravée (environ 8 minutes). A la suite de cela, le cuivre non protégé par la résine a alors été retiré, permettant d'obtenir le PCB modélisé en amont.  
 Pour finir, de l'acétone a été appliquée sur la plaquette pour éliminer les dernières traces de résine.


### 4.2. Perçage et soudure

Une fois le PCB réalisé, nous sommes passés au perçage de trous sur notre plaquette à l'aide d'une perçeuse électrique afin d'insérer nos composants : 
- 0.8mm de diamètre pour l'AOP, les résistances et les capacités
- 1mm de diamètre pour les connecteurs de l'Arduino et des headers des différents modules (pinces du capteur, bluetooth, encodeur rotatoire, écran OLED)

Enfin, nous avons soudé chaque composant à l'aide d'un fer à souder.

## 5. Application Android

[L'application](/Application) développée sous MIT App Inventor, un site internet permettant de designer des applications en ligne, permet d'établir la liaison entre les données relevées par l'arduino et le traitement de celles-ci, en direct puis via la création d'un fichier de données. 

Concrètement, l'application a été designée pour corréler avec le code arduino (cf 2.). Elle permet ainsi de se connecter à un module bluetooth chargé d'envoyer la tension relevée, qui sera traduite en résistance pour le capteur. Lorsque l'on est connecté, l'application est capable d'effectuer 3 tâches principales : 
- Relever la tension envoyée par Bluetooth, afficher la valeur de résistance correspondante, de manière numérique et graphique et la traduire dans un fichier texte. Cette fonction est commandée par un système Start/Stop.
- Effectuer une acquisition selon un temps donné. Il faut au préalable définir le temps d'acquisition via l'arduino. Ce temps vient remplacer le Start/Stop, sinon la fonction est la même que précédemment.
- Modifier la valeur de résistance de R2. Pour cela, il faut rentrer la valeur via l'arduino.

## 6. Tests
### 6.1. Banc de test

Pour réaliser nos tests, nous avons utilisé 2 bancs différents ; l'un déjà existant et pensé par nos prédécesseurs et un autre par nos soins lors de la réalisation du projet.

#### Le [banc de test](/Banc%20de%20test) que nous avons imaginé a été modélisé via un logiciel de CAO et ensuite imprimé grâce à une imprimante 3D. 


<img src="/Images/BancTest.jpg" width="400" height="300"> <img src="/Images/BancTest2.jpg" width="400" height="300">  

Il permet de mesurer la déformation du capteur en fonction du temps grâce à une rotation induite par un servomoteur et répond à deux problématiques :
 - La première étant la limite principale du banc de test déjà existant : il était destructif. En effet à chaque utilisation de celui-ci le capteur devenait inutilisable par la suite. Il nous était donc impossible de revenir aux valeurs initiales de résistances après passage du capteur sur le banc de test. 
- La seconde étant la volonté d’observer l’évolution en dynamique de la réponse du capteur afin de déterminer une potentielle fatigue de celui-ci lors d’un test cyclique. 

Nous avons donc réfléchi à un design permettant une installation fixe du capteur qui ne nécessitait plus d’action extérieure au cours de la mesure, et qui pouvait faire périodiquement une application de contrainte identique sur notre capteur. Pour cela, notre banc a été conçu en 3 parties : le socle, la pièce « escargot » et le servomoteur, pilotés via [un code Arduino](/Programme%20Arduino/Banc%20de%20Test/Servomoteur) supplémentaire. 

**Le socle**

<img src="/Images/Socle.png" width="400" height="300"> 
Le socle est la pièce massive qui permet de fixer le servomoteur et le capteur afin de ne pas avoir à retoucher le système entre les mesures.  

•	 La languette sur le côté gauche représente la zone permettant de fixer le capteur à l’aide des pinces conductrices.   
•	 Le demi cercle vide au milieu de la pièce correspond à la zone permettant la rotation de la pièce « escargot ».  
•	 L’encoche qui traverse la pièce dans la largeur permet de glisser le servomoteur et de le maintenir dans la position souhaitée.  


**La pièce « escargot »**

<img src="/Images/Escargot%20Dimensions.png " width="400" height="300"> 

Cette pièce est un embout pour le servomoteur : l’extrémité libre du capteur repose dessus lorsqu’il est fixé sur le banc. 
Le rayon de l’embout augmente d’un millimètre tous les dix degrés de rotation ce qui permet d’avoir une variation du rayon entre 5,5 mm et 21,5 mm sur l’ensemble de la rotation du servomoteur.   

Nous souhaitions pouvoir remonter à la déformation en connaissant la longueur du rayon or après plusieurs tentatives, nous nous sommes rendus compte qu’il était difficile de remonter à cette valeur en compression avec la composition géométrique de ce banc de test.   


**Le servomoteur**

Nous avons choisi d’utiliser le servomoteur SG90 car parmi ceux à notre disposition, c’est celui dont les dimensions étaient les plus adaptées pour notre capteur.   
En effet sa petite taille nous permet d’y fixer un embout de plus petite taille qui nous assure de rester dans le domaine de la déformation élastique du papier puisque nous pouvons  appliquer des déformations plus faibles et plus précises.   
Utiliser un servomoteur nous permet de gérer facilement la rotation de la pièce «escargot», et in extenso de fixer facilement la plage de déformation du capteur à l’aide du code Arduino. 


**Le code Arduino**

Nous avons utilisé [ce code Arduino](/Programme%20Arduino/Banc%20de%20test/Servomoteur) qui nous permet de changer la plage de rotation du servomoteur. Il nous permet en modifiant les lignes 17 et 22 de changer la plage de rotation du servomoteur. L’objectif étant de balayer la plus grande différence de rayon possible tout en ne dépassant jamais le bout de course de la pièce escargot afin de ne pas détruire le capteur.  


                                                                                              

#### Le banc de test déjà réalisé composé de 7 demi-cercles dont les rayons varient de 1 à 2,5 cm. 
<img src="/Images/BancTest3.png" width="400" height="300"> 


### 6.2. Résultats obtenus

**Avec le banc de test utilisant le servomoteur**

<img src="/Images/Graph%20temps.png" width="800" height="400">   

Nous pouvons voir que la jauge réagit de façon périodique à la contrainte du banc en dynamique. 
En effet, lors de la diminution du rayon de la pièce en escargot, nous observons une augmentation quasi-linéaire de la résistance (cf courbe ci-dessus zone 1). 
Lors de l'augmentation de celui-ci, nous observons une diminution quasi-linéaire de la résistance de la jauge de contrainte (cf courbe ci-dessus zone 2).
Nous observons également une plage de données instable entre ces deux phases. Cette réponse du capteur est due à l’imperfection de notre banc (cf courbe ci-dessus zone 3). En effet, lorsque l’on arrive au bout de la course du servomoteur, le capteur ne suit pas complètement l’évolution du rayon de courbure, et entre en contact avec une autre surface de la pièce en « escargot » que celle souhaitée. 

**Avec le banc de test déjà réalisé**

<img src="/Images/Graphs.png" width="700" height="900"> 

Comme nous pouvons l’observer sur les graphiques ci-dessus, la plupart des réponses des jauges aux déformations appliquées à l’aide du banc de test statique suivent une évolution quasi-linéaire. 

La résistance sans contrainte varie du simple au double entre deux jauges produites par le même type de crayon à papier. 

Les variations de résistance sont plus importantes lorsque la dureté du crayon est plus élevée. En effet, pour le HB nous avons pu observer au maximum une variation de 5 à 20 MOhms et pour le 2B de 4 à 5 MOhms. 

Les facteurs de jauge obtenus en faisant une approximation linéaire sont de :
- 6,5 et 3,2 pour les essais 1 et 2 avec des jauges dessinées avec des crayons 2B
- 6,1 et 11,4 pour les essais 1 et 2 avec des jauges dessinées avec des crayons B
- 13,1 et 27,2 pour les essais 1 et 2 avec des jauges dessinées avec des crayons HB



### 6.3. Analyse des résultats et discussion

Nous observons à l’aide de **notre banc de test** utilisant le servomoteur que le capteur retrouve sa valeur initiale de résistance entre chaque mise sous contrainte. Nous n’observons donc pas de fatigue de la jauge dans la gamme de contraintes que nous appliquons : il faudrait effectuer des tests sur de très longues périodes avant d’apercevoir d’éventuelles fatigues. 

Concernant les imprécisions de la zone de mesure se situant en bout de course du servomoteur, plusieurs améliorations sont envisageables : 
 - Concevoir la pièce « escargot » en miroir, de façon à toujours avoir un rayon plus petit sous la jauge au lieu du contraire actuellement
 - Repenser la pièce afin de pouvoir fixer directement l’extrémité du capteur à la pièce « escargot »

Nous aurions pu également réfléchir en amont au calcul de contrainte qui aurait été plus pertinent qu’un simple relevé de résistance.  
  
Ces différents résultats mettent en valeur les avantages et les limites de ce type de jauges de contrainte.   


Pour ce qui est du **banc de test déjà réalisé**, nous constatons que les jauges réalisées ont, d'après les essais, des facteurs de jauge très élevés avec l’utilisation de crayons à papier à pointe dure, mais que, si le crayon dépose trop peu de graphite, des problèmes de continuité électrique se posent.  

Une des principales limites est donc la dépose du graphite. En effet, nous remarquons des différences de quasiment un facteur 2 entre les facteurs de jauge des capteurs dessinés en 2B, B et HB. 
Ces différences peuvent être dûes à :
 - la non-répétabilité de la mesure et la destruction du capteur en fonction de la manipulation de la jauge et du banc
 - le dépôt de graphite sur le papier : la pression avec le crayon à papier, le nombre de passages du crayon, la précision du tracé    

Il faudrait réfléchir à un procédé permettant un dépôt uniforme, précis et répétable. Une impression mécanique automatisée serait une option pour rendre les facteurs de jauge plus constants.  

Nous pouvons tout de même conclure que la confection de jauges de contrainte en graphite est réalisable et permet de créer des jauges avec de très bon facteurs de jauge. 
Néanmoins, le processus de dessin doit être optimisé car il y a beaucoup trop de paramètres qui ne permettent pas de garantir la qualité de la jauge de contrainte. 


## 7. Datasheet

La [Datasheet](/Datasheet) présente l'ensemble des caractéristiques des jauges que nous avons réalisées ainsi que du shield qui permet de traduire un relevé de tension en mesure de résistance. L'objectif final est de revenir à une mesure de déformation. 