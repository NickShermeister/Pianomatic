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

//Variables for hardcoded songs
int tempo;            //BPM
int timeDelay;  //Delay for each beat
int num_beats;    //number of beats
int total_beats;  //Total number of beats
int current_note = 0; //current note number
int marysBeats[] = {5, 3, 1, 3, 5, 5, 5, 3, 3, 3, 5, 8, 8, 5, 3, 1, 3, 5, 5, 5, 5, 3, 3, 5, 3, 1};
int marysNumBeats[] =   {1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4};
int program_to_run;

//Setup Function
void setup() {  
  //Decide on program to run
  program_to_run = 0;
  
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


//Main loop; commented functions allow for different playing.
void loop() {
  if(program_to_run == 0){
    player();
  }
  else if(program_to_run == 1){
    chords();
  }
  else {
    maryHadALittleLamb();
  }
  
  delay(30);
}



//Main playing function; reads in from IR sensors.
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

  //Change the solenoids' states, with only the high val's location being HIGH and the rest LOW
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

//Hardcoded "Mary Had a Little Lamb"
void maryHadALittleLamb(){
  tempo = 240;
///  int timeDelay = 1000*60/tempo;
  timeDelay = 250;
  num_beats = 0;
  total_beats = 4*8;
  current_note = 0;

  while(num_beats < total_beats){
    digitalWrite(solenoidPins[marysBeats[current_note]-1], HIGH);
    delay(timeDelay*marysNumBeats[current_note]);
    digitalWrite(solenoidPins[marysBeats[current_note]-1], LOW);
    num_beats += marysNumBeats[current_note];
    current_note += 1;
    if(current_note >= 26){
      break;
    }
    delay(60);
  }
  
}

//Play a chord; right now just C Major
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







