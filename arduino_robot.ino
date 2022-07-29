// les libs
#include "bmm150.h"
#include "bmm150_defs.h"

// création objets
BMM150 bmm = BMM150();

// les variables
char message;                                 // message recu par bluetooth sur 1 octet
const unsigned int TRANSFERT_INTERVAL = 2000; // délais de transfert des données bluetooth
unsigned long previousMillis = 0;             // précédente valeur retournée par la fonction
const byte pinavantmoteurdroit = 24;          // pin actionneur marche avant moteur droit
const byte pinarrieremoteurdroit = 25;        // pin actionneur marche arriere moteur droit
const byte pinavantmoteurgauche = 22;         // pin actionneur marche avant moteur gauche
const byte pinarrieremoteurgauche = 23;       // pin actionneur marche arriere moteur gauche
const byte margemin = 0;                      // la marge minimale du compas
const byte margemax = 5;                      // la marge maximale d'erreur du compas
float angle_vehicule;                         // angle renvoyé par le compas
bool Fonction_automatique = true;             // check des outils pour l'auto_mode
byte contact_moteur = 2;                      // pin actionneur
bool etat_contact = false;                    // variable de l'état du contacteur
String code = "|";                            // code de séparation des données
String messageretour;                         // déclaration du message de retour vers le téléphone
String fakecode = "12";                       // déclaration fausse donnée de debut
String message_contact;                       // string variable de conversion
// le code
void setup()
{
  Serial.begin(9600);  // vitesse du moniteur série
  Serial1.begin(9600); // vitesse du bluetooth
  pinMode(pinarrieremoteurdroit, OUTPUT);
  pinMode(pinavantmoteurdroit, OUTPUT);
  pinMode(pinavantmoteurgauche, OUTPUT);
  pinMode(pinarrieremoteurgauche, OUTPUT);
  pinMode(contact_moteur, OUTPUT);   // configuration de la sortie du contacteur
  digitalWrite(contact_moteur, LOW); // arret du contacteur si precedements actif
  stop_moteur();
  if (bmm.initialize() == BMM150_E_ID_NOT_CONFORM) // vérification des fonction automatique
  {
    Serial.println(F("Defaut compas!"));
    Serial.println(F("Blocage des fonctions automatique"));
    Fonction_automatique = false;
  }
  else
  {
    Serial.println(F("fonction automatique disponible"));
    Fonction_automatique = true;
  }
  delay(1000); // délais de préparation des composants
  Serial.println("READY");
}

void loop()
{
  if (Serial1.available())
  {
    message = Serial1.read();
    Serial.print(F("code bluetooth recu: "));
    Serial.println(message);
    switch (message) // mise en switch (meilleurs prise en charge)
    {
    case 'S':
    { // on s'arrete
      Serial.println(F("arret"));
      stop_moteur(); // arret des moteur
      break;
    }
    case 'A':
    {
      Serial.println(F("en marche"));
      avance(); // mise en marche des 2 moteurs
      break;
    }
    case 'R':
    {
      Serial.println(F("on recule"));
      recule();
      break;
    }
    case 'G':
    {
      Serial.println(F("tourne a gauche"));
      gauche();
      break;
    }
    case 'D':
    {
      Serial.println(F("tourne a droite"));
      droit();
      break;
    }
    case 'I':
    {
      if (Fonction_automatique == true)
      {
        Serial.println(F("Mode demi-tour droit"));
        demi_tour_droit();
      }
      break;
    }
    case 'C':
    {
      if (etat_contact == false)
      {
        Serial.println(F("allumage contacteur moteur"));
        digitalWrite(contact_moteur, HIGH);
        etat_contact = true;
        Serial1.print(F("allumage moteur"));
      }
      else if (etat_contact == true)
      {
        Serial.println(F("extinction contacteur moteur"));
        digitalWrite(contact_moteur, LOW);
        etat_contact = false;
        Serial1.print(F("extinction contacteur moteur"));
      }
    }
    }
  }
  message = 'n'; // sup du précédents message
  unsigned long currentMillis = millis();
  // Si TRANSFERT_INTERVAL ou plus millisecondes se sont écoulés
  if (currentMillis - previousMillis >= TRANSFERT_INTERVAL)
  {
    // Garde en mémoire la valeur actuelle de millis()
    previousMillis = currentMillis;
    if (etat_contact == true)
    {
      message_contact = "1";
    }
    else
    {
      message_contact = "0";
    }
    messageretour = message_contact + code + fakecode;
    Serial.print("data: ");
    Serial.println(messageretour);
    Serial1.print(messageretour);
  }
}
// les fonctions
void avance()
{
  digitalWrite(pinarrieremoteurdroit, LOW);
  digitalWrite(pinarrieremoteurgauche, LOW);
  digitalWrite(pinavantmoteurdroit, HIGH);
  digitalWrite(pinavantmoteurgauche, HIGH);
}
void stop_moteur()
{
  digitalWrite(pinarrieremoteurdroit, LOW);
  digitalWrite(pinavantmoteurdroit, LOW);
  digitalWrite(pinavantmoteurgauche, LOW);
  digitalWrite(pinarrieremoteurgauche, LOW);
}
void recule()
{
  digitalWrite(pinavantmoteurdroit, LOW);
  digitalWrite(pinavantmoteurgauche, LOW);
  digitalWrite(pinarrieremoteurgauche, HIGH);
  digitalWrite(pinarrieremoteurdroit, HIGH);
}
void gauche()
{
  digitalWrite(pinarrieremoteurdroit, LOW);
  digitalWrite(pinavantmoteurgauche, LOW);
  digitalWrite(pinavantmoteurdroit, HIGH);
  digitalWrite(pinarrieremoteurgauche, HIGH);
}
void droit()
{
  digitalWrite(pinavantmoteurdroit, LOW);
  digitalWrite(pinarrieremoteurgauche, LOW);
  digitalWrite(pinarrieremoteurdroit, HIGH);
  digitalWrite(pinavantmoteurgauche, HIGH);
}
void allumage_contacteur()
{
  digitalWrite(contact_moteur, HIGH);
  contact_moteur = true;
}
void demi_tour_droit()
{
}
