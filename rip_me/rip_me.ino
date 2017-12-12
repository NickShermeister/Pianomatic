//Include needed libraries
#include <Servo.h>
//#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"


//Define variables
//Every servo will handle 6 IR sensors/servos
//ONLY HARDCODED VARIABLES; make sure they correleate 1:1. If they don't, everything breaks.

//Multiplexer constants
const int selectPins[3] = {11, 12, 13};
const int zInput = A0;

//Other pin constants
int sensorPins[] = {A1, A2, A3, A4};
int sensorBounds[] = {300, 300, 300, 200};
int multiplexerSensorBounds[] = {500, 350, 500, 500, 500, 300, 300, 300};
//int solenoidPins[] =  {2, A0, 3, A0, 4, 5, A0, 6, A0, 7, A0, 8};
int solenoidPins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, A5};
//w b w b w w b w b w b w 
int tempServo = 0;
const int arrayLength = 12;     //Number of notes in an octave

//TODO: DIGITAL INTERRUPT (haven't discussed as group yet)

//Normal variables
int sensorValues[4];  //Normal sensor values
int sensorValuesMultiplexer[8]; //Sensor values in multiplexer
int ByteReceived = -1;    // variable that holds what bytes are received from serial

//Setup Function
void setup() {  
  //mount Servos and set to 0 degrees
  for(int i = 0; i < arrayLength; i++){
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], LOW);
  }

  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], LOW);
  }

 pinMode(zInput, INPUT);
 for(int i = 0; i < 4; i ++)
 {
  pinMode(sensorPins[i], INPUT);
 }

 
}


void loop() {
  
    player();
  delay(25);  //delay so as not to have the arduino run at its full speed (there is no point)
}


//Main playing function
void player() {
  
  //First deal with multiplexer Serial.println(analogRead(zInput));
  for(int i = 0; i < 8; i++){
    selectMultiplexerPin(i);
    sensorValuesMultiplexer[i] = analogRead(zInput);

    
    //Change state to low/high
    if(sensorValuesMultiplexer[i] > multiplexerSensorBounds[i]){
      digitalWrite(solenoidPins[i], HIGH);
    }
    else {
      digitalWrite(solenoidPins[i], LOW);
    }
  }

  //Then get values for the other 4
  for (int i = 0; i < 4; i++){
    sensorValues[i]=analogRead(sensorPins[i]);
    if(sensorValues[i] > sensorBounds[i]){
      digitalWrite(solenoidPins[i+8], HIGH);
    }
    else {
      digitalWrite(solenoidPins[i+8], LOW);
    }
  }
}


void selectMultiplexerPin(int pin) {
  if (pin > 7) return; // Exit if pin is out of scope
  
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}


