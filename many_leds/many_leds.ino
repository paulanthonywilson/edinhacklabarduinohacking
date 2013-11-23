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
  
  int buttonState = digitalRead(button);
  Serial.println(buttonState);
  if(0 == buttonState){
   
    
  
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
