// Bibliotheque //
#include <SoftwareSerial.h>
#include <Servo.h>

// Declaration variable //
#define commande_moteur_horaire 4 //Grove relay
#define commande_moteur_horaire2 6 //Grove relay
#define commande_moteur_antihoraire 5 //Grove relay
#define commande_moteur_antihoraire2 7 //Grove relay
#define RX 2 //Grove bluetooth 
#define TX 3 // Grove bluetooth
#define servomoteur 8
#define cligno_gauche 15 //A1
#define cligno_droite 16 //A2
#define lampe 14 //A0

SoftwareSerial mySerial(RX,TX);
Servo monServomoteur;


char bluetooth;
int commande_bluetooth;
int val_servo=45;
boolean etat_lampe=0;
boolean etat_cligno_gauche=0;
boolean etat_cligno_droite=0;
boolean etat_warning=0;
boolean etat_cligno=0;
unsigned long timer0=0;

void setup()
{
    Serial.begin(9600);
    mySerial.begin(9600);

    pinMode(commande_moteur_horaire, OUTPUT);
    pinMode(commande_moteur_horaire2, OUTPUT);
    pinMode(commande_moteur_antihoraire, OUTPUT);
    pinMode(commande_moteur_antihoraire2, OUTPUT);

    pinMode(lampe, OUTPUT);
    pinMode(cligno_gauche, OUTPUT);
    pinMode(cligno_droite, OUTPUT);

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
//      Serial.println(bluetooth);
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
      else if (bluetooth == 'R') // Lampe
      {
        etat_lampe= !etat_lampe;
      }
      else if (bluetooth == 'F') // Warning
      {
       etat_warning= !etat_warning;
       etat_cligno_gauche=0;
       etat_cligno_droite=0;
      }
      else if (bluetooth == 'G') // Clignotant Gauche
      {
        etat_cligno_gauche= !etat_cligno_gauche;
        etat_cligno_droite=0;
        etat_warning=0;
      }
      else if (bluetooth == 'T') // Clignotant Droite
      {
        etat_cligno_droite = !etat_cligno_droite;
        etat_cligno_gauche=0;
        etat_warning=0;
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

    //Commande lampe
    if(etat_lampe==1)
    {
      digitalWrite(lampe, HIGH);
    }
   else
    {
      digitalWrite(lampe, LOW);
    }

    //Commande cligno
   if(etat_warning==1)
    {
      if (millis() - timer0 >=1000)
      {
        etat_cligno=!etat_cligno;
        digitalWrite(cligno_gauche, etat_cligno);
        digitalWrite(cligno_droite, etat_cligno);
        timer0=millis();
      }
    }
    else if(etat_cligno_gauche==1)
    {
      if (millis() - timer0 >=1000)
      {
        etat_cligno=!etat_cligno;
        digitalWrite(cligno_gauche, etat_cligno);
        timer0=millis();
      }
      digitalWrite(cligno_droite, LOW);
    }
    else if(etat_cligno_droite==1)
    {
      if (millis() - timer0 >=1000)
      {
        etat_cligno=!etat_cligno;
        digitalWrite(cligno_droite, etat_cligno);
        timer0=millis();
      }
      digitalWrite(cligno_gauche, LOW);
    }
   else
    {
      digitalWrite(cligno_droite, LOW);
      digitalWrite(cligno_gauche, LOW);
    }
    
  monServomoteur.write(val_servo);
  //Serial.println(val_servo);
}
