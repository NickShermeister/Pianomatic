//Looking at the machine, the far left is C. Far right is B (Make sure IR sensor is 1 when facing you)

//Multiplexer constants
const int selectPins[3] = {11, 12, 13};
const int zInput = A0;

//Other pin constants
int sensorPins[] = {A1, A2, A3, A4};
int sensorBounds[] = {350, 350, 350, 475, 340, 350, 475, 600, 350, 350, 350, 350};
int solenoidPins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, A5};
int sensorReads[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
int sum = 0;
int highVal = 0;
int highLoc = 0;
//w b w b w w b w b w b w (key orders)
const int arrayLength = 12;     //Number of notes in an octave

//Normal variables
int sensorValues[12];  //Multiplexed: 0-7; Normal read-ins: 8-11


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
    sensorValues[i] = analogRead(zInput);
    if (sensorValues[i] > highVal){
      highVal = sensorValues[i];
      highLoc = i;
    }
  }
  

  //Then get values for the other 4
  for (int i = 0; i < 4; i++){
    sensorValues[i+8]=analogRead(sensorPins[i]);
    if (sensorValues[i+8] > highVal){
      highVal = sensorValues[i+8];
      highLoc = i;
    }
  }

  for(int i = 0; i < 12; i++){
    if(i == highLoc){
      digitalWrite(solenoidPins[i], HIGH);
    }
    else{
      digitalWrite(solenoidPins[i], LOW);
    }
  }
  highLoc = 0;
  highVal = 0;
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

