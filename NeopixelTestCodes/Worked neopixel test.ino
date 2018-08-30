#include <Adafruit_NeoPixel.h>

 

// Which pin on the Arduino is connected to the NeoPixels?

#define PIN            6

 

// How many NeoPixels are attached to the Arduino?

#define NUMPIXELS      8*32

 

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.

// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest

// example for more information on possible values.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

 

int delayval = 100; // delay for half a second

 

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.

}

 

void loop() {

 

  for(int i = 0; i < NUMPIXELS; i += 1){

    pixels.setPixelColor(i, pixels.Color(random(256),random(256),random(256)));

    pixels.show() ;

    delay(delayval);

  }

  delay(500) ;

  for(int i = 0; i < 3; i++) {

    for(int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, pixels.Color(0,0,0)) ;

    }

    pixels.show() ;

    delay(500) ;

 

    int ran[3] = {

      random(256), random(256), random(256)        } 

    ;

    for(int i = 0; i < NUMPIXELS; i++) {

      pixels.setPixelColor(i, pixels.Color(ran[0],ran[1],ran[2])) ;

    }

    pixels.show() ;

    delay(500) ;

  }

  for(int i = 0; i < NUMPIXELS; i++) {

    pixels.setPixelColor(i, pixels.Color(0,0,0)) ;

  }

  pixels.show() ;

  delay(500) ;

}


