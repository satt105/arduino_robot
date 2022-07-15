#include "Grove_I2C_Motor_Driver.h"

#define I2C_ADDRESS_Moteur 0x0f // addresse driver l298 par défauts
char message;

void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  Motor.begin(I2C_ADDRESS_Moteur);
  delay(1000);
  Serial.println("READY");
}

void loop()
{
  if (Serial1.available())
  {
    char message = Serial1.read();
    Serial.print("code bluetooth recu: ");
    Serial.println(message);
    if (message == '1') // on s'arrete
    {
      Serial.println("arret");
      stop_moteur(); // arret des moteur
    }
    else if (message == '2') // on avance
    {
      Serial.println("en marche");
      avance(); // mise en marche des 2 moteurs
    }
    else if (message == '3') // on recule
    {
      Serial.println("on recule");
      recule();
    }
    else if (message == 4)
    {
      Serial.println("tourne a gauche");
      gauche();
    }
    else if (message == 5)
    {
      Serial.println("tourne a droite");
      droit();
    }
  }
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
  Motor.speed(MOTOR1, 100);
  Motor.speed(MOTOR2, -100);
}
void droit()
{
  Motor.speed(MOTOR1, -100);
  Motor.speed(MOTOR2, 100);
}