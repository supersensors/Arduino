/***************************************************************************
  This is a library for the AMG88xx GridEYE 8x8 IR camera

  This sketch tries to read the pixels from the sensor

  Designed specifically to work with the Adafruit AMG88 breakout
  ----> http://www.adafruit.com/products/3538

  These sensors use I2C to communicate. The device's I2C address is 0x69

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Dean Miller for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/

#include <Wire.h>
#include <Adafruit_AMG88xx.h>


Adafruit_AMG88xx amg;

float pixels[AMG88xx_PIXEL_ARRAY_SIZE];
int waitToGetAmb = 10;
int ambientTemp = 200;
int counter = 0;
int peopleCount = 0;
boolean isMovement = false;

void setup() {
    Serial.begin(9600);
    Serial.println(F("AMG88xx pixels"));

    
    bool status;
    
    // default settings
    status = amg.begin();
    if (!status) {
        Serial.println("Could not find a valid AMG88xx sensor, check wiring!");
        while (1);
    }
    
    Serial.println("-- Pixels Test --");

    Serial.println();

    delay(100); // let sensor boot up
}


void loop() {
    //read all the pixels
    amg.readPixels(pixels);
    int movement = 0;    

    //Serial.println(ambientTemp);
    
    for (int j = 1; j <= AMG88xx_PIXEL_ARRAY_SIZE; j++) {
      int fahrenheit = pixels[j-1] + (9/5) + 32;
      
      if ((abs(fahrenheit - ambientTemp) <= 5 || fahrenheit < ambientTemp) && counter % 100 == 0) {
        ambientTemp = pixels[j-1] + (9/5) + 32;
        counter++;
      }
      
      if((fahrenheit - ambientTemp) > 3 && !isMovement) {
        Serial.println(ambientTemp);
        isMovement = true;
        Serial.println("Person Detected!!!!!!!");
        Serial.println(peopleCount);
        peopleCount += 1;


        for(int i=1; i <= AMG88xx_PIXEL_ARRAY_SIZE; i++){
          int f = pixels[i-1] + (9/5) + 32;
          
          if((f - ambientTemp) > 3) {
            
            Serial.print("X");
            Serial.print(", ");
          } else {
             Serial.print("O");
             Serial.print(", ");
          }
         
          if( i%8 == 0 ) Serial.println();
        }
        
        j = 0;
        break; 
      }

      if ((fahrenheit - ambientTemp) > 3) {
        j = 0;
        break;
      }
      
      if (j == AMG88xx_PIXEL_ARRAY_SIZE) {
        //Serial.println("++++There is no person detected");
        isMovement = false;
      }
    }
}
