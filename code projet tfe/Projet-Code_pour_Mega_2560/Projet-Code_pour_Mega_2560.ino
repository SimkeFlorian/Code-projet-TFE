/*
========================
    Code projet TFE
========================



Ce code est le fruit de la production de mon travail. Il a été réalisé à l'ai de la documentation
de la bibliothèque fourni par Arduino : 
https://www.arduino.cc/en/reference/SD?pseSrc=pgCarteSdArduino;
Je me suis également inspiré de ce qu'un compte proposait sur la bibliothèque SD.H : https://passionelectronique.fr/carte-sd-arduino/


==============================================================================================================
||           _                                                                      _                       ||
||          (_)                                                                    (_)                      ||
||     ___   _   _ _ _ _ _   _   _    __               _ _ _   _     ___     _ ___  _     ___     _ _ _     ||
||    | __| | | |  _   _  \ | |/ /  /  _ \   ______   /  _ _| | |  /     \  | '__/ | |  /  _  \  |  _  \    ||
||    |__ | | | | | | | | | | |\ \ |   __/  |______|  | |---  | | |  (_)  | | |    | | |  ( )  | | | | |    ||
||    |___| |_| |_| |_| |_| |_| \_\ \____|            |_|     |_|  \ ___ /  \_|    |_|  \ ___,_| |_| |_|    ||
==============================================================================================================

Nom : Simke
Prénom : Florian
Profession : Étudiant
École : HEH campus technique
Option : Bioélectronique et instrumentation

*/

/*
  =====================================
           BIBLIOTHÈQUES
  =====================================
*/
#include <SD.h> //Bibliothèque pour le module SD avec le protocole SPI

//=====================================================================================//

#include <Wire.h> //Biliothèque pour le protocole I2C
#include <RTC.h>  //Bilibothèque pour le module RTC


/*
  =====================================
           Variables
  =====================================
*/
#define PINCS 53 // le module sera donc branché sur le pin 53 (CS), 51 (MOSI), 20 (MISO), 52 (SCK)
#define filename "datafile.txt"  //déf du nom de fichier test Excel (format 8.3) 
File myfile;  //initialisation de mon fichier pour les commandes relatives à la bibli SD.h

//==========================================================================================================//

int incomingByte = 0;
static DS1307 RTC; // Définition de la variable RTC comme variable static 

/* Les variables static sont des variables dont leur valeurs
 *  persisteront au-delà de l'appel de fonction, elles ne bougent pas
 */



/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID SETUP / FCT PRINCIPAL
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
============================================================================================*/

