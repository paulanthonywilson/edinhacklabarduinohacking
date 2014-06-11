#include <VirtualWire.h>

#define DOOR_OPEN_MESSAGE "b1e Bathroom is open."
#define DOOR_CLOSED_MESSAGE "b1e Bathroom is closed."

byte message[VW_MAX_MESSAGE_LEN]; // a buffer to store the incoming messages
char messageChr[VW_MAX_MESSAGE_LEN + 1];
bool bathroomOpen = true;
bool bathroomClosed = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Device is now ready");
  Serial.println(VW_MAX_MESSAGE_LEN);
  Serial.println("Device is definitely now ready");
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  vw_setup(2000);
  vw_rx_start();

}



void loop() {
  byte messageLength = VW_MAX_MESSAGE_LEN; // the size of the message
  if (vw_get_message(message, &messageLength)) {
    for (int i = 0; i < messageLength; i++) {
      messageChr[i] = message[i];
    }
    messageChr[messageLength]=0;
     
    bathroomOpen = strcmp(DOOR_OPEN_MESSAGE, messageChr) == 0;
    bathroomClosed = strcmp(DOOR_CLOSED_MESSAGE, messageChr) == 0;


    Serial.println(messageChr);

    Serial.println(bathroomOpen);
    Serial.println(bathroomClosed);
  } 
  digitalWrite(3, bathroomClosed);
  digitalWrite(4, bathroomOpen);
  
}
