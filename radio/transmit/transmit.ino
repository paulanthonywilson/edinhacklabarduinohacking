/*
SimpleSend
This sketch transmits a short text message using the VirtualWire library
connect the Transmitter data pin to Arduino pin 12
*/
#include <VirtualWire.h>
void setup()
{
// Initialize the IO and ISR
  //Serial.begin(9600);
  vw_setup(2000); // Bits per sec
  pinMode(3, OUTPUT);
}

long count = 0;
void loop()
{
  digitalWrite(3, HIGH);
  char msg[20];
  sprintf(msg, "Hello %4d", count++);
  //Serial.println(msg);
  send(msg);
  digitalWrite(3, LOW);
  delay(1000);
  
}

void send (char *message)
{
  vw_send((uint8_t *)message, strlen(message));
  vw_wait_tx(); // Wait until the whole message is gone
}

