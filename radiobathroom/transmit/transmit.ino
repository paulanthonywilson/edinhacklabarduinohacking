#include <avr/sleep.h>


int wakePin = 2;                 // pin used for waking up
int sleepStatus = 0;             // variable to store a request for sleep
int count = 0;                   // counter

volatile unsigned long wakeCount = 0;
void wakeUpNow() {
  wakeCount++;
}

void setup() {
  pinMode(wakePin, INPUT_PULLUP);
  Serial.begin(9600);
  attachInterrupt(0, wakeUpNow, LOW); 
}

void sleepNow() {
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    sleep_enable();
    attachInterrupt(0,wakeUpNow, LOW); 
    sleep_mode(); // blocks
    
    sleep_disable();
    detachInterrupt(0);
}

void loop()
{
  // display information about the counter
  Serial.print("Awake for ");
  Serial.print(count);
  Serial.print("sec");
  Serial.print(".  Wake count: ");
  Serial.println(wakeCount);
  count++;
  delay(1000);                           // waits for a second

  // compute the serial input
  if (Serial.available()) {
    int val = Serial.read();
    if (val == 'S') {
      Serial.println("Serial: Entering Sleep mode");
      delay(100);     // this delay is needed, the sleep 
                      //function will provoke a Serial error otherwise!!
      count = 0;
      sleepNow();     // sleep function called here
    }
    if (val == 'A') {
      Serial.println("Hola Caracola"); // classic dummy message
    }
  }

  // check if it should go to sleep because of time
  if (count >= 10) {
      Serial.println("Timer: Entering Sleep mode");
      delay(100);     // this delay is needed, the sleep 
                      //function will provoke a Serial error otherwise!!
      count = 0;
      sleepNow();     // sleep function called here
  }
}

