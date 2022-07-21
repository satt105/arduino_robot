#include "Grove_I2C_Motor_Driver.h"

#define I2C_ADDRESS_Moteur 0x0f // addresse driver l298 par défauts
char message;                   // message recu par bluetooth
const byte contact_moteur = 23; // pin actionneur
bool etat_contact = false;      // variable de l'état du contacteur
// moteur 1 = gauche
// moteur 2 = droite
void setup()
{
  Serial.begin(9600);                // vitesse du moniteur série
  Serial1.begin(9600);               // vitesse du bluetooth
  Motor.begin(I2C_ADDRESS_Moteur);   // configuration adresse
  pinMode(contact_moteur, OUTPUT);   // configuration de la sortie du contacteur
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
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, 100);
}
void stop_moteur()
{
  Motor.stop(MOTOR1);
  Motor.stop(MOTOR2);
}
void recule()
{
  Motor.speed(MOTOR1, -100);
  Motor.speed(MOTOR2, -100);
}
void gauche()
{
  Motor.speed(MOTOR1, -100);
  Motor.speed(MOTOR2, 100);
}
void droit()
{
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, -100);
}