void setup() {

  // Initialisation avec le port série 0 IDE Arduino
  Serial.begin(9600);
  // Initialisation du port série 1 sur lequel les données seront reçues
  Serial1.begin(115200);

// =========================================
//              PARTIE CARTE SD           
// =========================================


    //----------Étape 1 : Test de l'accésibilité de la carte SD depuis Arduino-------------//

  /*Il est impératif de tester si on a accéder à la carte si non
   * pourquoi continuer le code ?
   */

  Serial.println(F("Initialisation de la carte SD..."));

  if(!SD.begin(PINCS)){   //condition si la carte SD n'a pas démarrée
    
    Serial.println(F("Échec de l'initilisation de la carte SD !"));
    while (1); //boucle infini (stop le programme à cette étape)
    }

   //si la carte SD a démarrée :
   Serial.println(F("Initialisation terminée avec succès !"));
   Serial.println();

     //----------Étape 2 : Suppression du fichier 'file name' s'il existe déjà-------------//

  /* Je test ici si le fichier dans lequel je vais écrire existe ou non
   *  SI non le fichier n'existe pas et on continue lz programme
   *  SI oui le fichier existe je vais le supprimer pour le remplacer par un nouveau par la suite
   *  Remarque  : il s'agit d'un test la suppression du fichier n'est pas obligatoire,
   *  il est même absurde dans un projet de supprimer constament sont fichier au risque 
   *  de perdre les données qu'il contient
   */

  Serial.println(F("Vérification de l'existance du fichier : '"filename"'..."));
  if (!SD.exists(filename)){  //condition si le fichier n'existe pas
    
    Serial.print(F("Fichier '" filename "' inexistant."));
    }

  else {

    Serial.println(F("Fichier '" filename "' déjà existant"));
    Serial.println(F("Lancement de la suppression du fichier : '" filename "' ...")); 
    Serial.println();
    
      //----ON SUPPRIME LE FICHIER S'IL EXISTE DÉJÀ----//

      if (!SD.remove(filename)){    //condition si le fichier n'a pas été détruit...
        
        Serial.println(F("Échec de la suppression du fichier : '"filename"' présent sur la carte SD"));
        while (1); //boucle infinie pour l'arrêt du programme
        }

      //si le fichier a été supprimé
      else{
        
        Serial.println(F("Suppression du fichier : '"filename"' sur la carte SD réussi avec succès"));
        }

  }
  Serial.println();

// =========================================
//              PARTIE MODULE RTC           
// =========================================

  RTC.begin();  //Démarage du RTC

/*partie à décommentée pour ajuster l'heure et la date du module et puis remettre en commentaire*/
  //RTC.setDateTime(__DATE__, __TIME__); 
  
  Serial.print("Is Clock Running: "); //Affichafe dans le terminal
  if (RTC.isRunning())  //Fonction RTC.isRunning => vérification si le module est alimenté ou pas
  {

  //-- Si OUI --//
    Serial.println("Yes");
    RTC.setHourMode(CLOCK_H24);
    }
    
  else
  {
  //-- Si NON --//
    Serial.println("No"); //Afficha que le module est pas en trein de tourner
    Serial.println("Setting Time");
    //RTC.setHourMode(CLOCK_H12); //option de l'affichage de l'heure sous format 12H
    RTC.setHourMode(CLOCK_H24); //option de l'affichage de l'heure sous format 24H => préféré par moi même
    RTC.setDateTime(__DATE__, __TIME__);  //Mise à jour de la date et l'heure selon celles du pc
    RTC.startClock(); //commencement de l'horloge
  }

   //--------------------Partie Récepetion données et écriture dans le fichier------------------//

    Serial.print("Attente de la connexion série");
    while (!Serial1){
    Serial.print("...");
    }  
 
}


/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID LOOP / EXECUTION DU PROGRAMME
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
==============================================================================================*/

void loop() {
  
  Serial.println();


  //--------------------Partie Récepetion données et écriture dans le fichier------------------//

  Serial.println();
  
  while (Serial1.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial1.read() + (Serial1.read() << 8) + (Serial1.read() <<16) + (Serial1.read() <<24);

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
  }
  

  // Ouverture du fichier dans la carte SD en écriture seule
  myfile = SD.open(filename, FILE_WRITE); //ouverture du fichier pour écriture seul

  // Si je suis dans le fichier...
  if (myfile) {
    
    //---------------------Partie RCT et date_time----------------//

    // J'écris seulement la date dans le terminal de l'IDE
    Serial.print(RTC.getDay());
    Serial.print("-");
    Serial.print(RTC.getMonth());
    Serial.print("-");
    Serial.print(RTC.getYear());
    Serial.print("    ");

    // Série de if pour rajouter des '0' si on est à moins de 10 en HH,MM ou SS
    // Ecriture des valeurs de temps dans la carte SD et sur le terminal d'Arduino
    if (RTC.getHours() < 10) {
      Serial.print("0"); myfile.print("0");
      }
    Serial.print(RTC.getHours()); myfile.print(RTC.getHours());
    Serial.print(":");  myfile.print(":");

    if (RTC.getMinutes() < 10) {
      Serial.print("0"); myfile.print("0");
      }
    Serial.print(RTC.getMinutes()); myfile.print(RTC.getMinutes());
    Serial.print(":");  myfile.print(":");

    if (RTC.getSeconds() < 10){
      Serial.print("0");  myfile.print("0");
      }
    Serial.print(RTC.getSeconds()); myfile.print(RTC.getSeconds());
    Serial.print(""); myfile.print("\t"); 
    
    Serial.println("");

    Serial.println(F("Écriture sur le finchier '"filename"' possible"));

    // J'écris ensuite la données reçue sur le port série contenue dans 'variable'
    myfile.print(incomingByte);
    myfile.println();
    myfile.close();
    
  }

  // Si je n'accède pas au fichier...
  else {

    Serial.println(F("Écriture sur le fichier '"filename"' imposible"));
    while(1); // boucle infinie
    }
 
  delay(500); //délai avant de reprendre la boucle
}
