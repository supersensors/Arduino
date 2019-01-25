#include <SR04.h>

#include <HCSR04.h>

//www.elegoo.com
//2016.12.08
#include "SR04.h"
#define TRIG_PIN 12
#define ECHO_PIN 11
SR04 sr04 = SR04(ECHO_PIN,TRIG_PIN);
long distance;
const int ledPin =  LED_BUILTIN;
int ledState = LOW;
int counter = 0;
boolean hasPassed = true;
unsigned long previousMillis = 0;
const long interval = 200;

void setup() {
   Serial.begin(9600);
   delay(1000);
   pinMode(ledPin, OUTPUT);
}
 
void loop() {
   distance=sr04.Distance();
   if(distance < 80){
    if(hasPassed) {
      Serial.println("Activated");
      hasPassed = false;
      delay(500);
    }
   } else {
      hasPassed = true;
   }
  
   Serial.print(distance);
   Serial.println("cm");
   delay(100);
   }
 
