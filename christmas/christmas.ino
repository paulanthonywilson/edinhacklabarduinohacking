#include <Ultrasonic.h>

#define TRIGGER_PIN  13
#define ECHO_PIN     12

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

const int lowestRedGreen = 2;
const int highestRedGreen = 10;
const int yellow = 11;
const int highest = yellow;
const int lowest = lowestRedGreen;

void setup(){
  Serial.begin(9600);
  for (int i=lowest; i <= highest; i++){
    pinMode(i, OUTPUT);
  }
  
 
  Serial.println("Oh my");
  
}


void steady_flash(int period){
  Serial.println("steady");
  int state = millis() % (period * 2) < period ? HIGH : LOW;
  for (int i=lowest; i <= highest; i++){
    digitalWrite(i, state);
  }
}

void setRedGreen(int state){
  for (int i = lowestRedGreen; i <= highestRedGreen; i++){
    digitalWrite(i, state);
  }
}

void occasional_yellow(){
  Serial.println("occasional yellow");
  setRedGreen(LOW);
  int yellowState = (millis() / 1000) % 20 == 0 ? HIGH : LOW;
  digitalWrite(yellow, yellowState);
  
}

void flash_up(int period){
  Serial.println("flash");
  int timeslice = millis() / period;
  int on_pin = (timeslice % 9) + 2;
  for(int i = lowestRedGreen; i <= highestRedGreen; i++){
    digitalWrite(i, i == on_pin ? HIGH : LOW);
  }
  
  digitalWrite(yellow, on_pin % 2 == 0 ? HIGH: LOW);
}

float readCm() {
  return ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
}


void loop(){
  float cm = readCm();
  if (cm < 100){
    flash_up(cm * 100);
  } else if (cm < 150.0){
    steady_flash(cm * 20);
    
  } else { 
    occasional_yellow();
  }

}
