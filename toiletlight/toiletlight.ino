const int red = 13;
const int green = 12;
const int sensor = 2;


void setup(){
  //Serial.begin(9600);
  pinMode(red, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(sensor, INPUT);
}

void loop(){
  int sensorState = digitalRead(sensor);
  digitalWrite(red, sensorState);
  digitalWrite(green, !sensorState);
  delay(500);
}
  

