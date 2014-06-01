#include <avr/sleep.h>
#include <VirtualWire.h>


int wakePin = 2;                 // pin used for waking up
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter

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

void setLoopState(void (*newState)()){
  if(loopState != newState){
    millisEnteredState = millis();
    loopState = newState;
  }
}

void doorOpenLoop(){
  Serial.print("open ");
  send("The bathroom door is open. Thank you.");
}
void doorClosedLoop(){
  Serial.print("closed ");
  send("The bathroom door is closed. Thank you.");
}


void loop() {
  if(isDoorClosed()){
    setLoopState(doorOpenLoop);
  } else {
    setLoopState(doorClosedLoop);
  }
  (*loopState)();
  Serial.print(millisInState());
  Serial.print(" ");
  Serial.println(isDoorClosed());
}

