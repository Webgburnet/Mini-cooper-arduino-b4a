// Bibliotheque //
#include <SoftwareSerial.h>
#include <Servo.h>

// Declaration variable //
#define commande_moteur_horaire 4 //Grove relay
#define commande_moteur_horaire2 6 //Grove relay
#define commande_moteur_antihoraire 5 //Grove relay
#define commande_moteur_antihoraire2 7 //Grove relay
#define RX 2 //Grove bluetooth //Broche A3
#define TX 3 // Grove bluetooth //Broche A4
#define servomoteur 9 // Grove bluetooth //Broche A4

SoftwareSerial mySerial(RX,TX);
Servo monServomoteur;


char bluetooth;
int commande_bluetooth;
int val_servo=45;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    pinMode(commande_moteur_horaire, OUTPUT);
    pinMode(commande_moteur_horaire2, OUTPUT);
    pinMode(commande_moteur_antihoraire, OUTPUT);
    pinMode(commande_moteur_antihoraire2, OUTPUT);

	monServomoteur.attach(servomoteur);	
}
void loop()
{
    // Ordre de marche bluetooth //
//    Serial.print("\t");
//    Serial.print("commande bluetooth :");
//    Serial.print(commande_bluetooth);
//    Serial.print("\t");

    if (mySerial.available()>0)
    {
      bluetooth = mySerial.read() ;
      if (bluetooth == 'Z') //avancer
      {
        commande_bluetooth = 1;
      }
      else if (bluetooth == 'S') // Reculer
      {
        commande_bluetooth = 2;
      }
      else if (bluetooth == 'Q') // Gauche
      {
        commande_bluetooth = 3;
      }
	  else if (bluetooth == 'D') // Droite
      {
        commande_bluetooth = 4;
      }
	  else if (bluetooth == 'A') // Avancer + Gauche
      {
        commande_bluetooth = 5;
      }
	  else if (bluetooth == 'E') // Avancer + Droite
      {
        commande_bluetooth = 6;
      }
	  else if (bluetooth == 'W') // Reculer + Gauche
      {
        commande_bluetooth = 7;
      }
	  else if (bluetooth == 'C') // Reculer + Droite
      {
        commande_bluetooth = 8;
      }
	  
	  else if (bluetooth == 'X') // STOP
      {
        commande_bluetooth = 0;
      }
    }
    
    // Commande moteur //
	if(commande_bluetooth==0) //Stop Moteur
	{
		digitalWrite(commande_moteur_horaire, LOW);
		digitalWrite(commande_moteur_horaire2, LOW);
		digitalWrite(commande_moteur_antihoraire, LOW);
		digitalWrite(commande_moteur_antihoraire2, LOW);
    val_servo=45;
	}
	if(commande_bluetooth==1 /*|| commande_bluetooth==5 || commande_bluetooth==6*/) //Avancer ou Avancer + Gauche ou Avancer + Gauche
	{
		digitalWrite(commande_moteur_horaire, HIGH);
		digitalWrite(commande_moteur_horaire2, HIGH);
		digitalWrite(commande_moteur_antihoraire, LOW);
		digitalWrite(commande_moteur_antihoraire2, LOW);
    val_servo=45;
	}
	if(commande_bluetooth==2 /*|| commande_bluetooth==7 || commande_bluetooth==8*/) //Reculer
	{
		digitalWrite(commande_moteur_horaire, LOW);
		digitalWrite(commande_moteur_horaire2, LOW);
		digitalWrite(commande_moteur_antihoraire, HIGH);
		digitalWrite(commande_moteur_antihoraire2, HIGH);
   val_servo=45;
	}
	if(commande_bluetooth==3) //A Gauche ou A droite
	{
		digitalWrite(commande_moteur_horaire, LOW);
		digitalWrite(commande_moteur_horaire2, LOW);
		digitalWrite(commande_moteur_antihoraire, LOW);
		digitalWrite(commande_moteur_antihoraire2, LOW);
    val_servo=90;
	}
 if(commande_bluetooth==4) //A Gauche ou A droite
 {
    digitalWrite(commande_moteur_horaire, LOW);
    digitalWrite(commande_moteur_horaire2, LOW);
    digitalWrite(commande_moteur_antihoraire, LOW);
    digitalWrite(commande_moteur_antihoraire2, LOW);
    val_servo=0;
  }

  if(commande_bluetooth==5)
    {
      digitalWrite(commande_moteur_horaire, HIGH);
    digitalWrite(commande_moteur_horaire2, HIGH);
    digitalWrite(commande_moteur_antihoraire, LOW);
    digitalWrite(commande_moteur_antihoraire2, LOW);
      if(val_servo<90)
        {
          val_servo+=5;
        }
    }
    if(commande_bluetooth==6)
    {
      digitalWrite(commande_moteur_horaire, HIGH);
    digitalWrite(commande_moteur_horaire2, HIGH);
    digitalWrite(commande_moteur_antihoraire, LOW);
    digitalWrite(commande_moteur_antihoraire2, LOW);
      if(val_servo>0)
        {
          val_servo-=5;
        }
    }
    if(commande_bluetooth==7)
    {
      digitalWrite(commande_moteur_horaire, LOW);
    digitalWrite(commande_moteur_horaire2, LOW);
    digitalWrite(commande_moteur_antihoraire, HIGH);
    digitalWrite(commande_moteur_antihoraire2, HIGH);
      if(val_servo>0)
        {
          val_servo-=5;
        }
    }
    if(commande_bluetooth==8)
    {
      digitalWrite(commande_moteur_horaire, LOW);
    digitalWrite(commande_moteur_horaire2, LOW);
    digitalWrite(commande_moteur_antihoraire, HIGH);
    digitalWrite(commande_moteur_antihoraire2, HIGH);
      if(val_servo<90)
        {
          val_servo+=5;
        }
    }
  monServomoteur.write(val_servo);
  //Serial.println(val_servo);
}
