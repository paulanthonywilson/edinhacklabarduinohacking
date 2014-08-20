

#include <NewPing.h>
#include "LedControl.h"

#define TRIGGER_DISTANCE 20

const int trigger = 4;
const int echo = 3;
const int ledPin = 13;

LedControl lc=LedControl(12,11,10,2);

NewPing sonar(trigger,echo,300);

void setup()
{

  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  lc.shutdown(0, false);
  //delay(100);  
  //lc.shutdown(0, false);
  //lc.setIntensity(0,1);
  
}


unsigned int cm;

void printCm(unsigned int v) {
  Serial.print(v);
  Serial.print(" ");
  v = v % 1000;
  Serial.print(v);
  Serial.println("cm");
  for(int i = 0; i < 3; i++){
    int val = (int)(v / pow(10, i)) % 10;
    lc.setDigit(0, i, (byte) val, false);
  }

}


unsigned long lastUpdate;
void updateLed(){
  unsigned long now = millis();
  if(false && now - lastUpdate > 10000){
    printCm(cm);
    lastUpdate = now;
  }
}


void loop(){

  cm = sonar.ping_median(); // US_ROUNDTRIP_CM;
  digitalWrite(13, cm < TRIGGER_DISTANCE);
  
  if (cm < TRIGGER_DISTANCE) {
     lc.setDigit(0,0, (byte) 4, false);
  }
  
 
  Serial.println(sonar.convert_cm(cm));
  updateLed();
  delay(50);


}






