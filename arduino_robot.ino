// les libs
#include "bmm150.h"
#include "bmm150_defs.h"

// création objets
BMM150 bmm = BMM150();

// les variables
char message;                           // message recu par bluetooth sur 1 octet
const byte pinavantmoteurdroit = 22;    // pin actionneur marche avant moteur droit
const byte pinarrieremoteurdroit = 23;  // pin actionneur marche arriere moteur droit
const byte pinavantmoteurgauche = 24;   // pin actionneur marche avant moteur gauche
const byte pinarrieremoteurgauche = 25; // pin actionneur marche arriere moteur gauche
const byte margemin = 0;                // la marge minimale du compas
const byte margemax = 5;                // la marge maximale d'erreur du compas
float angle_vehicule;                   // angle renvoyé par le compas
bool Fonction_automatique = true;       // check des outils pour l'auto_mode

// le code
void setup()
{
  Serial.begin(9600);              // vitesse du moniteur série
  Serial1.begin(9600);             // vitesse du bluetooth
  pinMode(pinarrieremoteurdroit, OUTPUT);
  pinMode(pinavantmoteurdroit, OUTPUT);
  pinMode(pinavantmoteurgauche, OUTPUT);
  pinMode(pinarrieremoteurgauche, OUTPUT);
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
    char message = Serial1.read();
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
    }
  }
  message = 'n'; // sup du précédents message
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
void demi_tour_droit()
{
}