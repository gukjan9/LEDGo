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

// uint32_t c=0xA366FF;
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

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

uint32_t MyColors[12] = {C0, C1, C2, C3, C4, C5, C6, C7, C8, C9, C10, C11};

uint32_t color = MyColors[0];
uint8_t data[56];
boolean flag = 0;

int E1=0x00;
int E2=0x00;
int E3=0x00;
int E4=0x00;
int E5=0x00;
int E6=0x00;
int E7=0x00;

const int buttonPin1 = 22;    
const int buttonPin2 = 24;
const int buttonPin3 = 26;
const int buttonPin4 = 28;
const int buttonPin5 = 30;
const int buttonPin6 = 32;
const int buttonPin7 = 34;

int buttonState1 = 0;  
int buttonState2 = 0;  
int buttonState3 = 0;  
int buttonState4 = 0;  
int buttonState5 = 0;  
int buttonState6 = 0;  
int buttonState7 = 0; 

int led;

int cnt1 = 0;
int cnt2 = 0;
int cnt3 = 0;
int cnt4 = 0;
int cnt5 = 0;
int cnt6 = 0;
int cnt7 = 0;

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif
  // End of trinket special code 
  Serial.begin(9600);

  pinMode(buttonPin1, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(buttonPin3, INPUT_PULLUP);
  pinMode(buttonPin4, INPUT_PULLUP);
  pinMode(buttonPin5, INPUT_PULLUP);
  pinMode(buttonPin6, INPUT_PULLUP);
  pinMode(buttonPin7, INPUT_PULLUP);
  
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(30);

  for(int i=0; i<NUMPIXELS; i++) {
    data[i] = 8;
  }
}

void loop() {
  /*inputon(); */
  
  /*for(int i=0; i<NUMPIXELS; i++) {
      if((i % 16) == 0 || (i % 16) == 1 ||  (i % 16) == 14 ||  (i % 16) == 15)  continue;
        else display_PixelColor(i,c);*/

    led = data_create();
    Serial.print("data_create led = ");
    Serial.println(led);
    if(flag == 0) color = MyColors[2]; else color = MyColors[4];
    display_PixelColor(led, color);
  
  // delay(1000);
  // pixels.clear();


}

void display_PixelColor(int n, uint32_t color) {
      pixels.setPixelColor(n, color);
      pixels.show(); // This sends the updated pixel color to the hardware.
      delay(100); // Delay for a period of time (in milliseconds).
//      pixels.clear();
}


void stack(){
  if(Serial.available()){
    long row=Serial.parseInt();

   switch(row)
{case 1:
   E1=(E1<<1)|1;
   break;
 case 2:
   E2=(E2<<1)|1;
   break;
 case 3:
   E3=(E3<<1)|1;
   break;
 case 4:
   E4=(E4<<1)|1;
   break;
 case 5:
   E5=(E5<<1)|1;
   break;
 case 6:
   E6=(E6<<1)|1;
   break;
 case 7:
   E7=(E7<<1)|1;
   break;              
  }
}
}

int data_create() {   
  led = tack();
  Serial.print("tack led = ");
  Serial.println(led);
  if(flag == 0) flag = 1; else flag = 0;
  if(data[led] == 8) {
    data[led] = flag;
    return led;
  } else {
    data_create();
  }  
}

int tack(){
  // read the state of the pushbutton value:
  buttonState1 = digitalRead(buttonPin1);
  buttonState2 = digitalRead(buttonPin2);
  buttonState3 = digitalRead(buttonPin3);
  buttonState4 = digitalRead(buttonPin4);
  buttonState5 = digitalRead(buttonPin5);
  buttonState6 = digitalRead(buttonPin6);
  buttonState7 = digitalRead(buttonPin7);

  int row1[6] = {7, 6, 5, 4, 3, 2};
  int row2[6] = {8, 9, 10, 11, 12, 13};
  int row3[6] = {23, 22, 21, 20, 19, 18};
  int row4[6] = {24, 25, 26, 27, 28, 29};
  int row5[6] = {39, 38, 37, 36, 35, 34};
  int row6[6] = {40, 41, 42, 43, 44, 45};
  int row7[6] = {55, 54, 53, 52, 51, 50};


   // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (buttonState1 == HIGH) {
    Serial.println("Button1 Pressed");
    led = row1[cnt1];
    cnt1 += 1;
    Serial.print("cnt 1 :");
    Serial.println(cnt1);
  } else if (buttonState2 == HIGH) {
    Serial.println("Button2 Pressed");
    led = row2[cnt2];
    cnt2 += 1;
  } else if (buttonState3 == HIGH) {
    Serial.println("Button3 Pressed");
    led = row3[cnt3];
    cnt3 += 1;
  } else if (buttonState4 == HIGH) {
    Serial.println("Button4 Pressed");
    led = row4[cnt4];
    cnt4 += 1;
  } else if (buttonState5 == HIGH) {
    Serial.println("Button5 Pressed");
    led = row5[cnt5];
    cnt5 += 1;
  } else if (buttonState6 == HIGH) {
    Serial.println("Button6 Pressed");
    led = row6[cnt6];
    cnt6 += 1;
  } else if (buttonState7 == HIGH) {
    Serial.println("Button7 Pressed");
    led = row7[cnt7];
    cnt7 += 1;
  }
  return led;
}

/*void inputon(){
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
*/

