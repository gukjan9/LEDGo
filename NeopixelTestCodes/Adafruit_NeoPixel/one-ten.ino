// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      64

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

  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(30);
}

void loop() {

  // For a set of NeoPixels the first NeoPixel is 0, second is 1, all the way up to the count of pixels minus one.

  for(int i=0;i<NUMPIXELS;i++){//1

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
   pixels.setPixelColor(12, pixels.Color(255,0,0));
   pixels.setPixelColor(19, pixels.Color(255,0,0));
   pixels.setPixelColor(20, pixels.Color(255,0,0));
   pixels.setPixelColor(28, pixels.Color(255,0,0));
   pixels.setPixelColor(36, pixels.Color(255,0,0));
   pixels.setPixelColor(44, pixels.Color(255,0,0));
   pixels.setPixelColor(52, pixels.Color(255,0,0));
   pixels.setPixelColor(59, pixels.Color(255,0,0));
   pixels.setPixelColor(60, pixels.Color(255,0,0));
   pixels.setPixelColor(61, pixels.Color(255,0,0));
   pixels.show(); // This sends the updated pixel color to the hardware.
    delay(500); // Delay for a period of time (in milliseconds).
pixels.clear();
  break;
  }
 for(int i=0;i<NUMPIXELS;i++){//2
  pixels.setPixelColor(11, pixels.Color(255,69,0));
  pixels.setPixelColor(12, pixels.Color(255,69,0));
  pixels.setPixelColor(21, pixels.Color(255,69,0));
  pixels.setPixelColor(29, pixels.Color(255,69,0));
  pixels.setPixelColor(36, pixels.Color(255,69,0));
  pixels.setPixelColor(43, pixels.Color(255,69,0));
  pixels.setPixelColor(50, pixels.Color(255,69,0));
  pixels.setPixelColor(58, pixels.Color(255,69,0));
  pixels.setPixelColor(59, pixels.Color(255,69,0));
  pixels.setPixelColor(60, pixels.Color(255,69,0)); 
  pixels.setPixelColor(61, pixels.Color(255,69,0));
  pixels.setPixelColor(18, pixels.Color(255,69,0));

  
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
 for(int i=0;i<NUMPIXELS;i++){//3
  pixels.setPixelColor(11, pixels.Color(255,255,0));
   pixels.setPixelColor(12, pixels.Color(255,255,0));
    pixels.setPixelColor(18, pixels.Color(255,255,0));
     pixels.setPixelColor(21, pixels.Color(255,255,0));
      pixels.setPixelColor(29, pixels.Color(255,255,0));
       pixels.setPixelColor(35, pixels.Color(255,255,0));
        pixels.setPixelColor(36, pixels.Color(255,255,0));
         pixels.setPixelColor(45, pixels.Color(255,255,0));
          pixels.setPixelColor(53, pixels.Color(255,255,0));
           pixels.setPixelColor(50, pixels.Color(255,255,0));
             pixels.setPixelColor(59, pixels.Color(255,255,0));
 pixels.setPixelColor(60, pixels.Color(255,255,0));
 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
 for(int i=0;i<NUMPIXELS;i++){//4
  pixels.setPixelColor(11, pixels.Color(0,255,0));
  pixels.setPixelColor(12, pixels.Color(0,255,0));
   pixels.setPixelColor(18, pixels.Color(0,255,0));
    pixels.setPixelColor(20, pixels.Color(0,255,0));
     pixels.setPixelColor(25, pixels.Color(0,255,0));
      pixels.setPixelColor(28, pixels.Color(0,255,0));
       pixels.setPixelColor(33, pixels.Color(0,255,0));
        pixels.setPixelColor(41, pixels.Color(0,255,0));
         pixels.setPixelColor(42, pixels.Color(0,255,0));
          pixels.setPixelColor(43, pixels.Color(0,255,0));
           pixels.setPixelColor(44, pixels.Color(0,255,0));
            pixels.setPixelColor(45, pixels.Color(0,255,0));
             pixels.setPixelColor(46, pixels.Color(0,255,0));
              pixels.setPixelColor(52, pixels.Color(0,255,0));
             pixels.setPixelColor(60, pixels.Color(0,255,0));
             pixels.setPixelColor(36, pixels.Color(0,255,0));

 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
 for(int i=0;i<NUMPIXELS;i++){//5
  pixels.setPixelColor(10, pixels.Color(0,0,255));
  pixels.setPixelColor(11, pixels.Color(0,0,255));
  pixels.setPixelColor(12, pixels.Color(0,0,255));
  pixels.setPixelColor(13, pixels.Color(0,0,255));
  pixels.setPixelColor(18, pixels.Color(0,0,255));
  pixels.setPixelColor(26, pixels.Color(0,0,255));
  pixels.setPixelColor(34, pixels.Color(0,0,255));
  pixels.setPixelColor(35, pixels.Color(0,0,255));
  pixels.setPixelColor(36, pixels.Color(0,0,255));
  pixels.setPixelColor(45, pixels.Color(0,0,255));
  pixels.setPixelColor(53, pixels.Color(0,0,255));
  pixels.setPixelColor(59, pixels.Color(0,0,255));
  pixels.setPixelColor(60, pixels.Color(0,0,255));
 pixels.setPixelColor(58, pixels.Color(0,0,255));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
 for(int i=0;i<NUMPIXELS;i++){//6
 
 pixels.setPixelColor(11, pixels.Color(0,255,255));
 pixels.setPixelColor(12, pixels.Color(0,255,255));
 pixels.setPixelColor(21, pixels.Color(0,255,255));
 pixels.setPixelColor(18, pixels.Color(0,255,255));
 pixels.setPixelColor(26, pixels.Color(0,255,255));
 pixels.setPixelColor(34, pixels.Color(0,255,255));
 pixels.setPixelColor(35, pixels.Color(0,255,255));
 pixels.setPixelColor(36, pixels.Color(0,255,255));
 pixels.setPixelColor(45, pixels.Color(0,255,255));
 pixels.setPixelColor(42, pixels.Color(0,255,255));
 pixels.setPixelColor(50, pixels.Color(0,255,255));
 pixels.setPixelColor(59, pixels.Color(0,255,255));
 pixels.setPixelColor(60, pixels.Color(0,255,255));
 pixels.setPixelColor(53, pixels.Color(0,255,255));
 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
 for(int i=0;i<NUMPIXELS;i++){//7
 
 pixels.setPixelColor(10, pixels.Color(75,0,13));
 pixels.setPixelColor(11, pixels.Color(75,0,13));
 pixels.setPixelColor(12, pixels.Color(75,0,13));
 pixels.setPixelColor(13, pixels.Color(75,0,13));
 pixels.setPixelColor(21, pixels.Color(75,0,13));
 pixels.setPixelColor(29, pixels.Color(75,0,13));
 pixels.setPixelColor(37, pixels.Color(75,0,13));
 pixels.setPixelColor(45, pixels.Color(75,0,13));
 pixels.setPixelColor(53, pixels.Color(75,0,13));
 pixels.setPixelColor(61, pixels.Color(75,0,13));
pixels.setPixelColor(18, pixels.Color(75,0,13));
pixels.setPixelColor(26, pixels.Color(75,0,13));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
  for(int i=0;i<NUMPIXELS;i++){//8
  pixels.setPixelColor(11, pixels.Color(148,0,211));
 pixels.setPixelColor(12, pixels.Color(148,0,211));
 pixels.setPixelColor(18, pixels.Color(148,0,211));
 pixels.setPixelColor(21, pixels.Color(148,0,211));
 pixels.setPixelColor(29, pixels.Color(148,0,211));
 pixels.setPixelColor(26, pixels.Color(148,0,211));
 pixels.setPixelColor(35, pixels.Color(148,0,211));
 pixels.setPixelColor(36, pixels.Color(148,0,211));
 pixels.setPixelColor(45, pixels.Color(148,0,211));
 pixels.setPixelColor(53, pixels.Color(148,0,211));
 pixels.setPixelColor(60, pixels.Color(148,0,211));
 pixels.setPixelColor(59, pixels.Color(148,0,211));
 pixels.setPixelColor(42, pixels.Color(148,0,211));
 pixels.setPixelColor(50, pixels.Color(148,0,211));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
   for(int i=0;i<NUMPIXELS;i++){//9
  pixels.setPixelColor(11, pixels.Color(255,0,255));
  pixels.setPixelColor(12, pixels.Color(255,0,255));
  pixels.setPixelColor(18, pixels.Color(255,0,255));
  pixels.setPixelColor(26, pixels.Color(255,0,255));
  pixels.setPixelColor(35, pixels.Color(255,0,255));
  pixels.setPixelColor(36, pixels.Color(255,0,255));
  pixels.setPixelColor(37, pixels.Color(255,0,255));
  pixels.setPixelColor(29, pixels.Color(255,0,255));
  pixels.setPixelColor(21, pixels.Color(255,0,255));
  pixels.setPixelColor(45, pixels.Color(255,0,255));
  pixels.setPixelColor(53, pixels.Color(255,0,255));
  pixels.setPixelColor(61, pixels.Color(255,0,255));
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }

   for(int i=0;i<NUMPIXELS;i++){//9
  pixels.setPixelColor(9, pixels.Color(255,255,255));
  pixels.setPixelColor(17, pixels.Color(255,255,255));
  pixels.setPixelColor(25, pixels.Color(255,255,255));
  pixels.setPixelColor(33, pixels.Color(255,255,255));
  pixels.setPixelColor(35, pixels.Color(255,255,255));
  pixels.setPixelColor(41, pixels.Color(255,255,255));
  pixels.setPixelColor(49, pixels.Color(255,255,255));
  pixels.setPixelColor(57, pixels.Color(255,255,255));
  pixels.setPixelColor(12, pixels.Color(255,255,255));
  pixels.setPixelColor(13, pixels.Color(255,255,255));
  pixels.setPixelColor(19, pixels.Color(255,255,255));
  pixels.setPixelColor(27, pixels.Color(255,255,255));
  pixels.setPixelColor(35, pixels.Color(255,255,255));
  pixels.setPixelColor(43, pixels.Color(255,255,255));
  pixels.setPixelColor(51, pixels.Color(255,255,255));
  pixels.setPixelColor(60, pixels.Color(255,255,255));
  pixels.setPixelColor(61, pixels.Color(255,255,255));
  pixels.setPixelColor(54, pixels.Color(255,255,255));
  pixels.setPixelColor(46, pixels.Color(255,255,255));
  pixels.setPixelColor(38, pixels.Color(255,255,255));
  pixels.setPixelColor(30, pixels.Color(255,255,255));
  pixels.setPixelColor(22, pixels.Color(255,255,255));
  
 
  pixels.show(); // This sends the updated pixel color to the hardware.
  delay(500);
  pixels.clear();
  break;
 }
}
