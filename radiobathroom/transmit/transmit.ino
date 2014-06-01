#include <VirtualWire.h>
#include <avr/sleep.h>

#define DOOR_OPEN_MESSAGE "Bathroom door is open."
#define DOOR_CLOSED_MESSAGE "Bathroom door is closed."

int wakePin = 2;

void wakeUpNow() { }

void (*loopState)();
unsigned long millisEnteredState = 0l;

void setup() {
  pinMode(wakePin, INPUT_PULLUP);
  vw_setup(2000); // Bits per sec
  Serial.begin(9600);
}

void send (char *message) {
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
  Serial.println(message);
}


void sleepNow() {
  Serial.println("About to sleep");
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  attachInterrupt(0,wakeUpNow, LOW);
  sleep_mode(); // blocks

  sleep_disable();
  detachInterrupt(0);
}

bool isDoorClosed(){
  return digitalRead(2) == LOW;
}

long millisInState(){
  return millis() - millisEnteredState;
}

bool isNewToState(){
  return millisInState() < 10000;
}

void setLoopState(void (*newState)()){
  if(loopState != newState){
    millisEnteredState = millis();
    loopState = newState;
  }
}

void doorOpenLoop(){
  if(isNewToState()){ 
    send(DOOR_OPEN_MESSAGE);
    delay(250);
  } else {
    sleepNow();
  }
}
void doorClosedLoop(){
  if(isNewToState()){
    send(DOOR_CLOSED_MESSAGE);
    delay(250);
  }
}



void loop(){
  if(isDoorClosed()){
    setLoopState(doorClosedLoop);
  } else {
    setLoopState(doorOpenLoop);
  }
  (*loopState)();
  delay(100);
  Serial.println("tick");
}
