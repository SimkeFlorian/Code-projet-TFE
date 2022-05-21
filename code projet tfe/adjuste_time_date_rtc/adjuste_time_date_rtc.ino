// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //
//      Afficher la date et l'heure avec le module RTC                //
//      Sans interruption lorsqu'il est plus alimenté                 //
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ //

//=========================================================//
//--------------- On inclu les bibliothèques --------------//
//=========================================================//

#include <Wire.h>
#include <RTC.h>


static DS1307 RTC; // Définition de la variable RTC comme variable static 

/* Les variables static sont des variables dont leur valeurs
 *  persisteront au-delà de l'appel de fonction, elles ne bougent pas
 */


//==============================================================//
//--------------------- CODE PRINCIPALE ------------------------//
//==============================================================//


//****************************************//
//       Fonction void setup              //
//****************************************//

void setup()
{
	Serial.begin(9600); //Débit d'nvoie des données à 9600 Bauds
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
}

//****************************************//
//       Fonction void loop               //
//****************************************//

void loop()
{

 //------ On affiche chaque valeur grâce à la commande RTC.get....() -------//
 
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
    delay (1000); //délai de 1s avant que la boucle recommence
}
