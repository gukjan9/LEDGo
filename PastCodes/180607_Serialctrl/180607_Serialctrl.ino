// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library
#include "cor.h"
#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
#include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      56

#define COUNT 10
uint32_t c=0xA366FF;
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code 
  Serial.begin(9600);
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(30);
}

void loop() {
  inputon(); 
  
  /*for(int i=0; i<NUMPIXELS; i++) {
      if((i % 16) == 0 || (i % 16) == 1 ||  (i % 16) == 14 ||  (i % 16) == 15)  continue;
        else display_PixelColor(i,c);*/
  
  delay(100);
  pixels.clear();


}

void display_PixelColor(int n, int c) {
      pixels.setPixelColor(n, c);
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(100); // Delay for a period of time (in milliseconds).
//      pixels.clear();
}



void inputon(){
  if(Serial.available()){
  
    long value1=Serial.parseInt();

  switch(value1)
    {case 11:
    display_PixelColor(P11,c);
    break;
    case 12:
    display_PixelColor(P12,c);
    break;
    case 13:
    display_PixelColor(P13,c);
    break;
    case 14:
    display_PixelColor(P14,c);
    break;
    case 15:
    display_PixelColor(P15,c);
    break;
    case 16:
    display_PixelColor(P16,c);
    break;
    case 21:
    display_PixelColor(P21,c);
    break;
    case 22:
    display_PixelColor(P22,c);
    break;
    case 23:
    display_PixelColor(P23,c);
    break;
    case 24:
    display_PixelColor(P24,c);
    break;
    case 25:
    display_PixelColor(P25,c);
    break;
    case 26:
    display_PixelColor(P26,c);
    break;
    case 31:
    display_PixelColor(P31,c);
    break;
    case 32:
    display_PixelColor(P32,c);
    break;
    case 33:
    display_PixelColor(P33,c);
    break;
    case 34:
    display_PixelColor(P34,c);
    break;
    case 35:
    display_PixelColor(P35,c);
    break;
    case 36:
    display_PixelColor(P36,c);
    break;
    case 41:
    display_PixelColor(P41,c);
    break;
    case 42:
    display_PixelColor(P42,c);
    break;
    case 43:
    display_PixelColor(P43,c);
    break;
    case 44:
    display_PixelColor(P44,c);
    break;
    case 45:
    display_PixelColor(P45,c);
    break;
    case 46:
    display_PixelColor(P46,c);
    break;  
    case 51:
    display_PixelColor(P51,c);
    break;
    case 52:
    display_PixelColor(P52,c);
    break;
    case 53:
    display_PixelColor(P53,c);
    break;
    case 54:
    display_PixelColor(P54,c);
    break;
    case 55:
    display_PixelColor(P55,c);
    break;
    case 56:
    display_PixelColor(P56,c);
    break;
    case 61:
    display_PixelColor(P61,c);
    break;
    case 62:
    display_PixelColor(P62,c);
    break;
    case 63:
    display_PixelColor(P63,c);
    break;
    case 64:
    display_PixelColor(P64,c);
    break;
    case 65:
    display_PixelColor(P65,c);
    break;
    case 66:
    display_PixelColor(P66,c);
    break;
    case 71:
    display_PixelColor(P71,c);
    break;
    case 72:
    display_PixelColor(P72,c);
    break;
    case 73:
    display_PixelColor(P73,c);
    break;
    case 74:
    display_PixelColor(P74,c);
    break;
    case 75:
    display_PixelColor(P75,c);
    break;
    case 76:
    display_PixelColor(P76,c);
    }
}
}

