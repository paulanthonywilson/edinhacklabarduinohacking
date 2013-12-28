

#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     3

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

#define RED 11
#define GREEN 10
#define BLUE 9

#define GREEN_LIMIT 120.0
#define AMBER_LIMIT 70.0
#define WHITE_LIMIT 200.0


void setup(){
  Serial.begin(9600);
  for(int i = 9; i < 12; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  tone(8, 200, 1000);

}



float cm_proximity(){
  return ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
}

int counter = 0;

void write_colour(char colour_pin, char rgb_code){
  analogWrite(colour_pin, 255 - (rgb_code % 256));
}

float weight(float high, float low, float proximity){
  return max(255, (proximity - low) / (high - low) * 255);
}


void green(float proximity){
  write_colour(GREEN, 255);
  write_colour(RED, weight(WHITE_LIMIT, GREEN_LIMIT, proximity));
  write_colour(BLUE, 0);
} 

void amber(float proximity){
  write_colour(GREEN, weight(GREEN_LIMIT, AMBER_LIMIT, proximity));
  write_colour(RED, 255);
  write_colour(BLUE, 0);
}


void red(float proximity){
  write_colour(BLUE, 0);
  write_colour(GREEN, 0);
  write_colour(RED, 255);
}

void white(float proximity){
  write_colour(BLUE, 255 - weight(3500, AMBER_LIMIT, proximity));
  write_colour(GREEN, 255);
  write_colour(RED, 255);
}



void (*colour_action)(float x);
void set_colour(void (*colour_function)(float)){
  colour_action = colour_function;
}


double last_interval = 0;

void off(){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
}


double last_flash = 0.0;
void flash(float proximity){
  if(millis() - last_flash > 700.0){
    off();
  } else {
    (colour_action)(proximity);
  }
  if(millis() - last_flash > 1200.0){
    last_flash = millis();
  }
}





double last_change = 0;
int tone_value = 400;
void sound(){
  if(millis() > last_change + 500.0){
    last_change = millis();
    tone_value = tone_value == 300 ? 800 : 300;
    tone(8, tone_value, 500);
    delay(500);
    Serial.println(tone_value);
  }
}


void loop(){
  float proximity = cm_proximity();
  //Serial.print(proximity);
 
  if (proximity > WHITE_LIMIT){
    set_colour(white);
    //Serial.println(" white");
  } else if(proximity > GREEN_LIMIT){
     set_colour(green);
     //Serial.println(" green");
  } else if(proximity > AMBER_LIMIT){
    set_colour(amber);
    //Serial.println(" amber");
  } else {
    set_colour(red);
    //Serial.println(" red");
  }
  
  flash(proximity);
  if (proximity < 50.0){
    sound();
  }
  
  
}
