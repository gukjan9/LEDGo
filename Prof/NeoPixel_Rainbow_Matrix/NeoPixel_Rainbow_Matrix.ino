#include <Adafruit_NeoPixel.h>

#define PIN            6
#define NUMPIXELS      56
#define COUNT 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      pixels.show(); 
      delay(100); 
}

uint32_t C0 = 0x000000; //Black
uint32_t C1 = 0xFFFFFF; //White
uint32_t C2 = 0xFF0000; //Red
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x0000FF; //Blue
uint32_t C5 = 0xFFFF00; //Yellow
uint32_t C6 = 0x00FFFF; //Cyan
uint32_t C7 = 0xFF00FF; //Magenta
uint32_t C8 = 0x800000; //Maroon
uint32_t C9 = 0x808000; //Olive
uint32_t C10 = 0x800080; //Purple
uint32_t C11 = 0x008080; //Teal

uint32_t MyColors[12] = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11}; //put the colors in an array

uint32_t color = MyColors[0]; 

void setup() {
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {  
  for(int led=0; led<NUMPIXELS; led++) {  
    if(led % 2 == 0) color = MyColors[10]; else color = MyColors[11];
    if((led % COUNT) == 6 || (led % COUNT) == 7) continue; else display_PixelColor(led, color);
  }
  delay(1000);
  pixels.clear();
}
