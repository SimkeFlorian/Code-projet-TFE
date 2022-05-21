                 //----------------------------------//       
                          // FSR testing //
                 //----------------------------------//

// ==========================================================================
//    Déclaration des variables pour tester la led sur la broche PWM  //
// ==========================================================================

int PinAnal = A0; //le pin analogique de l'esp qui sera utilisé
float fsrVoltage; //la tension du capteur 
float fsrReading; //la valeur lue sur le pin analogique



// ===============================================
//      Programme principale Void setup 
// ===============================================

void setup() {

  Serial.begin(9600);
  pinMode (PinAnal, INPUT); //déclaration du pin analogique comme entrée

}

// ===========================================================
//    Void loop boucle infinie => execution du programme 
// ===========================================================

void loop() {
  
  /* lecture de la tension sur le pin analogique A0 */
  fsrReading = analogRead (PinAnal);
  
  /* on doit ensuite convertire la tension analogique en numérique pour le terminal Arduino */
  float fsrVoltage = fsrReading *(3.3 / 1023.0); // conversion analogique to numérique par produit croisé

  
  Serial.print("La tension est de : ");
  Serial.println(fsrVoltage);
  Serial.println ("-----------------------------------------------------"); 

  if (fsrVoltage < 0.1) {
    Serial.println("Aucune pression appliquée");
    }
  else {
     Serial.println("Pression détectée");
    }
    
  Serial.println("----------------------------------------------------------");
  delay (500);

}
