/*
SimpleSend
This sketch transmits a short text message using the VirtualWire library
connect the Transmitter data pin to Arduino pin 12
*/
#include <VirtualWire.h>
#include <NewPing.h>

#define TRIGGER_DISTANCE 130

NewPing sonar(4,3,200);

void setup()
{
// Initialize the IO and ISR
  Serial.begin(9600);
  vw_setup(2000); // Bits per sec
  pinMode(13, OUTPUT);
}

long flashStart = 0;
void flashLed(){
  flashStart = millis();

}

void led(){
  digitalWrite(13, millis() - flashStart < 200);
}

char message[VW_MAX_MESSAGE_LEN];
void loop(){
  delay(50);
  unsigned int cm = sonar.ping() / US_ROUNDTRIP_CM;
  sprintf(message, "%5d", cm);
  send(message);
  digitalWrite(13, cm < TRIGGER_DISTANCE);


}





void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

