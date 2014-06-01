#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
void setup() {
  Serial.begin(9600);
  Serial.println(VW_MAX_MESSAGE_LEN);
  Serial.println("Device is now ready");
  pinMode(3, OUTPUT);
  vw_setup(2000);
  vw_rx_start();

}

long flashLedStart;
void led(){
  digitalWrite(3, millis() - flashLedStart < 250);
}

void flashLed(){
  flashLedStart = millis();
}

void loop() {
  if (vw_get_message(message, &messageLength)) {
    flashLed();
    Serial.print("Received: ");
    for (int i = 0; i < messageLength; i++)
    {
      Serial.write(message[i]);
    }
    Serial.println();
  } 

  led();
}
