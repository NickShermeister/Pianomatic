//Code for running the stepper motor
//Speed of scrolling and be adjusted by the delay time

void setup() {
  pinMode(13, OUTPUT); 
}

void loop() {
  digitalWrite(13, HIGH);
  delay(1);
  digitalWrite(13, LOW);
  delay(1);
}
