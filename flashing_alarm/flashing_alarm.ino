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
}


float distanceToObject(){
  return ultrasonic.convert(ultrasonic.timing()), Ultrasonic::CM);
}

float alarmCm(){
 return 90.0;
}

void soundAlarm(){
  digitalWrite(7, HIGH);
  tone(5, 500, 50);
  delay(50);
  digitalWrite(6, HIGH);
  tone(5, 1000, 50);
  delay(50);
  digitalWrite(7, LOW);
  tone(5, 1500, 50);
  delay(50);
  digitalWrite(6, LOW);  
}

void loop(){
  if (distanceToObject() < alarmCm()){
    soundAlarm();
  }
}

