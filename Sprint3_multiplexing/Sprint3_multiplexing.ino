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
int sensorBounds[] = {230, 480, 630, 320};
int multiplexerSensorBounds[] = {200, 350, 350, 475, 340, 275, 475, 460};
int solenoidPins[] =  {2, A0, 3, A0, 4, 5, A0, 6, A0, 7, A0, 8};
//int solenoidPins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, A5};
//w b w b w w b w b w b w 
int tempServo = 0;
const int arrayLength = 12;     //Number of notes in an octave

//TODO: DIGITAL INTERRUPT (haven't discussed as group yet)

//Normal variables
int sensorValues[4];  //Normal sensor values
int sensorValuesMultiplexer[8]; //Sensor values in multiplexer
int ByteReceived = -1;    // variable that holds what bytes are received from serial
int bound = 800;          //The boundary that constitutes being on something; arbitrary needs to be determined
int tempInput = 0;        //The new bound before max/min are taken into account
unsigned long previousMillis = 0; //
int interval = 1000;      //Interval between test reads
String toPrint = "";



//Setup Function
void setup() {
  Serial.begin(9600); //Begin the serial so we can read from it/print to it
  printHelp();   // print the key
  printOutput(); // print what is printed in each of the four columns
  
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
  
  //Wait, nonverbose output
  if (ByteReceived == '0') {
    //pass
  }

  //Wait, verbose output
  else if (ByteReceived == '1') //Stay still.
  {
    printSensorInputs(false);
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
    printSensorInputs(false);
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

    //Change a bound
    else if (ByteReceived == '6'){
      Serial.println("What bound do you want to change?");
      
      while (!(Serial.available())) {
        delay(20);
      }
      
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived);

      if (tempInput < 8){
        Serial.println("What value do you want?");
        while (!(Serial.available())) {
          delay(20);
      }
      }
      else if (tempInput < 12){
        
      }
      else {
        Serial.println("Out of bounds. Try again.");
      }
    }
    
    
    else if (ByteReceived == '9'){
      Serial.println("What do you want the delay between outputs (in ms)");
      
      while (!(Serial.available())) {
        delay(20);
      }
      
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived);

      interval = tempInput;
    }

    

    else if (ByteReceived == 'A'){
      Serial.println("One Reading:");
      delay(100);
      
      printSensorInputs(true);
    }

    else if (ByteReceived == 'B'){
      Serial.println("What solenoid do you want to test? (location in array)");
      
      while (!(Serial.available())) {
        delay(20);
      }
      
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived) % arrayLength;

      if (tempInput < 8){
        Serial.println(sensorValuesMultiplexer[tempInput]);
      }
      else{
        Serial.println(sensorValues[tempInput-8]);
      }
    }
  }
 
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
//      if (ByteReceived == '3'){
//        printState(i, true);
//      }
    }
    else {
      digitalWrite(solenoidPins[i], LOW);
//      if (ByteReceived == '3'){
//        printState(i, false);
//      }
    }
  }


  
  //Then get values for the other 4
  for (int i = 0; i < 4; i++){
    sensorValues[i]=analogRead(sensorPins[i]);
    if(sensorValues[i] > sensorBounds[i]){
      digitalWrite(solenoidPins[i+8], HIGH);
//      if (ByteReceived == '3'){
//        printState(i+8, true);
//      }
    }
    else {
      digitalWrite(solenoidPins[i+8], LOW);
//      if (ByteReceived == '3'){
//        printState(i+8, false);
//      }
    }
  }
}

void printState(int pin, bool state) {
  if (state == true){
    toPrint += "Pin no: ";
    toPrint += String(pin);
    toPrint += " with output: HIGH";
    Serial.println(toPrint);
    toPrint = "";
  }
  else {
    toPrint += "Pin no: ";
    toPrint += String(pin);
    toPrint += " with output: LOW";
    Serial.println(toPrint);
    toPrint = "";
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


//Print the help key
void printHelp() {
  Serial.println("The key for changing modes/variables in this system is:");
  Serial.println("0: System at rest; nonverbose output.");
  Serial.println("1: System at rest; verbose output.");
  Serial.println("2: System active; nonverbose output.");
  Serial.println("3: System active; verbose output.");
  Serial.println("4: Print this help table again.");
  Serial.println("5: When mass printing values, can print which columns align to which values.");
  Serial.println("9: Changes how frequently you print sensor values.");
  Serial.println("A: Read in once from all sensors.");
  Serial.println("B: Test individual solenoid.");
}


//Print what gets printed where (I need to learn how to dynamically print like I want to; will come back)
void printOutput(){
  return;
}


//The function to print the sensor values (kept it in here so we aren't always printing).
void printSensorInputs(bool Force) {
    unsigned long currentMillis = millis();

  //Check to see if there is a large enough gap since the last button update
  if ((currentMillis - previousMillis) >= interval || Force){
    for(int i = 0; i < 8; i++){
      Serial.print("Array position: ");
      Serial.print(i);
      Serial.print("; \t");
      Serial.print(sensorValuesMultiplexer[i]);
      Serial.println("");
        } 
    for(int i = 0; i < 4; i++){
      Serial.print("Array position: ");
      Serial.print("A" + String(i+1));
      Serial.print("; \t");
      Serial.print(sensorValues[i]);
      Serial.println("");
    }
    Serial.println("\n\n");
    previousMillis = currentMillis;
  
  }
}


