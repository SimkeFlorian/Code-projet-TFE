                 //----------------------------------//       
                    // CODE PROJET TFE en filaire  //
                 //----------------------------------//
				 
// ===============================================================================================	//

	/* pour ce TFE, je vais monitorer l'activité des muscles respiratoires avec 
	*un capteur FSR et faire correspondre ces variations de tensions 
	*avec une heure et une date précise. Le tout sera inscrit dans un 
	*fichier Excel ou txt créé sur une carte micro SD. 
	--------------------------------------------------------------------------------------------
	*Le projet allie donc deux types de communication : SPI et I2C 
	*il y aura du traiement analogique vers le numérique avec le capteur flexible 
	*ainsi que du traitement de fichier avec les commandes pour le module lecteur SD Arduino
	*il s'agit donc d'un projet relativement complet sur le plan codage et communication électronique
	*/

// ===============================================================================================	//

/*
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

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<0>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>//


				//********************************************//
				//-------Déclarations des bibliothèques-------//
				//********************************************//
				
				
// =====================================================
//    Déclaration des bibliothèques pour le module RTC//
// =====================================================

#include <Wire.h>	//la bibliothèque qui gère la communication I2C avec le module et la carte 
#include <RTC.h>	//la bibliothèque du module RTC

// ============================================================
//    Déclaration des bibliothèques pour le module lecteur SD//
// ============================================================

#include <SPI.h> //la bibliothèque qui gère la communication SPI avec le module et la carte 
#include <SD.h> //la bibliothèque qui permet un tas de fonctions pour le module carte SD


//	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
//	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	//


				//****************************************//
				//-------Déclarations des variables-------//
				//****************************************//

// ==============================================================================
//    Déclaration des variables pour le capteur FSR et la lecture de sa tension//
// ==============================================================================

int PinAnal = A0; //le pin analogique de la carte qui sera utilisé pour lire la tension au point milieu 
float fsrVoltage; //la tension du capteur 
float fsrReading; //la valeur lue sur le pin analogique

// ==================================================================================
//    Déclaration des variables pour ajuster l'heure et la date avec le module RTC //
// ==================================================================================

 DS1307 RTC; // Définition de toutes les variable RTC (day, hours, sec...)


// ===========================================================
//    Déclaration des variables pour le module carte SD		//
// ===========================================================

const int pinCS = 10;  //broche de branchement de la carte au pin CS du module SD (D10 par défaut)
Sd2Card CarteSD; //instance carteSD => permet de la démarer
//SdVolume VolumeCarteSD; //Volume que peut contenir la carte SD --> pas utilisé ici
//uint32_t volumesize; // taille de la carte SD --> pas utilisé ici

#define PINCS 10 // le module sera donc branché sur le pin 10 (CS), 11 (MOSI), 12 (MISO), 13 (SCK)
#define filename "datafile.txt" //déf du nom de fichier de données sous format Excel (format 8.3) 
File file;  //initialisation de mon fichier pour les commandes relatives à la bibli SD.h


//	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	//
//	+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++	//


/*Remarque pour les print(F()) => le F sert à utiliser moins de place sur l'espace RAM car les donjnées qui
 *seront affichées, seront dans la mémoire flash et non plus dans la RAM : Astucieux pour certains projets!
 */


				//***********************************************//
				//-------Fonctions et programme principale-------//
				//***********************************************//
				
// ===================
//    VOID SETUP	//
// ===================

