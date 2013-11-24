
void setup(){
  Serial.begin(9600);
}

void loop(){
  int reading = analogRead(0);
  tone(9, 120 + reading, 10);
}
