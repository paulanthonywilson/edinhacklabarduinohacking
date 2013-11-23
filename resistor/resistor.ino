const int button = 8;

void setup(){
  Serial.begin(9600);
  for(int i=13; i > 8; i--){
    pinMode(i, OUTPUT);
  }

  pinMode(button, INPUT);
  digitalWrite(button, HIGH);

}


int delayValue(){
  return analogRead(0);
}
int buttonState(){
  return digitalRead(button);
}

void switchLights(int state){
  for(int i=13; i > 8; i--){
    if(buttonState() == 1){
      digitalWrite(i, state);
      delay(delayValue());
    }
  }
}

void loop(){
  switchLights(HIGH);
  switchLights(LOW);
}
