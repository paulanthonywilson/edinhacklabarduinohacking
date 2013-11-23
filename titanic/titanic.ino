int led=13;

void setup(){
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Maiden voyage!");
 
}

int pauseDelay = 500;

void flash(int timeLit){
  digitalWrite(led, HIGH);
  delay(timeLit);
  digitalWrite(led, LOW);
  delay(pauseDelay);

}

void dot(){
  flash(200);
}

void dash(){
  flash(1000);
}

void send(char letter){
  switch(letter){
    case 'o':
    dash();
    dash();
    dash();
    break;
    case 's':
    dot();
    dot();
    dot();
    break;
  }
}

void loop(){
  Serial.println("Iceberg!!");
  send('s');
  send('o');
  send('s');
  
  dash();
  dash();
  dash();
  
  dot();
  dot();
  dot();
  
  Serial.println("Help me! I'm sinking.");
  delay(2000);
}
