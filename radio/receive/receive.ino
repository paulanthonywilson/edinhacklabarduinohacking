#include <VirtualWire.h>
byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
char messageChr[VW_MAX_MESSAGE_LEN + 1];


void setup() {
  Serial.begin(9600);
  Serial.println(VW_MAX_MESSAGE_LEN);
  Serial.println("Device is now ready");
  pinMode(13, OUTPUT);
  vw_setup(2000);
  vw_rx_start();

}

long flashLedStart;
void led(){
  digitalWrite(13, millis() - flashLedStart < 250);
}

void flashLed(){
  flashLedStart = millis();
}

void loop() {
  byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
  if (vw_get_message(message, &messageLength)) {
    for(int i = 0; i < messageLength; i++) {
      messageChr[i] = message[i];
    }
    messageChr[messageLength] = 0;
    Serial.println(messageChr);
    
    
    if (strcmp("FAR", messageChr) == 0){
      digitalWrite(13, LOW);
    } else if(strcmp("NEAR", messageChr) == 0) {
      digitalWrite(13, HIGH);
    }
  }

}
