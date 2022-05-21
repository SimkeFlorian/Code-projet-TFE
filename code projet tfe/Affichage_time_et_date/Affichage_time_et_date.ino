         //*************************************************************//
        //      Affichage date et heure sur le terminal Arduino        //
        //*************************************************************//

        
// ===================================================
//    Inclusion de nos bibliothèque
// ==================================================

#include <Wire.h>   // bibliothèque pour la communication 
#include <DS3231.h> // bibliothèque pour le module RTC => contient également son adresse pour la communication I2C


// ===================================================
//        Déclaration des variabless
// ===================================================

DS3231 clock;
RTCDateTime dt;
RTC_DS1307 rtc;


// ===============================================
//      Programme principale Void setup 
// ===============================================

void setup()
{
  Serial.begin(9600);

  Serial.println("Initialisation de l'horloge DS3231...");
  // Initialisation de l'horloge DS3231
  clock.begin();

  
  // Manuellmeent la disposition est comme suite (Year, Month, Day, Hours, Min, Sec
  // clock.setDateTime(2022, 2, 13, 13, 35, 00);
  
  // On donne le croquis de l'envoie des données à l'Arduino _DATE_,__TIME__
  clock.setDateTime(__DATE__,__TIME__);  
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//
//+ Le code suivant peut être également utilisé afin de set up la date et l'heure +//
//+  clock.setDateTime(2022, 02, 19, 14 , 40, 00);     +//
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++//

}

// ===========================================================
//    Void loop boucle infinie => execution du programme 
// ===========================================================

void loop()
{
  dt = clock.getDateTime(); /* récupération de la date et l'heure dans dt*/

  Serial.print("Ligne de données: ");
  Serial.print(dt.year);   Serial.print("-");
  Serial.print(dt.month);  Serial.print("-");
  Serial.print(dt.day);    Serial.print(" ");
  Serial.print(dt.hour);   Serial.print(":");
  Serial.print(dt.minute); Serial.print(":");
  Serial.print(dt.second); Serial.println("");

  delay(1000);
}