void setup() {

Serial.begin(9600); //démarage de l'instance avec le moniteur série d'Arduino
	
	
		//++++++++++++++++++++PARTIE POUR CARTE SD+++++++++++++++++++//
		//-----------------------------------------------------------//
		

	SD.begin(pinCS); //démarage de la communication avec le module carte SD sur le pin CS
	Serial.println(F("Lancement des tests de la carte SD avant le début du programme..."));
	Serial.println();

	
	//----------TEST 1 : PRÉSENCE D'UNE CARTE SD OU NON-------------//
 
 
	Serial.println(F("TEST 1 : PRÉSENCE D'UNE CARTE SD"));
	Serial.println(F("--------------------------------"));
	if (!CarteSD.init(SPI_HALF_SPEED, pinCS )) {  //test si la carte SD démarre et est reconnue en cas de mauvais branchement
	
		Serial.println(F("Échec lors du démarrage de la carte SD. Le problème vient peut-être de : "));
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
	
	
	
	//----------TEST 2 : ACCESIBILITÉ DE LA CARTE SD-------------//

	Serial.println(F("TEST 2 : ACCESIBILITÉ DE LA CARTE SD"));
	Serial.println(F("-------------------------------------"));
	
	/*Il est impératif de tester si on a accès à la carte si non
	* pourquoi continuer le code ?
	*/

	Serial.println(F("Initialisation de la carte SD..."));
	Serial.println(F("Vérification de l'accès à la carte SD..."));
	
	if(!SD.begin(PINCS)){   //condition si la carte SD n'a pas démarrée
    
		Serial.println(F("Échec de l'initialisation de la carte SD !"));
		while (1); //boucle infini (stop le programme à cette étape)
	}

	//si la carte SD a démarrée :
	Serial.println(F("Initialisation terminée avec succès !"));
	Serial.println();

	
	//----------TEST 3 : Suppression du fichier de données s'il existe déjà-------------//

	/* Je test ici si le fichier dans lequel je vais écrire existe ou non
	*  SI non le fichier n'existe pas et on continue le programme
	*  SI oui le fichier existe je vais le supprimer pour le remplacer par un nouveau par la suite
	*  Remarque  : il s'agit d'un test la suppression du fichier n'est pas obligatoire,
	*  il est même absurde dans un projet de supprimer constament sont fichier au risque 
	*  de perdre les données qu'il contient --> A vous de vérifier ce qu'il vous faut
	*/

	Serial.println(F("Vérification de l'existance du fichier : '"filename"'..."));
	Serial.println(F("----------------------------------------------------------"));
	
	if (!SD.exists(filename)){  //condition si le fichier n'existe pas
    
		Serial.print(F("Fichier '" filename "' inexistant."));
		Serial.println();
    }

	else {	//s'il existe...

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

	
		//++++++++++++++++++++PARTIE POUR FSR+++++++++++++++++++//
		//------------------------------------------------------//
  
	pinMode (PinAnal, INPUT); //déclaration du pin analogique comme entrée
	

		//++++++++++++++++++++PARTIE POUR LE MODULE RTC++++++++++++++++++++//
		//-----------------------------------------------------------------//
	
	RTC.begin();  //Démarage du RTC

/*partie à décommentée pour ajuster l'heure et la date du module et puis remettre en commentaire*/
	//RTC.setDateTime(__DATE__, __TIME__); 
  
	Serial.println("Is Clock Running... "); //Affichafe dans le terminal (moniteur série d'Arduino)
	if (RTC.isRunning())  //Fonction RTC.isRunning => vérification si le module est alimenté ou pas
	{

	//-- Si OUI --//
		Serial.println("Yes");
		RTC.setHourMode(CLOCK_H24);
		}
		
	else
	{
		//-- Si NON --//
		Serial.println("No"); //Afficha que le module est pas en train de tourner
		Serial.println("Setting Time");
		//RTC.setHourMode(CLOCK_H12); //option de l'affichage de l'heure sous format 12H
		RTC.setHourMode(CLOCK_H24); //option de l'affichage de l'heure sous format 24H => préféré par moi même
		RTC.setDateTime(__DATE__, __TIME__);  //Mise à jour de la date et l'heure selon celles du pc
		RTC.startClock(); //commencement de l'horloge
	}

	Serial.println();

}

// ================================================================
//    Void loop boucle infinie => execution du programme principale
// ================================================================


void loop() {
	
   
		//++++++++++++++++++++PARTIE POUR LE MODULE RTC++++++++++++++++++++//
		//-----------------------------------------------------------------//
  
  
//------ On affiche chaque valeur grâce à la commande RTC.get....() -------//
 
	Serial.println(F("la date et l'heure sont : "));
	Serial.print(RTC.getDay());
    Serial.print("-");
    Serial.print(RTC.getMonth());
    Serial.print("-");
    Serial.print(RTC.getYear());
    Serial.print(" ");
    Serial.print(RTC.getHours());
    Serial.print(":");
    Serial.print(RTC.getMinutes());
    Serial.print(":");
    Serial.print(RTC.getSeconds());
    Serial.print("");
    Serial.println(""); 
    Serial.println();
	
		//++++++++++++++++++++PARTIE POUR FSR+++++++++++++++++++//
		//------------------------------------------------------//
  
	/* lecture de la tension sur le pin analogique A0 */
	fsrReading = analogRead (PinAnal);
  
	/* on doit ensuite convertire la tension analogique en numérique pour le terminal Arduino */
	float fsrVoltage = fsrReading *(3.3 / 1023.0); // conversion analogique to numérique par produit croisé

  
	Serial.print(F("La tension est de : "));
	Serial.println(fsrVoltage);
	Serial.println();

	if (fsrVoltage < 0.1) {
		Serial.println(F("Aucune pression appliquée"));
    }
  
	else {
		Serial.println(F("Pression détectée"));
    }

	Serial.println();
	
	
		//++++++++++++++++++++PARTIE POUR CARTE SD+++++++++++++++++++//
		//-----------------------------------------------------------//
	
	file = SD.open(filename, FILE_WRITE);
	
	if (file){
		
		Serial.println(F("Écriture sur le fichier '"filename"' possible"));
		Serial.println ();

/* Série de if => condition d'ajout d'un 0 si la valeur est inférieur à 10 */
    if (RTC.getHours() < 10) {
      file.print(0);
      }
		file.print(RTC.getHours()); file.print(":");
    
    if (RTC.getMinutes() < 10) {
      file.print(0);
      }
		file.print(RTC.getMinutes()); file.print(":"); 

    if (RTC.getSeconds() < 10) {
      file.print(0);
      }  
    file.print(RTC.getSeconds()); 
    file.print("\t");
		file.print(fsrVoltage); file.println();
		
		file.close();
	}
	
	else {
		
		Serial.println(F("Écriture sur le fichier '"filename"' impossible"));
		while(1);
	}
	
	Serial.println();
	Serial.print("La tension est de ");
	delay (1000); //délai de 1s avant que la boucle recommence 
}
