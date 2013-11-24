/*
 * HCSR04Ultrasonic/examples/UltrasonicDemo/UltrasonicDemo.pde
 *
 * SVN Keywords
 * ----------------------------------
 * $Author: cnobile $
 * $Date: 2011-09-17 02:43:12 -0400 (Sat, 17 Sep 2011) $
 * $Revision: 29 $
 * ----------------------------------
 */

#include <Ultrasonic.h>

#define TRIGGER_PIN  12
#define ECHO_PIN     11

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);


void setup(){
  Serial.begin(9600);
  
  pinMode(7, OUTPUT);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}


const int detectedCm = 150;
const int dangerCm = 120;
const int alarmCm = 90;

void loop(){
  //
  float cmMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM);
  
  if(cmMsec > detectedCm) {
    digitalWrite(7, LOW);
    digitalWrite(6, LOW);
  } else {    
    digitalWrite(6, HIGH);
    if (cmMsec > dangerCm){
      digitalWrite(7, LOW);
    } else {
      digitalWrite(7, HIGH);
      if (cmMsec <= alarmCm){
        tone(5, 1000, 10);
      }
    }
  }

}
