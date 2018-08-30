#include <Adafruit_NeoPixel.h>

#define NUMPIXELS      56
#define PIN            6 

int ch1 = 14;
int ch2 = 16;
int ch3 = 18;

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

uint32_t color = MyColors[6];

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      pixels.show(); 
      delay(100); 
}

void setup() {
  Serial.begin(115200);
  pixels.begin();
  pixels.setBrightness(10);
  
  pinMode(ch1, INPUT_PULLUP);
  pinMode(ch2, INPUT_PULLUP);
  pinMode(ch3, INPUT_PULLUP);

}

void loop() {
  int ch1_Read = digitalRead(14);
  int ch2_Read = digitalRead(16);
  int ch3_Read = digitalRead(18);

  delay(1000);

  Serial.print("CH1 : ");
  Serial.println(ch1_Read);
  Serial.print("CH2 : ");
  Serial.println(ch2_Read);
  Serial.print("CH3 : ");
  Serial.println(ch3_Read);

  if(ch1_Read == 0 && ch2_Read == 1 && ch3_Read == 1) // ch0은 1 1 1
  {
    display_PixelColor(1, color);
    pixels.clear();
  }

  else if(ch2_Read == 0 && ch1_Read == 1 && ch3_Read == 1)
  {
    display_PixelColor(2, color);
    pixels.clear();
  }

  else if(ch3_Read == 0 && ch1_Read == 1 && ch2_Read == 1)
  {
    display_PixelColor(3, color);
    pixels.clear();
  }

}
