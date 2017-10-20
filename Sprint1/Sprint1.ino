//Include needed libraries
#include <Servo.h>
//#include <Wire.h>
//#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"


//Define variables

//ONLY HARDCODED VARIABLES; make sure they correleate 1:1. If they don't, everything breaks.
int sensorPins[] = {A0, A1, A2, A3, A4};
int servoPins[] =  {8,  9,  10, 11, 12};
//TODO: DIGITAL INTERRUPT (haven't discussed as group yet)

//Normal variables
const int arrayLength = int(sizeof(sensorPins)/sizeof(int));
int sensorValues[arrayLength];  //this way we only have to define where the sensors are
Servo servos[arrayLength];
int servoLocations[arrayLength];


int ByteReceived = -1;    // variable that holds what bytes are received from serial
int bound = 500;          //The boundary that constitutes being on something; arbitrary needs to be determined
int newBound = 0;        //The new bound before max/min are taken into account
int finalDegree = 90;
int minDegree = 0;

// Create the motor shield object with the default I2C address; not needed for now
//Adafruit_MotorShield AFMS = Adafruit_MotorShield();

// Set up motors (later)
//Adafruit_DCMotor *leftMotor = AFMS.getMotor(2);
//Adafruit_DCMotor *rightMotor = AFMS.getMotor(1);


//Setup Function
void setup() {
  Serial.begin(9600); //Begin the serial so we can read from it/print to it
//  AFMS.begin();  // create with the default frequency 1.6KHz
  printHelp();   // print the key
  printOutput(); // print what is printed in each of the four columns
  
  //mount Servos and set to 0 degrees
  for(int i = 0; i < arrayLength; i++){
    servos[i].attach(servoPins[i]);
    servos[i].write(minDegree);
    servoLocations[i] = minDegree;
  }
  
}


void loop() {
  
  //Wait, nonverbose output
  if (ByteReceived == '0') {
    
  }

  //Wait, verbose output
  else if (ByteReceived == '1') //Stay still.
  {
    printSensorInputs();
  }

  //Play, nonverbose output
  else if (ByteReceived == '2')
  {
    player();
  }

  //Play, verbose output
  else if (ByteReceived == '3')
  {
    player();
    printSensorInputs();
  }

  //If there is something to be read from the serial port:
  if (Serial.available() > 0)
  {
    //Read in the byte and assign it to ByteReceived
    ByteReceived = Serial.read();
    Serial.println();    // End the line

    
    //print the information of what the different inputs do.
    if (ByteReceived == '4') {
      printHelp();
    }
    
    //print what each of the outputs are when running on verbose
    else if (ByteReceived == '5') {
      printOutput();
    }
    
    
    //change bound for what constitutes being on a note (max 1000)
    else if (ByteReceived == '6') 
    {
      Serial.println("What do you want the new bound to be (0-1000)?");
      //Wait until there's another input
      while (!(Serial.available())) {
        delay(20);
      }
      
      //Get the int that was sent via serial
      ByteReceived = Serial.parseInt();
      Serial.println();
      newBound = int(ByteReceived);
      
      //Change the bound, maxing at 1000.
      bound = newBound % 1001;
    }

    //Change how many degrees the servo turns
    else if (ByteReceived == '7'){
      Serial.println("What do you want the degree to be?");
      while (!(Serial.available())) {
        delay(20);
      }
      
      //Get the int that was sent via serial
      ByteReceived = Serial.parseInt();
      Serial.println();
      newBound = int(ByteReceived);
      
      //Change the bound, maxing at 179.
      finalDegree = newBound % 180;
    }
  }
 
  delay(25);  //delay so as not to have the arduino run at its full speed (there is no point)
}


//Main playing function
void player() {
  for(int i = 0; i < arrayLength; i++){
    sensorValues[i] = digitalRead(sensorPins[i]);
    if(sensorValues[i] < bound){
      servos[i].write(finalDegree);
      servoLocations[i] = finalDegree;
    }
    else{
      servos[i].write(minDegree); //One of the few hardcoded things here, sorry.
      servoLocations[i] = minDegree;
    }
  }
}


//Print the help key
void printHelp() {
  
}


//Print what gets printed where (I need to learn how to dynamically print like I want to; will come back)
void printOutput(){
  return ;
}


//The function to print the sensor values (kept it in here so we aren't always printing).
void printSensorInputs() {
  for(int i = 0; i < arrayLength; i++){
    Serial.print("Value number: ");
    Serial.print(i);
    Serial.print("\t \t");
    Serial.print(sensorValues[i]);
    Serial.print("Servo Location: ");
    Serial.print("\t \t");
    Serial.print(servoLocations[i]);
    Serial.println("");
  }
}
