  

#include <Ultrasonic.h>

#define TRIGGER_PIN  4
#define ECHO_PIN     3

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

#define RED 11
#define GREEN 10
#define BLUE 9

#define GREEN_LIMIT 140.0
#define AMBER_LIMIT 80.0
#define RAINBOW_LIMIT 230.0


void setup(){
  Serial.begin(9600);
  for(int i = 9; i < 12; i++){
    pinMode(i, OUTPUT);
    digitalWrite(i, HIGH);
  }
  tone(8, 200, 1000);

}




int counter = 0;

void write_colour(char colour_pin, char rgb_code){
  analogWrite(colour_pin, 255 - (rgb_code % 256));
}



void green(){
  write_colour(GREEN, 255);
  write_colour(RED, 0);
  write_colour(BLUE, 0);
} 

void amber(){
  write_colour(GREEN, 255);
  write_colour(RED, 255);
  write_colour(BLUE, 0);
}


void red(){
  write_colour(BLUE, 0);
  write_colour(GREEN, 0);
  write_colour(RED, 255);
}

long rainbow_colour = -1;
void rainbow(){
  if(rainbow_colour < 0) rainbow_colour = random(0,16777216);
  int red = rainbow_colour / 65536;
  int green = ((rainbow_colour - red) / 256) % 256;
  int blue  = rainbow_colour % 256;
  Serial.print(rainbow_colour);
  Serial.print(" "); 
  Serial.print(red);
  Serial.print(" "); 
  Serial.print(green);
  Serial.print(" ");
  Serial.print(blue);
  Serial.println();
  
  
  write_colour(BLUE, blue);
  write_colour(GREEN, green);
  write_colour(RED, red);
}



void (*colour_action)();
void set_colour(void (*colour_function)()){
  colour_action = colour_function;
}


double last_interval = 0;

void off(){
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  
}


double last_flash = 0.0;
bool is_on = true;
void flash(){
 
  if(millis() - last_flash > 700.0){
    if(is_on){
      off();
      is_on = false;
    }
  } else {
    if(!is_on){
      (colour_action)();
      is_on = true;
    }
  }
  if(millis() - last_flash > 1200.0){
    last_flash = millis();
    rainbow_colour = -1;
  }
 
}



void playTone(int period, int duration)
{
// period is one cycle of tone
// duration is how long the pulsing should last in milliseconds
  int pulse = period / 2;
  for (long i = 0; i < duration * 1000L; i += period )
  {
    digitalWrite(8, HIGH);
    delayMicroseconds(pulse);
    digitalWrite(8, LOW);
    delayMicroseconds(pulse);
  }
}

double last_sound = -30000;
void sound(){
  Serial.print("sound ");
  Serial.println(millis() - last_sound);
  if(millis() - last_sound > 5000){
    for (int i=0; i < 5; i++){
      playTone(100, 200);
      playTone(400, 200);
    }
    last_sound = millis();
  }
}


double filtered_proximity = -1;
double raw_proximity;

const double proximity_k = 0.1;
void detect_proximity(){
  raw_proximity = ultrasonic.convert(ultrasonic.timing(), Ultrasonic::CM);
  raw_proximity = min(300.0, raw_proximity);
  if(filtered_proximity < 0) filtered_proximity = raw_proximity;
  filtered_proximity = filtered_proximity + proximity_k * (raw_proximity - filtered_proximity);
  
}




void loop(){
  detect_proximity();

  if (filtered_proximity > RAINBOW_LIMIT){
    set_colour(rainbow);
  } else if(filtered_proximity > GREEN_LIMIT){
     set_colour(green);
  } else if(filtered_proximity > AMBER_LIMIT){
    set_colour(amber);
  } else {
    set_colour(red);
  }
  
  flash();
  if (filtered_proximity < 50.0){
    sound();
  }
  
  
}
