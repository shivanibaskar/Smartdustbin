// This uses Serial Monitor to display Range Finder distance readings

// Include NewPing Library
#include "NewPing.h"
#include <Servo.h>//servo library
Servo dustbinMotor;
int count=0;
long duration, dist, average;
long aver[3];  //array for average
int led=13;


// setup trigger and echo pin of ultrasonic sensor
#define TRIGGER_PIN 9
#define ECHO_PIN 10
#define dustbinMotorPin 7

// Maximum distance we want to ping for (in centimeters).
#define MAX_DISTANCE 200  

// setup of pins and maximum distance.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
float distance;

void setup() 
{
  Serial.begin(9600);
  dustbinMotor.attach(dustbinMotorPin);
  dustbinMotor.write(0);         //close cap on power on
  delay(100);
  dustbinMotor.detach();
  pinMode(led,OUTPUT); 
}

void loop() 
{
  // Send ping, get distance in cm 
  // Send results to Serial Monitor
  Serial.print("Distance = ");
   for (int i=0;i<=2;i++)
   {
     distance = sonar.ping_cm();            
     aver[i]=distance;
     delay(10);              //delay between measurements
    }
  dist=(aver[0]+aver[1]+aver[2])/3;    
  if (dist >= 40 || dist <= 2) 
  {
    Serial.println("Out of range");
  }
  else 
  {
    count=count+1;
    Serial.print(distance);
    Serial.println(" cm");
    dustbinMotor.attach(dustbinMotorPin);
    delay(1);
    dustbinMotor.write(0);  
    delay(3000);       
    dustbinMotor.write(150);    
    delay(1000);
    dustbinMotor.detach(); 
  }
  if(count>3)//blink if dustbin is full 
  {
    digitalWrite(led,HIGH);
    delay(100);
    digitalWrite(led,LOW);
  }
}
