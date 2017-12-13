//Looking at the machine, the far left is C. Far right is B (Make sure IR sensor is 1 when facing you)


int solenoidPins[] =  {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, A5};
//w b w b w w b w b w b w (key orders)
const int arrayLength = 12;     //Number of notes in an octave


//Setup Function
void setup() {  
  //mount Servos and set to 0 degrees
  for(int i = 0; i < arrayLength; i++){
    pinMode(solenoidPins[i], OUTPUT);
    digitalWrite(solenoidPins[i], LOW);
  }
 
}

void loop() {
  player();
}

//Main playing function
void player() {
  
  //First deal with multiplexer Serial.println(analogRead(zInput));
  for(int i = 0; i < 12; i++){
      digitalWrite(solenoidPins[i], HIGH);
      delay(1000);
      digitalWrite(solenoidPins[i], LOW);
  }

}

