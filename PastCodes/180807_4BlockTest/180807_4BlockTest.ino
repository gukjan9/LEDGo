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

uint32_t color = MyColors[4];

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

void blockBlink(){
  
}

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.setBrightness(20);

}

void loop() {
  int cnt = 0;
  int i = 22;
  int j = 21;

  while(i>=2 && j>=1){
    int ledarr[4] = {calcLED(1,i), calcLED(1,j), calcLED(2,i), calcLED(2,j)};
    display_PixelColor(ledarr[cnt], color);
    display_PixelColor(ledarr[cnt+1], color);
    display_PixelColor(ledarr[cnt+2], color);
    display_PixelColor(ledarr[cnt+3], color);
    delay(100);
    i = i-4;
    j = j-4;
    clearPIXELS();
  }

  /* int ledarr1[4] = {calcLED(1,24), calcLED(1,23), calcLED(2,24), calcLED(2,23)};
  int ledarr2[4] = {calcLED(1,23), calcLED(1,22), calcLED(2,23), calcLED(2,22)};
  int ledarr3[4] = {calcLED(1,22), calcLED(1,21), calcLED(2,22), calcLED(2,21)};

  display_PixelColor(ledarr1[cnt], color);
  display_PixelColor(ledarr1[cnt+1], color);
  display_PixelColor(ledarr1[cnt+2], color);
  display_PixelColor(ledarr1[cnt+3], color);
  clearPIXELS();
  delay(1000);

  display_PixelColor(ledarr2[cnt], color);
  display_PixelColor(ledarr2[cnt+1], color);
  display_PixelColor(ledarr2[cnt+2], color);
  display_PixelColor(ledarr2[cnt+3], color);
  clearPIXELS();
  delay(1000);

  display_PixelColor(ledarr3[cnt], color);
  display_PixelColor(ledarr3[cnt+1], color);
  display_PixelColor(ledarr3[cnt+2], color);
  display_PixelColor(ledarr3[cnt+3], color);
  clearPIXELS();
  delay(1000); */

  /* 작동 x
    for(i=24; i>=2; i--){
    int ledarr[4] = {calcLED(1,i), calcLED(1,j), calcLED(2,i), calcLED(2,j)};
    display_PixelColor(ledarr[cnt], color);
    display_PixelColor(ledarr[cnt+1], color);
    display_PixelColor(ledarr[cnt+2], color);
    display_PixelColor(ledarr[cnt+3], color);
    clearPIXELS();
    delay(1000);      
    }
  for(j=23; j>=1; j--){
    int ledarr[4] = {calcLED(1,i), calcLED(1,j), calcLED(2,i), calcLED(2,j)};
    display_PixelColor(ledarr[cnt], color);
    display_PixelColor(ledarr[cnt+1], color);
    display_PixelColor(ledarr[cnt+2], color);
    display_PixelColor(ledarr[cnt+3], color);
    clearPIXELS();
    delay(1000); 
  } */
  
  /* 테스트용
  int led1 = calcLED(1,24);
  int led2 = calcLED(1,23);
  int led3 = calcLED(2,24);
  int led4 = calcLED(2,23);

  display_PixelColor(led1, color);
  display_PixelColor(led2, color);
  display_PixelColor(led3, color);
  display_PixelColor(led4, color); */
  

}
