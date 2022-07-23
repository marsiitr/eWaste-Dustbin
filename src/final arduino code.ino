#include <Stepper.h>
#include <EEPROM.h>
#include <Arduino.h>
#include "HX711.h"
HX711 scale;
const int stepsPerRevolution = 200;  
Stepper myStepper1(stepsPerRevolution, 8, 9, 10, 11);
Stepper myStepper2(stepsPerRevolution, 4, 5, 6, 7);
int trigPin2 = 44;
int echoPin2 = 42;
long duration2;
//int sensorpin = 0;                 // analog pin used to connect the sharp sensor
//int bval = 0;                 // variable to store the values from sensor(initially zero)
int x=2;
int trigPin = 24;
int echoPin = 26;

const int LOADCELL_DOUT_PIN = 32;
const int LOADCELL_SCK_PIN = 34;
long duration;
 long arr[5];
 long arr2[5];
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

  
void setup() {
EEPROM.write(0,7);

myStepper1.setSpeed(10);
myStepper2.setSpeed(60);
pinMode(trigPin,OUTPUT); //set trigPin as output pin of Arduino
pinMode(echoPin,INPUT);  //set echoPin as output pin of Arduino


  Serial.begin(57600);
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);         
  scale.set_scale(1114.81);
  //scale.set_scale(-471.497);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0  
  
Serial.begin(9600);
 for(int i=0; i<5 ; ++i){
 digitalWrite(trigPin,LOW); //generate square wave at trigger pin
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 arr[i]=  {pulseIn(echoPin,HIGH)};//calculation of distance of obstacle
delay(500);}
duration = (arr[0]+arr[1]+arr[2]+arr[3]+arr[4])*(0.16666);

EEPROM.update(0,duration*0.034/2);
Serial.println(EEPROM.read(0));
 delay(500);

}




void loop(){ 
//int bval = analogRead(sensorpin);// reads the value of the sharp sensor
// Serial.print(" ir ");
// Serial.println(bval);            // prints the value of the sensor to the serial monitor
// delay(400); 

 for(int i=0; i<5 ; ++i){
 digitalWrite(trigPin2,LOW); //generate square wave at trigger pin
 delayMicroseconds(2);
 digitalWrite(trigPin2,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin2,LOW);
 arr2[i]=  {pulseIn(echoPin2,HIGH)};//calculation of distance of obstacle
delay(500);}
duration2 = (arr2[0]+arr2[1]+arr2[2]+arr2[3]+arr2[4])*(0.16666);
long distance2 = duration2*0.034/2;
Serial.print("person distance ");

Serial.println(distance2);
if(distance2<150){

 

  Serial.print("\t| weight:\t");
Serial.println(scale.get_units(10));
if((scale.get_units(10))!=0){

   
if(EEPROM.read(0)<20)
{Serial.println("insufficient space"); delay(1000);}
 
else{
    
//rotation over the pit of both panels together//
  switch(3){
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
  delay(2000);

  
//steppermotor object fall motion// 
  myStepper1.step(40);
  delay(1500);
  myStepper1.step(-40);
  delay(2000);

 //ultra sonic//
 long duration;

 for(int i=0; i<5 ; ++i){
 digitalWrite(trigPin,LOW); //generate square wave at trigger pin
 delayMicroseconds(2);
 digitalWrite(trigPin,HIGH);
 delayMicroseconds(10);
 digitalWrite(trigPin,LOW);
 arr[i]= {pulseIn(echoPin,HIGH)};//calculation of distance of obstacle
delay(500);}
duration = (arr[0]+arr[1]+arr[2]+arr[3]+arr[4])*(0.16666);

EEPROM.update(0,duration*0.034/2);
Serial.print(EEPROM.read(0));
Serial.println(" uv reading");
delay(500);

 //backrotation over the pit of both panels together//
 switch(3){
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
  
  delay(2000);
}}}}
