//Looking at the machine, the far left is C. Far right is B (Make sure IR sensor is 1 when facing you)

//Multiplexer constants
const int selectPins[3] = {11, 12, 13};
const int zInput = A0;

//Other pin constants
int sensorPins[] = {A1, A2, A3, A4};
int sensorBounds[] = {300, 300, 250, 300, 200, 300, 300, 300, 300, 300, 300, 300};
int solenoidPins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, A5};
//w b w b w w b w b w b w (key orders)


//Misc. Variables
int highVal = -1;   //Highest value in this check of hte IR sensors
int highLoc = 0;    //Location in the array of sensor reads of the high val
int sensorReads[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};   //All values of this read
const int arrayLength = 12;     //Number of notes in an octave
int sensorValues[12];  //Multiplexed: 0-7; Normal read-ins: 8-11
int tempo;


//Setup Function
void setup() {  
  //Set up solenoid pins as outputs
  for(int i = 0; i < arrayLength; i++){
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], LOW);
  }

  //Set up multiplexing pins as outputs
  for (int i=0; i<3; i++)
  {
    pinMode(selectPins[i], OUTPUT);
    digitalWrite(selectPins[i], LOW);
  }
 pinMode(zInput, INPUT);    //Set up multiplexing input as an input
 //Set up remainder of sensor pins as inputs
 for(int i = 0; i < 4; i ++)
 {
  pinMode(sensorPins[i], INPUT);
 } 
}


//Main loop
void loop() {
  maryHadALittleLamb();
//  player();
//  chords();
//  digitalWrite(5, HIGH);
//  delay(70);  //delay so as not to have the arduino run at its full speed (there is no point)
//  digitalWrite(5, LOW);
  delay(30);
}



//Main playing function
void player() {
  
  //Get values for multiplexed sensors and compare to the high val
  for(int i = 0; i < 8; i++){
    selectMultiplexerPin(i);
    sensorValues[i] = analogRead(zInput);
    if (sensorValues[i] > highVal && sensorValues[i]>sensorBounds[i]){
      highVal = sensorValues[i];
      highLoc = i;
    }
  }
  

  //Then get values for the other 4 and compare to high val
  for (int i = 0; i < 4; i++){
    sensorValues[i+8]=analogRead(sensorPins[i]);
    if (sensorValues[i+8] > highVal && sensorValues[i+8]>sensorBounds[i]){
      highVal = sensorValues[i+8];
      highLoc = i;
    }
  }

  //Change the solenoids' states, with only the high val being HIGH and the rest LOW
  for(int i = 0; i < 12; i++){
    if(i == highLoc){
      digitalWrite(solenoidPins[i], HIGH);
    }
    else{
      digitalWrite(solenoidPins[i], LOW);
    }
  }
  //Reset the high location and value
  highLoc = -1;
  highVal = -1;
}

//Select the right pin for multiplexing
void selectMultiplexerPin(int pin) {
  if (pin > 7) return; // Exit if pin is out of scope
  
  for (int i=0; i<3; i++) //Loop through all 3 pins
  {
    if (pin & (1<<i))     //Determine if the pin should output HIGH or LOW
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}

void maryHadALittleLamb(){
  tempo = 60;
///  int timeDelay = 1000*60/tempo;
  int timeDelay = 250;
  int num_beats = 0;
  int total_beats = 4*8;
  int current_note = 0;
  int marysBeats[] = {5, 3, 1, 3, 5, 5, 5, 3, 3, 3, 5, 8, 8, 5, 3, 1, 3, 5, 5, 5, 5, 3, 3, 5, 3, 1};
  int numBeats[] =   {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4};

  while(num_beats < total_beats){
    digitalWrite(solenoidPins[marysBeats[current_note]-1], HIGH);
    delay(timeDelay*numBeats[current_note]);
    digitalWrite(solenoidPins[marysBeats[current_note]-1], LOW);
    num_beats += numBeats[current_note];
    current_note += 1;
    if(current_note >= 26){
      break;
    }
    delay(60);
  }
  
}

void chords(){
  int chord[] = {0, 4, 7};

  for(int i = 0; i < 3; i++){
    digitalWrite(solenoidPins[chord[i]], HIGH);
  }
  delay(1000);
  for(int i = 0; i < 3; i++){
    digitalWrite(solenoidPins[chord[i]], LOW);
  }
  
  
}







