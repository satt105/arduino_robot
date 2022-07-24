char message;                   // message recu par bluetooth
const byte contact_moteur = 23; // pin actionneur
const byte pinavantmoteurdroit = 22;
const byte pinarrieremoteurdroit = 23;
const byte pinavantmoteurgauche = 24;
const byte pinarrieremoteurgauche = 25;
bool etat_contact = false; // variable de l'état du contacteur

void setup()
{
  Serial.begin(9600);              // vitesse du moniteur série
  Serial1.begin(9600);             // vitesse du bluetooth
  pinMode(contact_moteur, OUTPUT); // configuration de la sortie du contacteur
  pinMode(pinarrieremoteurdroit, OUTPUT);
  pinMode(pinavantmoteurdroit, OUTPUT);
  pinMode(pinavantmoteurgauche, OUTPUT);
  pinMode(pinarrieremoteurgauche, OUTPUT);
  stop_moteur();
  digitalWrite(contact_moteur, LOW); // arret du contacteur si precedements actif
  delay(1000);                       // délais de préparation des composants
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
    case '1':
    { // on s'arrete
      Serial.println(F("arret"));
      stop_moteur(); // arret des moteur
      break;
    }
    case '2':
    {
      Serial.println(F("en marche"));
      avance(); // mise en marche des 2 moteurs
      break;
    }
    case '3':
    {
      Serial.println(F("on recule"));
      recule();
      break;
    }
    case '4':
    {
      Serial.println(F("tourne a gauche"));
      gauche();
      break;
    }
    case '5':
    {
      Serial.println(F("tourne a droite"));
      droit();
      break;
    }
    case '6':
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
      break;
    }
    }
  }
  message = 'n'; // sup du précédents message
}
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
