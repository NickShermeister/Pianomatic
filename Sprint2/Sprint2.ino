//Include needed libraries
#include <Servo.h>
//#include <Adafruit_MotorShield.h>
//#include "utility/Adafruit_MS_PWMServoDriver.h"


//Define variables
//Every servo will handle 6 IR sensors/servos
//ONLY HARDCODED VARIABLES; make sure they correleate 1:1. If they don't, everything breaks.
int sensorPins[] = {A0, A1, A2, A3, A4, A5};
int servoPins[] =  {8,  9,  10, 11, 12, 13};
bool servoDirection = true; //We will have two different directions, but each servo will be constant. Therefore, we only need one bool to know what direction the servo should be set up in.
//TODO: DIGITAL INTERRUPT (haven't discussed as group yet)

//Normal variables
const int arrayLength = int(sizeof(sensorPins)/sizeof(int));
int sensorValues[arrayLength];  //this way we only have to define where the sensors are
Servo servos[arrayLength];
int servoLocations[arrayLength];


int ByteReceived = -1;    // variable that holds what bytes are received from serial
int bound = 900;          //The boundary that constitutes being on something; arbitrary needs to be determined
int tempInput = 0;        //The new bound before max/min are taken into account
int finalDegree = 80;
int highDegree = 90;
unsigned long previousMillis = 0;
int interval = 1000;
int pos;
int tempAngle = 0;


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
    if (servoDirection) {
      servos[i].write(finalDegree);
      servoLocations[i] = finalDegree;
    }
    else {
      servos[i].write(highDegree);
      servoLocations[i] = highDegree;
    }
    
    servoLocations[i] = highDegree;
  }
  
}


void loop() {
  
  //Wait, nonverbose output
  if (ByteReceived == '0') {
    
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
      tempInput = int(ByteReceived);
      
      //Change the bound, maxing at 1000.
      bound = tempInput % 1001;
    }

    //Change how many degrees the servo turns
    else if (ByteReceived == '7'){
      Serial.println("What do you want the rest degree to be?");
      while (!(Serial.available())) {
        delay(20);
      }
      
      //Get the int that was sent via serial
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived);
      
      //Change the bound, maxing at 179.
      highDegree = tempInput % 180;
    }

    else if (ByteReceived == '8'){
      Serial.println("What do you want the hit degree to be?");
      while (!(Serial.available())) {
        delay(20);
      }
      
      //Get the int that was sent via serial
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived);
      
      //Change the bound, maxing at 179.
      finalDegree = tempInput % 180;
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
      Serial.println("What servo do you want to test? (location in array)");
      
      while (!(Serial.available())) {
        delay(20);
      }
      
      ByteReceived = Serial.parseInt();
      Serial.println();
      tempInput = int(ByteReceived) % arrayLength;

      sweep(tempInput);
    }
  }
 
  delay(25);  //delay so as not to have the arduino run at its full speed (there is no point)
}


//Main playing function
void player() {
  for(int i = 0; i < arrayLength; i++){
    sensorValues[i] = analogRead(sensorPins[i]);
    if(!servoDirection) {
      if(sensorValues[i] > bound){
        tempAngle = finalDegree;
      }
      else{
        tempAngle = highDegree;
      }
    }
    else {
      if(sensorValues[i] > bound){
        tempAngle = 180-finalDegree;
      }
      else{
        tempAngle = 180-highDegree;
      }
    }
    servos[i].write(tempAngle);
    servoLocations[i] = tempAngle;
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
  Serial.println("6: Change the bound for what constitutes being on a note (max of 1000, min of 0).");
  Serial.println("7: Changes the servos' start angle (max of 180, min of 0).");
  Serial.println("8: Changes the servos' end angle (max of 180, min of 0).");
  Serial.println("9: Changes how frequently you print sensor values.");
  Serial.println("A: Read in once from all sensors.");
  Serial.println("B: Run sweep on an individual servo to make sure it's working.");

}


//Print what gets printed where (I need to learn how to dynamically print like I want to; will come back)
void printOutput(){
  return ;
}

void sweep(int location) {
  if(!servoDirection) {
    for (pos = 0; pos < 179; pos += 2) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servos[location].write(pos);              // tell servo to go to position in variable 'pos'
      if ((Serial.available())) {
          break;
        }
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 180; pos > 1; pos -= 2) { // goes from 180 degrees to 0 degrees
      servos[location].write(pos);              // tell servo to go to position in variable 'pos'
      if ((Serial.available())) {
          break;
        }
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  else {
    for (pos = 180; pos > 1; pos -= 2) { // goes from 180 degrees to 0 degrees
      servos[location].write(pos);              // tell servo to go to position in variable 'pos'
      if ((Serial.available())) {
          break;
        }
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    for (pos = 0; pos < 179; pos += 2) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      servos[location].write(pos);              // tell servo to go to position in variable 'pos'
      if ((Serial.available())) {
          break;
        }
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}


//The function to print the sensor values (kept it in here so we aren't always printing).
void printSensorInputs(bool Force) {
    unsigned long currentMillis = millis();

  //Check to see if there is a large enough gap since the last button update
  if ((currentMillis - previousMillis) >= interval || Force){
    for(int i = 0; i < arrayLength; i++){
      Serial.print("Array position: ");
      Serial.print(i);
      Serial.print("; \t");
      Serial.print(sensorValues[i]);
      Serial.print("\t\tServo Location: ");
      Serial.print("\t");
      Serial.print(servoLocations[i]);
      Serial.println("");
        } 
    previousMillis = currentMillis;
  
  }
}

