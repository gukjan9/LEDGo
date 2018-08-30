#include <Adafruit_NeoPixel.h>

#define PIN            3
#define NUMPIXELS      768
#define COUNT 8

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const int buttonPin1 = 22;   
int buttonState1 = 0;
int bt1=0;

void display_PixelColor(int led, uint32_t color) {
      pixels.setPixelColor(led, color);
      pixels.show(); 
      delay(100); 
}

int n = 0;

int pressKey(){
  bt1 = digitalRead(buttonPin1);

  while(1){
    buttonState1=digitalRead(buttonPin1);

    if(bt1 !=0&&  buttonState1==0){
    Serial.println("Button1 Pressed");
    n++;
    if(n>6) n = 0;
    return n;
   }
   bt1=buttonState1;
  }
}

uint32_t C1 = 0xFFFFFF; //White
uint32_t C2 = 0xFF0000; //Red
uint32_t C3 = 0x00FF00; //Green
uint32_t C4 = 0x0000FF; //Blue
uint32_t C5 = 0xFFFF00; //Yellow
uint32_t C6 = 0x00FFFF; //Cyan
uint32_t C7 = 0xFF00FF; //Magenta

uint32_t MyColors[7] = {C1, C2, C3, C4, C5, C6, C7}; //put the colors in an array 

void setup() {
  Serial.begin(9600);
  pinMode(buttonPin1, INPUT);
  pixels.begin();
  pixels.setBrightness(10);
}

void loop() {
  for(int led=0; led<NUMPIXELS; led++) {
    int j = pressKey();
    uint32_t color = MyColors[j];
    Serial.println(j);
    display_PixelColor(led, color);
  }
  delay(1000);
  pixels.clear();
}
