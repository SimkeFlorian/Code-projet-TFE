/*
 * Ce code est utilisé pour envoyer des données d'un esp à un autre esp
 * il utilise pour cela la communication esp_now
 * Dans ce code ce sont des données d'un capteur FSR qui seront envoyées vers un autre esp
 * 
 * Cette partie de code-ci est utilisé pour l'appareil expéditeur de données
*/

/*
  =====================================
           BIBLIOTHÈQUES
  =====================================
*/

#include <ESP8266WiFi.h> // bibliothèque pour utiliser le WiFi avec un esp
#include <espnow.h> // bibliothèque pour la communication esp_now


/*
  =====================================
             PARTIE ESP_NOW
  =====================================
*/

// Déf de l'adresse Mac de l'appareil qui recevra les infos
uint8_t broadcastAddress[] = {0x44,0x17,0x93,0x10,0x75,0x71};

// Création d'une structure pour l'envoie des données
// Devra être identique à celle du receveur
typedef struct struct_message { //je définis le type de variable que sont les données de mon capteur
  int datasensor;
} struct_message;

// Création d'une struct_message pour appeler myData avec les données définies dans le typedef au dessus
struct_message myData;


// Définition de la fonction Callback (fct de rappel) pour l'envoie des données
void OnDataSent(uint8_t *mac_addr, uint8_t sendStatus) {
  Serial.print("Etat du dernier packet envoyé: ");
  // Vérification de l'état de l'envoie des données si réussi ou non
  if (sendStatus == 0){
    Serial.println("Send success");
  }
  else{
    Serial.println("Send fail");
  }
}


// ==============================================================================
//    Déclaration des variables pour le capteur FSR et la lecture de sa tension//
// ==============================================================================

int PinAnal = A0; //le pin analogique de la carte qui sera utilisé pour lire la tension au point milieu 
float fsrVoltage; //la tension du capteur 
float fsrReading; //la valeur lue sur le pin analogique
int Datavoltage; //La variable pour stoker la valeur du capteur en mV => afin d'avoir un int et plus un float


/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID SETUP / FCT PRINCIPAL
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
============================================================================================*/

 
void setup() {
  // Initialisation avec le moniteur série d'Arduino
  Serial.begin(115200);
 
  // Configuration de l'appareil en tant que station WiFi
  WiFi.mode(WIFI_STA);

  // Initialisation de la communication ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erreur lor de l'initialisation de la communication ESP-NOW");
    return;
  }

  // Une fois initialisé:
  // on s'enregistre pour recevoir les infos sur l'envoie des packets
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER); // déf du rôle de l'esp8266
  esp_now_register_send_cb(OnDataSent); //enregistrement pour l'état des packet
  
  // enregistrement à un autre appareil esp_now
  esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 1, NULL, 0);


/*
  =========================================
             PARTIE CAPTEUR FSR
  =========================================
*/
  
  pinMode (PinAnal, INPUT); //déclaration du pin analogique comme entrée

}


/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID LOOP / EXECUTION DU PROGRAMME
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
==============================================================================================*/

 
void loop() {

 /*
  =========================================
             PARTIE CAPTEUR FSR
  =========================================
*/ 
  
  // lecture de la tension sur le pin analogique A0 
  fsrReading = analogRead (PinAnal);
  
  // on doit ensuite convertire la tension analogique en numérique pour le terminal Arduino 
  fsrVoltage = fsrReading *(3.3 / 1023.0); // conversion analogique to numérique par produit croisé
  Datavoltage = fsrVoltage * 1000;

  // Configuration de la valeur à envoyer en lui donnant la valeur de mon capteur FSR contenue dans la variable fsrVoltage    
  myData.datasensor = Datavoltage;

  // Envoie du message comme suite
  esp_now_send(broadcastAddress, (uint8_t *) &myData, sizeof(myData));

  Serial.println(myData.datasensor);

  delay(500); //délai avant recommencer la boucle 1s
  
}
