/*
 * Ce code est utilisé pour envoyer des données d'un esp à un autre esp
 * il utilise pour cela la communication esp_now
 * Dans ce code ce sont des données d'un capteur FSR qui seront reçues par un esp
 * 
 * Cette partie de code-ci est utilisé pour l'appareil receveur de données
*/

int variable = 280;

/*
  =====================================
           BIBLIOTHÈQUES
  =====================================
*/

#include <ESP8266WiFi.h> //bibliothèque pour le WiFI avec l'esp8266
#include <espnow.h> //bibliothèque pour utiliser la communication ESP_NOW |e| esp

/*
  =====================================
             PARTIE ESP_NOW
  =====================================
*/

// Création de la structure d'envoie des données du capteur
// /!\ Doit correspondre avec celle de l'expéditeur 
typedef struct struct_message {
  int datasensor;
} struct_message;

// Création d'une struct_message pour appeler myData
struct_message myData;

// La fonction Callback qui sera exécutée lors de la récéption des données
void OnDataRecv(uint8_t * mac, uint8_t *incomingData, uint8_t len) {
  memcpy(&myData, incomingData, sizeof(myData));
  // On affiche les données du capteur qui sont reçues dans la variable datasensor
  Serial.print(F("Bytes received: "));
  Serial.println(len);
  Serial.print(F("La tension est de : "));
  Serial.println(myData.datasensor);  //appel de la variable datasensor crée dans la fct myData (typedef)
  Serial.println();

}


/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID SETUP / FCT PRINCIPAL
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
============================================================================================*/
 
void setup() {
  // Initialisation avec le moniteur série d'Arduino
  Serial.begin(115200);
  // Initialisation du port série 1 de la carte ESP
  Serial1.begin(115200);
  
  // Configuration de l'appareil en tant que station WiFi
  WiFi.mode(WIFI_STA);

  // Initialisation de la communication ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Erreur lors de l'initialisation de la communication ESP_NOW");
    return;
  }
  
  // Une fois la communication établie:
  // enregistrement pour recevoir les infos des envoies des packets
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE); // déf du rôle de l'esp8266
  esp_now_register_recv_cb(OnDataRecv); //enregistrement à la fct de rappel lors de la récéption des données
}

/*============================================================================================
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  
                                  VOID LOOP / EXECUTION DU PROGRAMME
                                  
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
==============================================================================================*/

void loop() {

    // On récupère la valeur de la tension en mV dans la variable 'variable'
  variable = myData.datasensor;
 
  Serial.print (F("Le tension est bien de : "));
  Serial.println(variable);
  // On écrit sur le port série la valeur du capteur 
  // Celle-ci est sur max 4 octets donc on l'envoie octet par octet
  Serial1.write(variable & 0xFF); // octet de poids faible
  Serial1.write(( variable >>8) & 0xFF); 
  Serial1.write(( variable >>16) & 0xFF);
  Serial1.write(( variable >>24) & 0xFF); // octet de poids fort

  delay(500);
}
