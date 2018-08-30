#include <Adafruit_NeoPixel.h>

#define PIN            6

#define PIXELS_ROWS 32
#define PIXELS_COLUMNS 24
#define PIXELS_COUNT 768 //PIXELS_ROWS * PIXELS_COLUMNS

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(PIXELS_COUNT, PIN, NEO_GRB + NEO_KHZ800);

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

uint32_t color1 = MyColors[4];
uint32_t color2 = MyColors[7];

void display_PixelColor(int led, uint32_t color) {
  /* int row;
  int col;
      led = calcLED(row, col); */
      pixels.setPixelColor(led, color);
      pixels.show(); 
}

void clearPIXELS(){
  for (int i=0; i<PIXELS_COUNT; i++){
    pixels.setPixelColor(i, 0);
  }
}

int calcLED(int row, int col){
  int odd = row%2;
  int led = 0;

  if(odd){
    if(col >= 1 && col <= 8){
      led = 8*row - col;
      return led;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row - col + 264;
      return led;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row - col + 528;
      return led;
    }
  }
  else{
    if(col >= 1 && col <= 8){
      led = 8*row + col - 9;
      return led;
    }
    else if(col >= 9 && col <= 16){
      led = 8*row + col - 9 + 248;
      return led;
    }
    else if(col >= 17 && col <= 24){
      led = 8*row + col - 9 + 496;
      return led;
    }
  }
}

void showBlockcolor1(int a, int i){
  int cnt = 0;

  int ledarr[9] = {calcLED(a,i), calcLED(a,i+1), calcLED(a,i+2), calcLED(a+1,i), calcLED(a+1,i+1), calcLED(a+1,i+2), calcLED(a+2,i), calcLED(a+2,i+1), calcLED(a+2,i+2)};
  display_PixelColor(ledarr[cnt], color1);
  display_PixelColor(ledarr[cnt+1], color1);
  display_PixelColor(ledarr[cnt+2], color1);
  display_PixelColor(ledarr[cnt+3], color1);
  display_PixelColor(ledarr[cnt+4], color1);
  display_PixelColor(ledarr[cnt+5], color1);
  display_PixelColor(ledarr[cnt+6], color1);
  display_PixelColor(ledarr[cnt+7], color1);
  display_PixelColor(ledarr[cnt+8], color1);
}

void showBlockcolor2(int a, int i){
  int cnt = 0;

  int ledarr[9] = {calcLED(a,i), calcLED(a,i+1), calcLED(a,i+2), calcLED(a+1,i), calcLED(a+1,i+1), calcLED(a+1,i+2), calcLED(a+2,i), calcLED(a+2,i+1), calcLED(a+2,i+2)};
  display_PixelColor(ledarr[cnt], color2);
  display_PixelColor(ledarr[cnt+1], color2);
  display_PixelColor(ledarr[cnt+2], color2);
  display_PixelColor(ledarr[cnt+3], color2);
  display_PixelColor(ledarr[cnt+4], color2);
  display_PixelColor(ledarr[cnt+5], color2);
  display_PixelColor(ledarr[cnt+6], color2);
  display_PixelColor(ledarr[cnt+7], color2);
  display_PixelColor(ledarr[cnt+8], color2);
}

void blockBlink(){
  int i = 21;
  int a = 1;

  while(i>=1){
    showBlockcolor1(a, i);
    delay(100);
    i = i-4;
    clearPIXELS();
  }
}

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);
  blockBlink();

}

void loop() {
  
  

}
