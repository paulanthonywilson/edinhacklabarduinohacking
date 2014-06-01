

volatile int state = LOW;
volatile unsigned long interrupt_count = 0;
void setup(){
  Serial.begin(9600);
  pinMode(2, INPUT);
  attachInterrupt(0, pressed, CHANGE);

}

void loop(){
  /*Serial.println(digitalRead(2));*/
  Serial.print(digitalRead(2));
  Serial.print(" ");
  Serial.print(interrupt_count);
  Serial.print(" ");
  Serial.println(state);
}


void pressed(){
  state = !state;
  interrupt_count++;
}
