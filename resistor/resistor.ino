const int button = 8;

void setup(){
  Serial.begin(9600);
  for(int i=13; i > 8; i--){
    pinMode(i, OUTPUT);
  }

  pinMode(button, INPUT);
  digitalWrite(button, HIGH);

}

void loop(){
 int delayValue = analogRead(0);
  Serial.print("Analog reading: ");
  Serial.println(delayValue);
  
  int buttonState = digitalRead(button);
  if(1 == buttonState){



    for(int i=13; i > 8; i--){
      digitalWrite(i, HIGH);
      delay(100);
    }

    for(int i=13; i > 8; i--){
      digitalWrite(i, LOW);
      delay(100);
    }
  }

}
