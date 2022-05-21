//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//            Affichage des données de la carte SD                  //
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

//*********************************//
//----Appel des bibliothèques------//
//*********************************//

#include <SPI.h> //la bibliothèque qui gère la communication SPI avec le module et la carte 
#include <SD.h> //la bibliothèque qui permet un tas de fonctions pour le module carte SD

//*********************************//
//----Définition des variables-----//
//*********************************//

const int pinCS = 10;  //broche de branchement de la carte au pin CS du module SD (D10 par défaut)
Sd2Card CarteSD; //instance carteSD => permet de la démarer
SdVolume VolumeCarteSD; //Volume que peut contenir la carte SD 
uint32_t volumesize; // taille de la carte SD

//==============================//
//+       CODE PRINCIPALE      +//
//==============================//

//********************//
//-----Void setup-----//
//********************//

void setup () {
  
  SD.begin(pinCS); //démarage de la communication avec le module carte SD sur le pin CS

  Serial.begin(9600); //débit d'envoie des données
  Serial.println(F("Les données de votre carte SD sont : "));
  Serial.println(F("--------------------------------------------------------------------------------------"));
  Serial.println();

//.......................................................................................................//
                         
                          //----TEST CARTE SD------//
                          //***********************//

//----------TEST 1 : PRÉSENCE D'UNE CARTE SD OU NON-------------//
 
  if (!CarteSD.init(SPI_HALF_SPEED, pinCS )) {  //test si la carte SD démare et est reconnue en cas de mauvais branchement
    Serial.println(F("Échec lors du démarage de la carte SD. Le problème vient peut-être de : "));
    Serial.println(F("- Mauvais branchement de la carte SD dans le module. "));
    Serial.println(F("- Alimentation mal raccordée"));
    Serial.println(F("- Mauvais pin définit pour le chip select(pin D10, par défaut)"));
    Serial.println();
    Serial.println(F("Appuyez sur RESET pour relancer le programme, au besoin."));
    while (1);      // Boucle infinie, arrêt du programme
  } 
  
  else {
    Serial.println(F("Câblage correct, carte SD trouvée."));
    Serial.println();
  }

//----------TEST 2 : Le type de carte insérée dans le module------------//

  Serial.print(F("Type de carte SD insérée : "));
  
/* Le switch case est similaire à un while plus fort car il va chrcher à rentrer dans une 
 * condition (case) si celle-ci est remplie. Si elle ne rempli pas de condition,
 * le break nous fait sortir du while et par défaut j'indique que la carte est de type inconnue.*/
 
  switch (CarteSD.type()) {   //fonction carteSD.type permet de donner le type de carte
    case SD_CARD_TYPE_SD1:    //chaque condition en fct du type de carte on y rentre ou non
      Serial.println(F("SD1"));
      break;
    case SD_CARD_TYPE_SD2:
      Serial.println(F("SD2"));
      break;
    case SD_CARD_TYPE_SDHC:
      Serial.println(F("SDHC"));
      break;
    default:
      Serial.println(F("Inconnu"));
  }
  Serial.println();


//----------TEST 3 : tentative d'ouverture du volume et de la partition (qui doit être en FAT16, ou FAT32) + affichage du format------------//  

  if (!VolumeCarteSD.init(CarteSD)){     // Vérification du volume de la carte SD avec la fonction Volume.CarteSD.init (CarteSD)
    Serial.println(F("Aucune partition FAT16/FAT32 trouvée."));
    Serial.println(F("Vérifiez si votre carte SD est bien formatée !"));
    while (1);      // Boucle infinie, arrêt du programme
  } 
  
  else {
    Serial.print(F("Format du volume : FAT"));
    Serial.println(VolumeCarteSD.fatType(), DEC); //Affichage du format de la carte SD avec la fct VolumeCarteSD.fatType () en valeur décimale (DEC). 
  }

  //----------TEST 4 : affichage de la taille et du volume, en KB/MB/GB

/* Le but ici va être d'afficher la taille en KB/MB/GB de libre dans notre carte SD */

  volumesize = VolumeCarteSD.clusterCount() * VolumeCarteSD.blocksPerCluster(); //rentre la valeur de la taille de notre carte dans la variable volumesize
  volumesize = volumesize / 2;         // Rem : les blocs d'une carte SD font toujours 512 octets (il faut donc 2 blocs pour faire 1KB)
  Serial.print(F("Taille du volume (en KB): ")); Serial.println(volumesize);
  Serial.print(F("Taille du volume (en MB): ")); Serial.println(volumesize / 1024);
  Serial.print(F("Taille du volume (en GB): ")); Serial.println(volumesize / 1024 / 1024.0); //Convertion en MB et GB depuis les KB 
  Serial.println();

  Serial.println(F("Fin !"));
 
  }

//********************//
//-----Void loop------//
//********************//

void loop() {
  
  //Vide car tout ne s'affiche qu'une seul fois dans le void setup => pas utilisé ici
  }
