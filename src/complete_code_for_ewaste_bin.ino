#include <Stepper.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "HX711.h"
HX711 scale;
const int stepsPerRevolution = 200;  
Stepper myStepper1(stepsPerRevolution, 10, 11, 12, 13);
Stepper myStepper2(stepsPerRevolution, 4, 5, 6, 7);
int trigPin2 = 3;
int echoPin2 = 2;
long duration2;
                 
int x=2;
int trigPin = 24;
int echoPin = 26;

const int LOADCELL_DOUT_PIN = 32;
const int LOADCELL_SCK_PIN = 34;
long duration;

void rot(int a){
  for(int i=0;i<a;i++){
   myStepper1.step(1);
   myStepper2.step(-1);
  }}


  void brot(int b){
  for(int i=0;i>b;i--){
   myStepper1.step(-1);
   myStepper2.step(1);
  }}

long uss(){ 
digitalWrite(trigPin2,LOW); //generate square wave at trigger pin
 delayMicroseconds(2);
 digitalWrite(trigPin2,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2,LOW);
delay(100);

 return (pulseIn(echoPin2,HIGH))*0.034/2;
  }

  
void setup() {


myStepper1.setSpeed(10);
myStepper2.setSpeed(60);
pinMode(trigPin,OUTPUT); //set trigPin as output pin of Arduino
pinMode(echoPin,INPUT);  //set echoPin as output pin of Arduino


  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);         
  scale.set_scale(-1214.81);
  scale.tare();              
Serial.begin(9600);

 for(int i=0; i<5 ; ++i){
EEPROM.write(i,uss());
Serial.print("lvl of pit no. ");
Serial.println(i+1);
Serial.println(EEPROM.read(i));
delay(10);
  uss();
  rot(40);
  delay(1000);
 
  } 
  
delay(900);
  brot(-200);
}

 


void loop(){ 

long distance2 = uss();
Serial.print("person distance ");

Serial.println(distance2);
if(distance2<150){
 Serial.println("\t| put weight:\t");
  
if((scale.get_units(10))>5){
  
Serial.print("\t| weight:\t");
Serial.println(scale.get_units(10));

   
if(EEPROM.read(x)<20)
{Serial.println("insufficient space"); delay(1000);}
 
else{
    
//rotation over the pit of both panels together//
  switch(x){
    case 1: rot(0);
            break;
    case 2: rot(40);
            break;
    case 3: rot(80);
            break;
    case 4: brot(-80);
            break;
    case 5: brot(-40);
            break;
  }
  delay(1000);

  
//steppermotor object fall motion// 
  myStepper1.step(40);
  delay(500);
  myStepper1.step(-40);
  delay(500);

 //ultra sonic//

EEPROM.update(x,uss);
Serial.print(" pit lvl reading ");
Serial.println(EEPROM.read(x));

delay(300);

 //backrotation over the pit of both panels together//
 switch(x){
    case 1: brot(0);
            break;
    case 2: brot(-40);
            break;
    case 3: brot(-80);
            break;
    case 4: rot(80);
            break;
    case 5: rot(40);
            break;
  } 
  
  delay(1000);
}}}}
