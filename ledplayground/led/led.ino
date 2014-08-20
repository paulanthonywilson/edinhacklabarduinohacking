#include "LedControl.h"


LedControl lc=LedControl(12,11,10,2);


void printNumber(unsigned long v) {
  v = v %100000000;
  for(long i = 0; i < 8; i++){
    long val = (long)(v / pow(10, i)) % 10;
    lc.setDigit(0, i, (byte) val, false);
  }

}

unsigned long start;

void setup(){
  Serial.begin(9600);
  Serial.println(lc.getDeviceCount());
  lc.shutdown(0, false);
  lc.setIntensity(0,3);
  randomSeed(analogRead(3));
  long r = random(10000000);
  Serial.println(r);
  start = millis();
}




void loop(){
  
  long runningTime = millis() - start;
  long secs = runningTime;
 
  
  //lc.setIntensity(0, random(10));
  printNumber(100000000l - secs);
  delay(70);

  
  
}
