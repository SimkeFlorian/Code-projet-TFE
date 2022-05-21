//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+         TEST ECRITURE ET LECTURE DANS UN FICHIER DE LA CARTE SD                    +//
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//**********************//
//----BIBLIOTHRQUES-----//
//*********************//

#include <SD.h>

//*********************************//
//----Définition des variables-----//
//*********************************//

#define PINCS 10 // le module sera donc branché sur le pin 10 (CS), 11 (MOSI), 12 (MISO), 13 (SCK)
#define filename "testfile.txt"  //déf du nom de fichier test (format 8.3) 
#define wordtest "J'apprend à écrire dans une carte SD avec Arduino!"  //text d'essai que l'on va écrire dans le fichier
File myfile;  //initialisation de mon fichier pour les commandes relatives à la bibli SD.h

//==============================//
//+       CODE PRINCIPALE      +//
//==============================//

//********************//
//-----Void setup-----//
//********************//


/*Remarque pour les print(F()) => le F sert à utilisé moins de place sur l'espace RAM car les donjnées qui
 *seront affichées, seront dans la mémoire flash et non plus dans dans la RAM : Astuciuex pour certains projets!
 */
 
void setup (){
  
  // Initialisation de la liaison série (pour donner les infos au moniteur série de l'Arduino)

  Serial.begin (9600);
  Serial.println("Programme de test d'écriture et de lecture sur une carte SD depuis l'Arduino");
  Serial.println("============================================================================");
  Serial.println();

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

  
  //----------Étape 3 : Ouverture en écriture du fichier 'filename'-------------//

  Serial.println(F("Écriture des données dans le fichier : '"filename"'")); 

  myfile = SD.open(filename, FILE_WRITE); //ouverture du fichier pour écriture seul

  if (myfile){    //condition si on est rentré dans le fichier en écriture
    
    Serial.println(F("Écriture des données suivantes : '"wordtest"' dans le fichier '"filename"'..."));
    myfile.println(wordtest); //écriture du texte dans le fichier ouvert
    myfile.close(); //fermeture du fichier pour sauvegarder 
    }

  //si on a pas su rentré dans le fichier
  else {
    
    Serial.println(F("Échec de l'overture en écriture sur le fichier : '"filename"' dans la carte SD"));
    while (1); //boucle infinie pour sortir du programme;
    }
    
  Serial.println();

  //----------Étape 4 : Lecture des données écrite sur le fichier 'filename'-------------//

  Serial.println(F("Lecture des données présente dans le fichier : '"filename"'..."));
  
  myfile = SD.open(filename, FILE_READ); //ouverture du fichier pour lecture seul

  if (myfile){
    
    Serial.println(F("Affichage du contenu du fichier : '"filename"' présent sur la carte SD ci-après"));
    Serial.write("-> Le texte présent dans le fichier = ");
    while (myfile.available()) {              // Lecture, jusqu'à ce qu'il n'y ait plus rien à lire
      Serial.write(myfile.read());            // ... et affichage sur le moniteur série d'Arduino!
    }
    
    Serial.println();
    myfile.close();                           // Fermeture du fichier et sauvegarde des données
    Serial.println(F("Lecture terminée."));
  }

  else {
    
    Serial.println(F("Échec de la lecture des données dans le fichier : '"filename"' présent sur la carte SD"));
    while (1);
    }
  Serial.println();Serial.println(F("-----FIN DU PROGRAMME-----"));
  }


//********************//
//-----Void loop------//
//********************//

void loop() {
  
  //Vide car tout ne s'affiche qu'une seul fois dans le void setup => pas utilisé ici
  }
