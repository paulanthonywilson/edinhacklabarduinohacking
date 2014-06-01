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
  
 
  Serial.println("********");
  
}




float readCm() {
  return ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
}

int period;
float cm;

int steady_flash_state = LOW;
void steady_flash(){
  steady_flash_state = steady_flash_state == LOW ? HIGH : LOW;
  for(int i = lowest; i <= highest; i++){
    digitalWrite(i, steady_flash_state);
  }
}

long last_change = 0;

void (*action)();

void flash(){
  if(millis() - last_change > period){
    (*action)();
    last_change = millis();
  }
}


int cylon_number = 0;
int cylon_pin(){
  if (cylon_number < 9) {
    return cylon_number + 2;
  } else {
    return 19 - cylon_number;
  }

}
void cylon(){
  digitalWrite(cylon_pin(), LOW);
  cylon_number = (cylon_number + 1) % 18;
  digitalWrite(cylon_pin(), HIGH);
  digitalWrite(yellow, cylon_number < 9 ? HIGH : LOW);
}
 
void darkenAll(){
  for(int i = lowest; i <= highest; i++){
    digitalWrite(i, LOW);
  }
}

void set_action(void (*new_action)()){
  if (new_action != action){
    darkenAll();
    action = new_action; 
  }
}

void loop(){
  cm = readCm();
  if(cm < 100.0){
    period = max(cm * 5, 100);
    set_action(cylon);
  } else {
    period = min(2000, cm * 10);
    set_action(steady_flash);
  }
  flash();

}
